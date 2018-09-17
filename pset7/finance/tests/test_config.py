# flask run # in another tab
# xvfb-run python3 test_config.py
import os, sys, time
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
basedir = os.path.abspath(os.path.dirname(__file__))

import unittest
from application import app
from selenium import webdriver
from selenium.webdriver import FirefoxOptions
from selenium.webdriver.common.keys import Keys

class TestConfig(unittest.TestCase):

    def setUp(self):
        opts = FirefoxOptions()
        opts.add_argument("--headless")
        self.driver = webdriver.Firefox(options=opts)

    def test_google_search(self):
        self.driver.get("http://www.google.com")
        elem = self.driver.find_element_by_name("q")
        search = "python"
        elem.send_keys(search)
        submit = self.driver.find_element_by_name("btnK")
        time.sleep(1)
        submit.click()
        time.sleep(1)
        if "python" in self.driver.title:
            print("32. self.driver.title == " + self.driver.title)
        assert "python" in self.driver.title

    def test_facebook_login(self):
        self.driver.get("http://www.facebook.com")
        assert "Facebook" in self.driver.title
        elem = self.driver.find_element_by_id("email")
        if "www.facebook.com" in self.driver.title:
            print("41. self.driver.title == " + self.driver.title)
        # assert "www.facebook.com" in self.driver.title

    def test_python_org(self):
        self.driver.get('https://python.org')
        print("46. self.driver.title == " + self.driver.title)

    def tearDown(self):
        self.driver.close()
        self.driver.quit()

if __name__ == '__main__':
    unittest.main()

