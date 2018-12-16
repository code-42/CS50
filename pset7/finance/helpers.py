import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps
from cs50 import eprint

def apology(message, code=400):
    eprint("\nin apology():")

    if(session["user_id"] is None):
        return render_template("login.html")

    user_id = session["user_id"]
    username = session["username"]
    eprint(str(username) + " " + str(user_id))

    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s

    # add username and user_id for the Welcome message in navbar
    return render_template("apology.html", top=code, bottom=escape(message), username=username, user_id=user_id), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        response = requests.get(f"https://api.iextrading.com/1.0/stock/{urllib.parse.quote_plus(symbol)}/quote")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        # print(quote)
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"],
            "timestamp": quote["delayedPriceTime"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"
