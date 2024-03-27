import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ? ORDER BY symbol", session["user_id"])
    symbol_dic = {}
    all_total = 0

    count = 0
    for symbol in symbols:

        s = symbols[count]["symbol"]
        number = db.execute("SELECT SUM(shares) as ? FROM transactions WHERE user_id = ? AND symbol = ?", s, session["user_id"], s)

        if number[0][s] > 0:
            price = lookup(s)['price']
            name = lookup(s)['name']
            total = price * number[0][s]

            all_total += total

            price = usd(price)
            total = usd(total)

            symbol_dic.update({s: [name, number[0][s], price, total]})
            count += 1

        else:
            count += 1

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
    all_total += cash
    cash = usd(cash)
    all_total = usd(all_total)

    return render_template("index.html", symbol_dic=symbol_dic, cash=cash, total=all_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        result = lookup(request.form.get("symbol"))

        if result == None:
            return apology("Invalid symbol", 400)

        else:
            if not request.form.get("shares"):
                return apology("must provide shares", 400)

            if not request.form.get("shares").isdigit():
                return apology("Invalid shares", 400)

            shares = request.form.get("shares")
            cost = result["price"] * int(shares)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = float(cash[0]['cash'])

            if cash < cost:
                return apology("Not enough cash", 400)

            remain = cash - cost
            time = datetime.now()
            db.execute("INSERT INTO transactions(user_id, symbol, shares, time, total) VALUES (?, ?, ?, ?, ?)",
                       session["user_id"], request.form.get("symbol").capitalize(), shares, time, cost)
            db.execute("UPDATE users SET cash=? WHERE id=?", remain, session["user_id"])
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    data = db.execute("SELECT symbol, shares, total, time FROM transactions WHERE user_id=?", session["user_id"])

    for item in data:
        item['total'] = usd(item['total'])

    return render_template("history.html", data=data)


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

    if request.method == "POST":
        symbol = request.form.get("symbol").capitalize()

        result = lookup(symbol)

        if result == None:
            return apology("Invalid symbol", 400)

        else:
            result["price"] = usd(result["price"])
            return render_template("quoted.html", result=result)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must re-confirm the password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must match the passwords", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("invalid username", 400)

        name = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, hash)

        rows = db.execute("SELECT * FROM users WHERE username = ?", name)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        symbol = request.form.get("symbol").capitalize()
        result = lookup(symbol)

        if not request.form.get("shares"):
            return apology("must provide shares", 400)

        if not request.form.get("shares").isdigit():
            return apology("Invalid shares", 400)

        shares = int(request.form.get("shares"))

        shares_have = db.execute("SELECT SUM(shares) as sum_shares FROM transactions WHERE user_id=? and symbol=?",
                                 session["user_id"], symbol)[0]['sum_shares']

        if shares > shares_have:
            return apology("Not enough shares", 400)

        else:
            sell_price = result["price"] * int(shares)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = float(cash[0]['cash'])

            remain = cash + sell_price
            time = datetime.now()

            shares = -abs(shares)

            db.execute("INSERT INTO transactions(user_id, symbol, shares, time, total) VALUES (?, ?, ?, ?, ?)",
                       session["user_id"], symbol, shares, time, sell_price)
            db.execute("UPDATE users SET cash=? WHERE id=?", remain, session["user_id"])

            return redirect("/")

    else:

        symbols = db.execute("SELECT DISTINCT symbol  FROM transactions WHERE user_id = ?", session["user_id"])
        symbol_ls = []
        count = 0
        for symbol in symbols:

            s = symbols[count]["symbol"]

            number = db.execute("SELECT SUM(shares) as sum_shares FROM transactions WHERE user_id=? and symbol=?",
                                session["user_id"], s)[0]['sum_shares']
            if number > 0:
                symbol_ls.append(s)
                count += 1
            else:
                count += 1

        return render_template("sell.html", symbol_ls=symbol_ls)


@app.route("/changepw", methods=["GET", "POST"])
def changepw():
    """Change password"""

    if request.method == "POST":

        if not request.form.get("old_pw"):
            return apology("must provide current password", 403)
        if not request.form.get("new_pw"):
            return apology("must provide new password", 403)
        if not request.form.get("cfm_pw"):
            return apology("must reconfirm the new password", 403)

        rows = db.execute("SELECT * FROM users WHERE id=?", session['user_id'])
        if not check_password_hash(rows[0]["hash"], request.form.get("old_pw")):
            return apology("wrong current password", 403)

        if request.form.get("new_pw") != request.form.get("cfm_pw"):
            return apology("must match the passwords", 403)

        hash = generate_password_hash(request.form.get("new_pw"))

        db.execute("UPDATE users SET hash=? WHERE id=?", hash, session['user_id'])

        return redirect("/")

    else:
        return render_template("chgpw.html")

