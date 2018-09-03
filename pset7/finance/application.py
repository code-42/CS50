import os

from cs50 import SQL, eprint
from flask import Flask, flash, redirect, render_template, request, session, url_for, make_response
# url_for() added by me 201808112215 per Doug Lloyds flask video
# https://www.youtube.com/watch?v=0SQdkDpMzKE&list=PLXmMXHVSvS-CMpHUeyIeqzs3kl-tIG-8R
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Ensure number of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        else:
            session["quote"] = lookup(request.form.get("symbol"))
            session["symbol"] = request.form.get("symbol")
            session["shares"] = int(request.form.get("shares"))
            print("in buy():")
            print(session["quote"])
            print(session["symbol"])
            print(session["shares"])

            user_id = session["user_id"]
            print(user_id)

            cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
              user_id=session["user_id"])

            session["cash"] = cash

            cash = cash[0]["cash"]

            fcash = float(cash)
            print("fcash == " + str(fcash))

            if(fcash <= 0):
                return apology("Sorry, you don't have enough cash for this trade.", 403)

            if(session.get('quote') is None):
                print("invalid symbol")
                return apology("invalid symbol", 403)

            return render_template("confirm.html", symbol=session, shares=session, quote=session)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/confirm", methods=["GET", "POST"])
@login_required
def confirm():
    """Confirm trade shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        print("in confirm():")
        shares = session.get('shares')
        print(shares)
        quote = session.get('quote')
        print(quote)
        print(quote["symbol"])

        user_id = session["user_id"]
        print(user_id)

        # addTradeToDatabase(shares,quote)
        return render_template("index.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/buy")  # change to / when finish testing /buy

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        else:
            session["quote"] = lookup(request.form.get("symbol"))
            print("in quote():")
            print(session["quote"])

            if(session.get('quote') is None):
                print("invalid symbol")
                return apology("invalid symbol", 403)

            return render_template("quoted.html", quote=session)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Adapted from "/login" above
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 403)

        # passed above tests so add name and password hash to database
        username = request.form.get("username")
        password = request.form.get("password")
        print("144. " + username + password)

        # source https://docs.python.org/2/library/hashlib.html
        hash = generate_password_hash(password)
        print("147. " + hash)

        check_hash = check_password_hash(hash, password)
        print("150. " + str(check_hash))

        # source Zamylas walkthrough video 2
        db.execute("INSERT INTO users (username, hash) \
        VALUES(:username, :hash)", \
        username=request.form.get("username"), \
        hash=hash)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
            username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    #return apology("TODO")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


# add transaction to atabase
def addTradeToDatabase(shares,quote):

    # extract values out of session object
    user_id = session["user_id"]
    symbol = quote["symbol"]
    price = quote["price"]
    timestamp = quote["timestamp"]

    # add trade to portfolio
    db.execute("INSERT INTO trades (user_id, shares, symbol, price, timestamp) \
        VALUES(:user_id, :shares, :symbol, :price, :timestamp)", \
        user_id=user_id,shares=shares,symbol=symbol,price=price,timestamp=timestamp)

# create table for transactions
# CREATE TABLE 'trades' ('user_id' TEXT NOT NULL,'shares' INTEGER NOT NULL,'symbol' TEXT NOT NULL,'price' REAL NOT NULL,'timestamp' DATETIME PRIMARY KEY NOT NULL);
