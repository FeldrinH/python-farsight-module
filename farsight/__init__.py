import re
import requests
from . import _impl

offset_repository = "https://api.github.com/repos/floh22/native-farsight-module/contents/offsets?ref=main"

_connected = False
_offsets_set = False
_champions_set = False
_game_version = None

_version_cleaning_regex = re.compile(r"[^\d.]")

def connect_to_league():
    global _connected
    if _connected:
        print("Warning: connect_to_league called while already connected")
        return
    
    if not _offsets_set:
        _import_offsets()
    
    if not _champions_set:
        _import_champions()
    
    _impl.connectToLeague()
    _connected = True

def disconnect_from_league():
    global _connected
    if not _connected:
        print("Warning: disconnect_from_league called while not connected")
        return

    _impl.disconnectFromLeague()
    _connected = False

def make_snapshot() -> dict:
    if not is_ready():
        raise RuntimeError("Not connected to league! Cannot create snapshot.")

    try:
        return _impl.makeSnapshot()
    except Exception:
        # Exceptions here generally mean LoL has closed. Disconnect automatically.
        disconnect_from_league()
        raise

def is_ready() -> bool:
    return _connected and _offsets_set and _champions_set

def _import_offsets():
    if _game_version is None:
        version_data: dict = _fetch_json('https://raw.communitydragon.org/latest/content-metadata.json')
        set_version(version_data['version'].split('.'))

    print(f"Latest game version: {'.'.join(_game_version)}")

    url = _get_patch_url(_game_version)
    offsets_data: dict = _fetch_json(url)
    offsets = {k: int(v, 0) for k, v in offsets_data.items()}

    set_offsets(offsets)

def _import_champions():    
    champions_data: list = _fetch_json('https://raw.communitydragon.org/latest/plugins/rcp-be-lol-game-data/global/default/v1/champion-summary.json')
    champions = [c['alias'].lower() for c in champions_data]

    set_champions(champions)

def _get_patch_url(version: list[int]) -> str:
    offsets_repo_data: list = _fetch_json(offset_repository)
    
    latest_patch_file = None
    latest_patch_version = -1
    for file in offsets_repo_data:
        offset_version = _version_cleaning_regex.sub('', file['name']).split('.')
        if offset_version[:len(version)] == version:
            offset_patch_version = int(offset_version[2])
            if latest_patch_file is None or offset_patch_version > latest_patch_version:
                latest_patch_file = file
                latest_patch_version = offset_patch_version
    
    if latest_patch_file is None:
        raise RuntimeError(f"Could not find offsets for game version {version}")

    print(f"Found offsets for version {'.'.join(version)}.{latest_patch_version}")

    return latest_patch_file['download_url']

def _fetch_json(url: str):
    res = requests.get(url)
    res.raise_for_status()
    return res.json()

def set_version(version: list[str]):
    global _game_version
    # Keep only first two numbers of version, because the last one does not need to match when finding a suitable offset
    _game_version = version[:2]

def set_offsets(offsets: dict[str, int]):
    global _offsets_set
    _impl.setOffsets(offsets)
    _offsets_set = True

def set_champions(champions: list[str]):
    global _champions_set
    _impl.setChampionNames(champions)
    _champions_set = True
