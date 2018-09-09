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

    if(session["user_id"] is None):
        return render_template("login.html")

    rows = viewPortfolio()
    if len(rows) == 0:
        print("53. rows == " + str(len(rows)))
        return apology("sorry, you have no stocks", 403)

    portfolio = {}
    for row in range(len(rows)):
        session["quote"] = lookup(rows[row]["symbol"]) # get fresh data
        portfolio[rows[row]["symbol"]] = (
            rows[row]["symbol"],
            rows[row]["company_name"],
            rows[row]["sum(shares)"],
            session["quote"].get("price"),
            rows[row]["sum(shares * price)"]
            )

    cash = getCash() - sumPortfolio()
    sumTotal = cash + sumPortfolio()

    return render_template("index.html", portfolio=portfolio, cash=cash, sumTotal=sumTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Returns apology page if input is not valid
        isValidInput()

        session["quote"] = lookup(request.form.get("symbol"))
        session["shares"] = int(request.form.get("shares"))

        if(session.get('quote') is None):
            print("invalid symbol")
            return apology("invalid symbol", 403)

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
          user_id=session["user_id"])

        cash = float(cash[0]["cash"])
        print("cash == " + str(cash))

        price = session["quote"].get("price")
        shares = session["shares"]
        total = price * shares
        print("total == " + str(total))

        if(cash < total):
            return apology("Sorry, you don't have enough money for this trade.", 403)

        return render_template("confirm.html", shares=session, quote=session)

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
        print("118. num shares" + str(session.get('shares')))
        quote = session.get('quote')
        print("120. ")
        print(quote)
        print(quote["symbol"])
        print(quote["price"])

        price = session.get('price')
        print("124. " + str(price))
        # print(quote["symbol"].get('price'))

        user_id = session["user_id"]
        print(user_id)

        addTradeToDatabase(shares,quote,user_id)

        rows = viewPortfolio()
        # return render_template("index.html", portfolio=rows)
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # return apology("TODO")

    user_id = session["user_id"]

    # Query database for view
    rows = db.execute("SELECT * FROM trades WHERE user_id = :user_id",
                      user_id=user_id)

    if len(rows) == 0:
        return apology("sorry, you have no stocks", 403)

    return render_template("history.html", trades=rows)


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

        print("188. rows == " + str(len(rows)))
        print(str(rows[0]["username"]))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            print("193. rows == " + str(len(rows)))
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")  # change to / when finish testing /buy

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

@app.route("/register_test", methods=["GET", "POST"])
def register_test():
    """Register user"""


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

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
            username=request.form.get("username"))

        if len(rows) > 0:
            return apology("Sorry, that username is already taken. Try again.", 403)

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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Returns apology page if input is not valid
        isValidInput()

        symbol = request.form.get("symbol")
        session["quote"] = lookup(request.form.get("symbol"))
        session["shares"] = int(request.form.get("shares")) * -1

        if(getNumSharesOwned(symbol) < abs(session["shares"])):
            return apology("Sorry, you don't have enough shares for this trade.", 403)

        return render_template("confirm.html", shares=session, quote=session)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        rows = viewPortfolio()
        return render_template("sell.html", portfolio=rows)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


# add transaction to atabase
def addTradeToDatabase(shares,quote,user_id):

    # extract values out of session object
    # user_id = session["user_id"]

    symbol = quote["symbol"]
    company_name = quote["name"]
    price = quote["price"]
    timestamp = quote["timestamp"]
    tradeTotal = shares * price

    # add trade to portfolio
    db.execute("INSERT INTO trades (user_id, shares, symbol, company_name, price, timestamp) \
        VALUES(:user_id, :shares, :symbol, :company_name, :price, :timestamp)", \
        user_id=user_id,shares=shares,symbol=symbol,company_name=company_name,price=price,timestamp=timestamp)

    # Query database for cash
    id=user_id
    rows = db.execute("SELECT cash FROM users WHERE id = :id", id=id)

    print("188. rows == " + str(len(rows)))

    cash = rows[0]["cash"]
    print("360. cash == " + str(cash))

    cashBalance = cash - tradeTotal
    print(cashBalance)

    id = session["user_id"]
    db.execute("UPDATE users SET cash = :cashBalance WHERE id = :id", \
        id=id, cashBalance=cashBalance)

# retrieve portfolio view for display to index.html
def viewPortfolio():

    user_id = session["user_id"]
    print("362. user_id == " + str(user_id))

    # Query database for view
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id",
                      user_id=user_id)

    print(len(rows))
    print("357. rows == " + str(len(rows)))
    print(rows)

    return rows


# add up the total of all positions
def sumPortfolio():

    user_id = session["user_id"]

    # Query database for portfolio
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id",
                      user_id=user_id)

    if len(rows) == 0:
        return apology("sorry, you have no stocks", 403)

    print("422. ")
    sumStocks = 0
    for row in range(len(rows)):
        print(rows[row]["sum(shares * price)"])
        sumStocks = sumStocks + rows[row]["sum(shares * price)"]
        print(sumStocks)

    return sumStocks

def getCash():

    id = session["user_id"]

    # Query database for cash
    rows = db.execute("SELECT cash FROM users WHERE id = :id", id=id)

    if len(rows) == 0:
        return apology("sorry, you have no cash", 403)

    cash = rows[0]["cash"]

    return cash

# get number of shares in portfolio
def getNumSharesOwned(symbol):

    user_id = session["user_id"]
    numShares = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id and symbol = :symbol",
      user_id=session["user_id"], symbol=symbol)

    numShares = int(numShares[0]["sum(shares)"])
    print("347. numShares == " + str(numShares))

    return numShares


def isValidInput():

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            print("315. symbol == " + request.form.get("symbol"))
            return apology("must provide symbol", 403)

        # Ensure number of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 403)

        return True



