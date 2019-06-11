import pickle
import os

work_dir = os.path.dirname(os.path.abspath(__file__))
ACTION_DICT_FILE = os.path.join(work_dir, 'read/action_dict3.pkl')
ACTIONS = pickle.load(open(ACTION_DICT_FILE, 'rb'))
ACTION_SIZE = len(ACTIONS)
MODEL_SAVE_PATH = 'model/'
