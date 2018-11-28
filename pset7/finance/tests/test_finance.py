# flask run # in another tab
# xvfb-run python3 test_finance.py
import os, sys
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
basedir = os.path.abspath(os.path.dirname(__file__))

import unittest
from application import *
from selenium import webdriver
from selenium.webdriver import FirefoxOptions
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

class TestFinance(unittest.TestCase):

    def setUp(self):
        # setUp must click big red Open the App button
        # and then login to test functions in the app

        # configure Firefox to run headless
        opts = FirefoxOptions()
        opts.add_argument("--headless")
        self.driver = webdriver.Firefox(options=opts)
        self.driver.implicitly_wait(30) # seconds

        # access the app URL
        url = "https://edwd42-cs50-code42.c9users.io:8080"
        self.driver.get(url)
        # html = self.driver.page_source
        # print(html)

        # click the big red button to Open the App
        # self.driver.implicitly_wait(1) # seconds
        submit_button = self.driver.find_element_by_class_name("button")
        submit_button.click()
        # time.sleep(2)
        self.driver.implicitly_wait(10) # seconds
        # print("38. sleeping for 2...")
        print("\n39. self.driver.title == " + self.driver.title)

    # def test_login(self):
        # login to the app - this is in setUp() not separate test_login()
        # so makes this an integration test not unit test.  hmmm.

        try:
            # print("46. self.driver.title == " + self.driver.title)
            username = self.driver.find_element_by_id("username")
            username.send_keys("ee")
            password = self.driver.find_element_by_id("password")
            password.send_keys("dd")
            submit_button = self.driver.find_element_by_id("submit")
            submit_button.click()
            self.driver.implicitly_wait(10) # seconds
            print("\n53. self.driver.title == " + self.driver.title)
            assert "C$50" in self.driver.title
        except:
            print("\n56. cannot find Log In")
            self.driver.close()
            self.driver.quit()

    def test_quote(self):
        # navigate to the quote link
        url = "https://edwd42-cs50-code42.c9users.io:8080/quote"
        # quote_link = self.driver.find_element_by_xpath('//a[@href="/quote"]')
        quote_link = self.driver.find_element_by_link_text("Quote")
        # quote_link = self.driver.find_element_by_id("quote")
        quote_link.click()
        # make sure we're on the Quote page - self.driver.title == C$50 Finance: Quote
        print("\n67. self.driver.title == " + self.driver.title)
        try:
            symbol = self.driver.find_element_by_name("symbol")
            symbol.send_keys("ee")
            # <button class="btn btn-primary" type="submit" id="submit>Get Quote</button>
            submit_button = self.driver.find_element_by_id("submit")
            submit_button.click()

            # now we should be on the Quoted page
            # print("76. self.driver.title == " + self.driver.title)
            assert "Quoted" in self.driver.title
        except:
            print("\n79. cannot find Quote page")
            self.driver.close()
            self.driver.quit()

    def test_deposit(self):
        print("86. inside test_deposit(self)")
        self.deposit(55)

    def tearDown(self):
        print("\n102. inside tearDown()")
        self.driver.close()
        self.driver.quit()

if __name__ == '__main__':
    # app.run(host=os.getenv('IP', '0.0.0.0'), port=int(os.getenv('PORT', 8080)))
    unittest.main()
