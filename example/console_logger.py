import pprint
import time
import traceback
import farsight

while True:
    # Note: connect_to_league and make_snapshot will raise an exception if the LoL client is not available or reading fails for some other reason.
    try:
        if not farsight.is_ready():
            farsight.connect_to_league()
    
        snapshot = farsight.make_snapshot()
        pprint.pprint(snapshot)
    except Exception as e:
        print("Failed to make snapshot:")
        traceback.print_exc()

    time.sleep(1)