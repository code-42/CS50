# flask run # in another tab
# xvfb-run python3 test_finance.py
import os, sys, time
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
basedir = os.path.abspath(os.path.dirname(__file__))

import unittest
from application import *
from selenium import webdriver
from selenium.webdriver import FirefoxOptions
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
# from selenium.webdriver.support.ui import WebDriverWait
# from selenium.webdriver.support.ui import expected_conditions as EC

class TestFinance(unittest.TestCase):

    def setUp(self):
        # setUp must click big red Open the App
        # and then login to test functions in the app

        # configure Firefox to run headless
        opts = FirefoxOptions()
        opts.add_argument("--headless")
        self.driver = webdriver.Firefox(options=opts)

        # access the app URL
        url = "https://edwd42-cs50-code42.c9users.io:8080"
        self.driver.get(url)
        self.driver.implicitly_wait(4) # seconds
        # html = self.driver.page_source
        # print(html)

        # click the big red button to Open the App
        # self.driver.implicitly_wait(1) # seconds
        submit_button = self.driver.find_element_by_class_name("button")
        submit_button.click()
        # time.sleep(2)
        self.driver.implicitly_wait(2) # seconds
        print("27. sleeping for 2...")
        print("28. self.driver.title == " + self.driver.title)

    def test_login(self):
        # login to the app - this is in setUp() not separate test_login()
        # so makes this an integration test not unit test.  hmmm.

        try:
            # print("40. self.driver.title == " + self.driver.title)
            username = self.driver.find_element_by_id("username")
            time.sleep(1)
            username.send_keys("ee")
            password = self.driver.find_element_by_id("password")
            password.send_keys("dd")
            submit_button = self.driver.find_element_by_id("submit")
            submit_button.click()
            time.sleep(10)
            print("49. self.driver.title == " + self.driver.title)
            assert "C$50" in self.driver.title
        except:
            print("52. cannot find Log In")
            self.driver.close()
            self.driver.quit()



    # def wait_for_element():
    #     # source https://selenium-python.readthedocs.io/waits.html#explicit-waits
    #     try:
    #         element = WebDriverWait(self.driver, 10).until(
    #             EC.presence_of_element_located((By.ID, "button"))
    #         )
    #     finally:
    #         self.driver.close()
    #         self.driver.quit()

    def tearDown(self):
        self.driver.close()
        self.driver.quit()

if __name__ == '__main__':
    # app.run(host=os.getenv('IP', '0.0.0.0'), port=int(os.getenv('PORT', 8080)))
    unittest.main()
