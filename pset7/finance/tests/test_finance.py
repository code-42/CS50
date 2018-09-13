import os, sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
basedir = os.path.abspath(os.path.dirname(__file__))

import unittest
from application import app
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

class TestFinance(unittest.TestCase):

    def setUp(self):
        self.driver = webdriver.Chrome("/usr/local/bin")

    def test_login(self):
        driver.get("http://edwd42-cs50-code42.c9users.io:8080")
        # username = driver.find_element_by_id("username")
        # username.send_keys("ee")
        # password = driver.find_element_by_id("password")
        # password.send_keys("dd")
        # submit_button = driver.find_element_by_id("submit")
        # submit_button.click()

    def tearDown(self):
        self.driver.close()
        self.driver.quit()

if __name__ == '__main__':
    unittest.main()