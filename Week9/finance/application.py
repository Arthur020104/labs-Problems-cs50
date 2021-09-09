import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    wallet = db.execute("SELECT * FROM wallet WHERE user_id = ? ORDER BY share DESC",session.get("user_id"))
    shareinfo = []
    pricetotal = []
    price = []
    for i in range(len(wallet)):
        shareinfo.append(lookup(wallet[i]['share']))
        pricetotal.append(round(wallet[i]['quantity'] * shareinfo[i]['price'], 2))
        price.append(shareinfo[i]['price'])
    i = -1
    return render_template("index.html", wallet=wallet, price=price, pricetotal=pricetotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    user_id = session.get("user_id")
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    if request.method == "GET":
        return render_template("buy.html",cash=cash[0]['cash'])
    if request.method == "POST":
        share = request.form.get("share").upper()
        quantity = int(request.form.get("quantity"))
        shareinfo = lookup(share)
        if shareinfo == None:
            return apology("Share does't exist")
        lost = float(shareinfo["price"]) * quantity
        if cash[0]['cash'] > lost :
            db.execute("UPDATE users SET cash = ? WHERE id = ?" ,float(cash[0]['cash']) - lost, user_id)
            todays_date = datetime.date.today()
            db.execute("INSERT INTO transactions(type, user_id, quantity, share, price, time) VALUES(?, ?, ?, ?, ?, ?)","buy", user_id, int(quantity), share, float(shareinfo["price"]), str(todays_date))
            wallet_quant = db.execute("SELECT quantity FROM wallet WHERE user_id = ? AND share = ?",user_id,str(share))
            if wallet_quant :#not NULL
                db.execute("UPDATE wallet SET quantity = ? WHERE user_id = ? AND share = ?",int(wallet_quant[0]["quantity"] + quantity), user_id, share)#wallet_quant[0]["quantity"] can only be acess if exist
                return render_template("buy.html",sharename = shareinfo["name"], quantity = quantity, lost = lost, shareprice = shareinfo["price"],cash=cash[0]['cash'])
            else:
                db.execute("INSERT INTO wallet (share, user_id, quantity, name) VALUES(?, ?, ?, ?)", share, user_id, quantity, shareinfo["name"])
                return render_template("buy.html",sharename = shareinfo["name"], quantity = quantity, lost = lost, shareprice = shareinfo["price"],cash=cash[0]['cash'])
        else:
            return apology("Your money isn't enough")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY id DESC", session.get("user_id"))
    return render_template("history.html",transactions = transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

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
    share = request.form.get("share")
    if request.method =="GET":
        return render_template("quote.html")
    if request.method =="POST":
        shares = lookup(share)
        if shares == None:
            return apology("Share-Code does not exist")
        return render_template("quote.html",shares=shares)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    username = request.form.get("username")
    password = request.form.get("password")
    passwordconf = request.form.get("confpassword")
    if password != passwordconf:
        return apology("The password and the confirm password are different", 403)
    #TODO passwordconf on js

    if request.method == "GET":
        return render_template("register.html")
    if request.method == "POST":
        if not len(db.execute("SELECT hash FROM users WHERE username=?",username)) != 0:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",username,generate_password_hash(password))
            return redirect('/')
        else:
            return apology("The username is already in use", 403)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    if request.method == "POST":
        share = request.form.get("share").upper()
        quantity = int(request.form.get("quantity"))
        user_id = session.get("user_id")
        shareinfo = lookup(share)
        if shareinfo == None:
            return apology("Share does't exist")
        profit = float(shareinfo["price"]) * quantity
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        wallet_quant = db.execute("SELECT quantity FROM wallet WHERE user_id = ? AND share = ?",user_id,str(share))
        if wallet_quant:#not NULL
            if wallet_quant[0]["quantity"] - quantity == 0:
                db.execute("UPDATE users SET cash = ? WHERE id = ?" ,float(cash[0]['cash']) + profit, user_id)
                todays_date = datetime.date.today()
                db.execute("INSERT INTO transactions(type, user_id, quantity, share, price, time) VALUES(?, ?, ?, ?, ?, ?)","sell", user_id, int(quantity), share, float(shareinfo["price"]), str(todays_date))
                db.execute("DELETE FROM wallet WHERE quantity = ? AND user_id = ? AND share = ?",int(wallet_quant[0]["quantity"]), user_id, share)#wallet_quant[0]["quantity"] can only be acess if exist
                return render_template("sell.html",sharename = shareinfo["name"], quantity = quantity, profit = profit, shareprice = shareinfo["price"])
            elif wallet_quant[0]["quantity"] >= quantity:
                db.execute("UPDATE users SET cash = ? WHERE id = ?" ,float(cash[0]['cash']) + profit, user_id)
                todays_date = datetime.date.today()
                db.execute("INSERT INTO transactions(type, user_id, quantity, share, price, time) VALUES(?, ?, ?, ?, ?, ?)","sell", user_id, int(quantity), share, float(shareinfo["price"]), str(todays_date))
                db.execute("UPDATE wallet SET quantity = ? WHERE user_id = ? AND share = ?",int(wallet_quant[0]["quantity"] - quantity), user_id, share)#wallet_quant[0]["quantity"] can only be acess if exist
                return render_template("sell.html",sharename = shareinfo["name"], quantity = quantity, profit = profit, shareprice = shareinfo["price"])
            else:
                return apology("You don't have this amount of shares")

        else:
            return apology("You don't have this share")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
#@for code in default_exceptions:
