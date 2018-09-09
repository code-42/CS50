import unittest

from . import app
# from .. import application

class TestConfig(unittest.TestCase):

    def test_config_loading(self):
        # assert app.config['DEBUG'] is True
        # assert app.config['SQL'] == 'sqlite:///finance.db'
        pass

if __name__ == '__main__':
    unittest.main()
