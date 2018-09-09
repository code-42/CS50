import unittest
import application
from flask import request

class TestFinance(unittest.TestCase):

    def test_login(self):
        with application.test_request_context('/login', method='POST'):
            tester = application.login()
            response = tester.get('/login', content_type='html/text')
            self.assertEqual(response.status_code, 200)

    # def test_login_page_loads(self):
    #     tester = application.register()
    #     response = tester.get('/register', content_type='html/text')
    #     self.assertTrue('Register' in response.data)

    # def test_correct_login(self):
    #     tester = application.login()
    #     response = tester.post(
    #         '/login',
    #         data=dict(username="ee", password="dd"),
    #         follow_redirects=True
    #         )
    #     self.assertIn(b'Login', response.data)

if __name__ == '__main__':
    unittest.main()
