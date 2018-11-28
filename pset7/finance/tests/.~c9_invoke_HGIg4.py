# xvfb-run python3 test_finance.py
import os, sys, time
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
basedir = os.path.abspath(os.path.dirname(__file__))

import unittest
from application import app
from selenium import webdriver
from selenium.webdriver import FirefoxOptions
# from selenium.webdriver import FirefoxProfile
from selenium.webdriver.common.keys import Keys
# from selenium.webdriver.remote.webdriver import WebDriver

# from selenium.webdriver.firefox.options import Options
# from selenium.webdriver.common.proxy import Proxy

class TestFinance(unittest.TestCase):

    def setUp(self):
        opts = FirefoxOptions()
        opts.add_argument("--headless")
        self.driver = webdriver.Firefox(options=opts)


    def test_login(self):
        url = "https://edwd42-cs50-code42.c9users.io:8080"
        self.driver.get(url)
        submit_button = self.driver.find_element_by_class_name("button")
        submit_button.click()
        time.sleep(10)
        print("76. sleeping for 10...")
        username = self.driver.find_element_by_id('username')
        time.sleep(1)
        username.send_keys("ee")
        password = self.driver.find_element_by_id("password")
        password.send_keys("dd")
        submit_button = self.driver.find_element_by_id("submit")
        submit_button.click()
        time.sleep(10)
        print("86. self.driver.title == " + self.driver.title)
        assert "C$50" in self.driver.title

    def tearDown(self):
        self.driver.close()
        self.driver.quit()


if __name__ == '__main__':
    # app.run(host=os.getenv('IP', '0.0.0.0'), port=int(os.getenv('PORT', 8080)))
    unittest.main()






















