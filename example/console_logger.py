import pprint
import time
import farsight

while True:
    # Note: connect_to_league and make_snapshot will raise an exception if the LoL client is not available or reading fails for some other reason.
    try:
        if not farsight.is_ready():
            farsight.connect_to_league()
    
        snapshot = farsight.make_snapshot()
        pprint.pprint(snapshot)
    except Exception as e:
        print(f"Failed to make snapshot: {type(e).__name__}: {e}")

    time.sleep(1)