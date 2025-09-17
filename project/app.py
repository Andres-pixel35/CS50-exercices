import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for, send_file
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import requests
from markupsafe import escape

from helpers import login_required

app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///project.db")

mydb = SQL("sqlite:///animes.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == 'POST':
        title = request.form['query']

        search_type = request.form['type']

        return redirect(url_for('result', title=title, type=search_type))
    return render_template('index.html')

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            flash("Invalid username and/or password.")
            return render_template("login.html")

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

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")

        password = request.form.get("password")

        checkpassword = request.form.get("confirmation")

        if password != checkpassword:
            flash("Passwords do not match.")
            return redirect('/register')

        hashpassword = generate_password_hash(password)

        try:
            db.execute("""INSERT INTO users (username, hash) VALUES (?, ?)""",
                       username, hashpassword)
        except ValueError:
            flash("Username alreadty exists")
            return redirect('/register')

        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/newpassword", methods=["GET", "POST"])
def change_password():

    if request.method == "POST":

        users = db.execute("SELECT username FROM users")

        username = request.form.get("username")

        if username not in users[0]["username"]:
            flash("You are not registered yet.")
            return render_template("forgot_password.html")

        hash = db.execute("SELECT hash FROM users WHERE username = ?", username)

        password = request.form.get("newpassword")

        if check_password_hash(hash[0]["hash"], password):
            flash("This is already your password.")
            return render_template("forgot_password.html")

        checkpassword = request.form.get("confirmation")

        if password != checkpassword:
            flash("Both password must be equals.")
            return render_template("forgot_password.html")

        hashpassword = generate_password_hash(password)

        db.execute("""UPDATE users SET hash = ? WHERE username = ?""", hashpassword, username)

        return redirect("/login")

    return render_template("forgot_password.html")

@app.route('/result')
@login_required
def result():
    title = request.args.get('title')
    search_type = request.args.get('type')

    results = search_anilist_multiple(title, search_type)

    # If results is a response (send_file), return it directly
    if hasattr(results, 'status_code'):
        return results

    return render_template('results_list.html', results=results, search_type=search_type)


def search_anilist_multiple(title, media_type):
    query = '''
    query ($search: String, $type: MediaType) {
      Page(perPage: 10) {
        media(search: $search, type: $type) {
          id
          title {
            english
            romaji
          }
          coverImage {
            medium
          }
          type
        }
      }
    }
    '''
    media_map = {
        'anime': 'ANIME',
        'manga': 'MANGA',
    }

    variables = {'search': title, 'type': media_map.get(media_type)}
    response = requests.post('https://graphql.anilist.co', json={'query': query, 'variables': variables})
    data = response.json().get('data', {}).get('Page', {}).get('media', [])

    if not data:
        return send_file('static/error_message.png', mimetype='image/png')

    return data  # list of media dicts


@app.route('/details/<int:media_id>')
@login_required
def details(media_id):
    # Fetch detailed info for selected media by ID
    query = '''
    query ($id: Int) {
      Media(id: $id) {
        title {
          romaji
        }
        description(asHtml: true)
        coverImage {
          large
        }
        type
      }
    }
    '''
    variables = {'id': media_id}
    response = requests.post('https://graphql.anilist.co', json={'query': query, 'variables': variables})
    data = response.json().get('data', {}).get('Media', None)

    if not data:
        return send_file('static/error_message.png', mimetype='image/png')

    result = {
        'title': data['title']['romaji'],
        'image': data['coverImage']['large'],
        'description': data['description'],
        'type': data['type'].capitalize()
    }

    return render_template('result.html', result=result)


@app.route('/library', methods=["GET", "POST"])
@login_required
def library():

    user_id = session["user_id"]

    if user_id == 1:
        db = mydb
    else:
        db = SQL("sqlite:///project.db")


    if request.method == "POST":

        deletetype = request.form.get("deletetype")

        deletework = request.form.get("deletework")
        if deletework is not None:

            delete_exists = db.execute("SELECT * FROM animes WHERE user_id = ? AND LOWER(name) = LOWER(?) and type = ?", user_id, deletework, deletetype)
            if not delete_exists:
                flash(f'"{escape(deletework)}" ({escape(deletetype)}) does not exists in yout library', "error_work_donot_exists")


            db.execute("DELETE FROM animes WHERE LOWER(name) = LOWER(?) AND user_id = ? AND type = ?", deletework, user_id, deletetype)
            return redirect("/library")

        title = request.form.get("title").title()

        type = request.form.get("type")

        status = request.form.get("status")
        if not status:
            status = "Unknown"

        rating = request.form.get("rating")
        if rating:
            try:
                rating = int(rating)
            except ValueError:
                return redirect("/library")
        else:
            rating = "N/A"


        exists = db.execute("SELECT * FROM animes WHERE user_id = ? AND LOWER(name) = LOWER(?) AND type = ?", user_id, title, type)
        if exists:
            flash(f'"{escape(title)}" ({escape(type)}) is already in your library.', "error_work_exists")
            return redirect("/library")

        db.execute("""INSERT INTO animes (user_id, name, type, status, rating) VALUES (?, ?, ?, ?, ?)""", user_id, title, type, status, rating)

        return redirect("/library")

    filter_type = request.args.get("filter_type")
    filter_status = request.args.get("filter_status")
    sort = request.args.get("sort")
    order = request.args.get("order", "asc").lower()

    query = "SELECT * FROM animes WHERE user_id = ?"
    params = [user_id]

    if filter_type:
        query += " AND type = ?"
        params.append(filter_type)

    if filter_status:
        query += " AND status = ?"
        params.append(filter_status)

    if sort == "rating":
        if order == "desc":
            query += " ORDER BY rating DESC"
        else:
            query += " ORDER BY rating ASC"

    animes = db.execute(query, *params)
    return render_template("library.html", animes=animes)

@app.route('/library/update', methods=['POST'])
@login_required
def update_work():

    user_id = session["user_id"]

    if user_id == 1:
        db = mydb
    else:
        db = SQL("sqlite:///project.db")

    title = request.form.get('title')
    work_type = request.form.get('type')
    new_status = request.form.get('status')
    new_rating = request.form.get('rating')

    if not new_status:
        new_status = "Unknown"

    if new_rating:
        try:
            new_rating = int(new_rating)
        except ValueError:
            flash("Invalid rating value", "update_error")
            return redirect("/library")

    else:
        new_rating = "N/A"


    work = db.execute("SELECT * FROM animes WHERE user_id = ? AND LOWER(name) = LOWER(?) AND type = ?", user_id, title, work_type)
    if not work:
        flash(f'"{escape(title)}" ({escape(work_type)}) does not exists in your library, yet', "update_error")
        return redirect("/library")

    db.execute("UPDATE animes SET status = ?, rating = ? WHERE user_id = ? AND LOWER(name) = LOWER(?) AND type = ?", new_status, new_rating, user_id, title, work_type)

    flash(f'"{escape(title)}" ({escape(work_type)}) updated successfully', "update_success")

    return redirect(url_for('library'))






