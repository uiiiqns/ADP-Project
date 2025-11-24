import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/misys/forza_ws/race_stack/install/f1tenth_stack'
