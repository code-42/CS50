# xvfb-run python3 test_finance.py
import os, sys, time
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
basedir = os.path.abspath(os.path.dirname(__file__))

import unittest
from application import app
from selenium import webdriver
from selenium.webdriver import FirefoxOptions
from selenium.webdriver import FirefoxProfile
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.remote.webdriver import WebDriver

from selenium.webdriver.firefox.options import Options
from selenium.webdriver.common.proxy import Proxy


class TestFinance(unittest.TestCase):

    # proxy_use= "http://edwd42-cs50-code42.c9users.io:8080"
    # desired_capability = webdriver.DesiredCapabilities.FIREFOX
    # desired_capability['proxy'] = {
    #     'proxyType': "manual",
    #     'httpProxy': proxy_use

    # }

    queryURL = "http://edwd42-cs50-code42.c9users.io:8080"
    browser = webdriver.Firefox()
    browser.get(queryURL)

    def setUp(self):
        # self.driver = webdriver.Chrome("/home/ubuntu/bin/chrome")
        # self.driver = webdriver.Chrome()
        opts = FirefoxOptions()
        # profile = webdriver.FirefoxProfile()
        # profile.set_preference("network.proxy.no_proxies_on", "http://edwd42-cs50-code42.c9users.io:8080/login")
        opts.add_argument("--headless")
        # profile = FirefoxProfile()
        # profile.set_preference("network.proxy.type", 1)
        # profile.set_preference("network.proxy.http", 'http://edwd42-cs50-code42.c9users.io')
        # profile.set_preference("network.proxy.http_port", '8080')
        host = "http://edwd42-cs50-code42.c9users.io:8080"
        # port = "8080"
        # opts.add_argument('--proxy-server=http://edwd42-cs50-code42.c9users.io:8080')

        # self.driver = WebDriver(command_executor=host, options=opts)
        self.driver = WebDriver(options=opts)
        # self.webdriver.common.utils.find_connectable_ip(host, port)
        # self.driver = webdriver.Firefox(command_executor=host, options=opts)

    # def test_google_search(self):
    #     search = "python"
    #     self.driver.get("http://www.google.com")
    #     elem = self.driver.find_element_by_name("q")
    #     elem.send_keys(search)
    #     submit = self.driver.find_element_by_name("btnK")
    #     time.sleep(2)
    #     submit.click()
    #     time.sleep(5)
    #     if "python" in self.driver.title:
    #         print("31. self.driver.title == " + self.driver.title)

    #     assert "python" in self.driver.title

    # def test_facebook_login(self):
    #     self.driver.get("http://www.facebook.com")
    #     assert "Facebook" in self.driver.title
    #     elem = self.driver.find_element_by_id("email")
    #     elem.send_keys("edwd")
    #     if "www.facebook.com" in self.driver.title:
    #         print("41. self.driver.title == " + self.driver.title)
    #     # assert "www.facebook.com" in self.driver.title

    # def test_python_org(self):
    #     self.driver.get('https://python.org')
    #     print("46. self.driver.title == " + self.driver.title)
    #     # html = self.driver.page_source
    #     # print(html)

    def test_login(self):
        self.driver.get("http://edwd42-cs50-code42.c9users.io:8080")
        print("53. self.driver.title == " + self.driver.title)
        username = self.driver.find_element_by_name("username")
        time.sleep(1)
        username.send_keys("ee")
        # password = self.driver.find_element_by_id("password")
        # password.send_keys("dd")
        # submit_button = self.driver.find_element_by_id("submit")
        # submit_button.click()
        # assert "CS50" in self.driver.title

    def tearDown(self):
        # self.browser.close()
        # self.browser.quit()
        self.driver.close()
        self.driver.quit()


if __name__ == '__main__':
    unittest.main()
