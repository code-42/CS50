import os, sys
sys.path.append('../')

import application
import unittest
from application import app

class TestConfig(unittest.TestCase):

    def test_config_loading(self):
        # assert app.config['DEBUG'] is True
        # assert app.config['SQL'] == 'sqlite:///finance.db'
        pass

if __name__ == '__main__':
    unittest.main()

