import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from datetime import datetime
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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

    user_id = session["user_id"]

    transactions = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
        ORDER BY shares DESC""", user_id)

    row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = row[0]["cash"]

    rcash = float(cash)

    updated_transactions = []
    grand_total = 0

    for transaction in transactions:
        info = lookup(transaction["symbol"])
        price = info["price"]
        total = price * transaction["total_shares"]
        grand_total += total

        updated_transactions.append({
            "symbol": transaction["symbol"],
            "shares": transaction["total_shares"],
            "price": price,
            "total": total
        })

    final_total = grand_total + rcash

    return render_template("index.html", transactions=updated_transactions, rcash=rcash, final_total=final_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Must provide a symbol", 402)

        stock = lookup(symbol)
        if not stock:
            return apology("Must provide a valid symbol", 420)

        shares = request.form.get("shares")
        if not shares:
            return apology("Must provide a number", 430)

        current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        user_id = session["user_id"]

        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = row[0]["cash"]

        new_cash = cash - (stock["price"] * int(shares))
        if new_cash < 0:
            return apology("Insufficient money", 500)

        db.execute("""INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)""", user_id, stock['symbol'],
                   int(shares), stock['price'], current_time)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY time ASC", user_id)

    return render_template("history.html", transactions=transactions)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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

    if request.method == "GET":
        return render_template("quote.html")

    symbol = request.form.get("symbol").upper()
    if not symbol:
        return apology("Must provide a symbol", 300)

    stock = lookup(symbol)
    if not stock:
        return apology("Must provide a valid symbol, 420")

    return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Must provide an username")

        password = request.form.get("password")
        if not password:
            return apology("Must provide a password", 403)

        checkpassword = request.form.get("confirmation")
        if not checkpassword:
            return apology("Must provide a password", 403)

        elif password != checkpassword:
            return apology("Both password must be equals", 404)

        hashpassword = generate_password_hash(password)

        try:
            db.execute("""INSERT INTO users (username, hash) VALUES (?, ?)""",
                       username, hashpassword)
        except ValueError:
            return apology("Your username is taken", 405)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        user_id = session["user_id"]

        current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Must provide a symbol", 302)

        total_shares = db.execute("""
            SELECT SUM(shares) as total_shares FROM transactions
            WHERE user_id = ? AND symbol = ?
            """, user_id, symbol)

        shares = int(request.form.get("shares"))
        if not shares:
            return apology("Must provide a number", 407)
        elif shares > total_shares[0]["total_shares"]:
            return apology("You don't own that much", 201)

        info = lookup(symbol)

        new_cash = info["price"] * shares

        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = row[0]["cash"]

        new_cash = new_cash + cash

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        db.execute("""INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, ?)""", user_id, symbol, shares,
                   info["price"], current_time)

        return redirect("/")

    else:
        symbols = db.execute("""
            SELECT symbol FROM transactions
            WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0
            """, session["user_id"])

        return render_template("sell.html", transactions=symbols)


@app.route("/change", methods=["GET", "POST"])
def change_password():

    if request.method == "POST":

        users = db.execute("SELECT username FROM users")

        username = request.form.get("username")
        if not username:
            return apology("Must provide an username")

        elif username not in users[0]["username"]:
            return apology("You are not registered yet")

        hash = db.execute("SELECT hash FROM users WHERE username = ?", username)

        password = request.form.get("newpassword")
        if not password:
            return apology("Must provide a new password")

        elif check_password_hash(hash[0]["hash"], password):
            return apology("This is your password already")

        checkpassword = request.form.get("newpassword2")
        if not checkpassword:
            return apology("Must provide a password (again)")

        elif password != checkpassword:
            return apology("Both passwords must be equals")

        hashpassword = generate_password_hash(password)

        db.execute("""UPDATE users SET hash = ? WHERE username = ?""", hashpassword, username)

        return redirect("/login")

    return render_template("forgot_password.html")
