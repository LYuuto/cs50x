import os

from cs50 import SQL
from flask import Flask, render_template, request, session
from tempfile import mkdtemp
from datetime import datetime

from helpers import sessiontime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///files.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
def index():

    return render_template("index.html")

@app.route("/services", methods=["GET"])
def services():

    return render_template("services.html")

@app.route("/booking-dates", methods=["GET", "POST"])
def date():

    if request.method == "POST":

        db.execute("DELETE FROM temp")

        if not request.form.get("date"):
            return render_template("errorform.html")

        date = request.form.get("date")
        sessionlist = db.execute("SELECT session FROM bookings WHERE date = ?;", date)
        session =[]
        for i in range(len(sessionlist)):
            session.append(sessionlist[i]['session'])
        db.execute("INSERT INTO temp VALUES (?);", date)
        return render_template("booking.html", date = date, takensession = session)
    else:
        db.execute("DELETE FROM temp")
        return render_template("date.html")



@app.route("/booking", methods=["GET", "POST"])
def booking():

    if request.method == "POST":
        if not request.form.get("name"):
            return render_template("errorform.html")
        name = request.form.get("name")

        date = db.execute("SELECT * FROM temp")[0]['date']

        if not request.form.get("session"):
            return render_template("errorform.html")
        session = request.form.get("session")

        if not request.form.get("mail"):
            return render_template("errorform.html")
        mail = request.form.get("mail")

        note = request.form.get("note")

        db.execute("DELETE FROM temp;")
        db.execute("INSERT INTO bookings (name, date, session, email, note) VALUES(?, ?, ?, ?, ?)", name, date, session, mail, note)
        data = db.execute("SELECT id, session, date FROM bookings WHERE name=? and date=? and session=? and email=? and note=?;", name, date, session, mail, note)

        datalist = []

        datalist.append(data[0]['id'])
        datalist.append(data[0]['date'])

        date = sessiontime(data[0]['session'])

        datalist.append(date)
        print(datalist)

        return render_template("booked.html", data = datalist)

    else:
        return render_template("date.html")

@app.route("/about", methods=["GET"])
def contact():

    return render_template("about.html")

@app.route("/check", methods=["GET", "POST"])
def check():

    if request.method == "POST":
        if not request.form.get("id"):
            return render_template("errorform.html")
        id = request.form.get("id")

        if not request.form.get("mail"):
            return render_template("errorform.html")
        mail = request.form.get("mail")

        row = db.execute("SELECT * FROM bookings WHERE id = ? and email = ?;", id, mail)

        if len(row) != 1:
            return render_template("check.html")

        else:
            dbid = row[0]['id']
            dbname = row[0]['name']
            dbdate = row[0]['date']
            dbsession = sessiontime(row[0]['session'])
            dbmail = row[0]['email']
            dbnote = row[0]['note']

            ls = [dbid, dbname, dbdate, dbsession, dbmail, dbnote]


        return render_template("checkbook.html", ls = ls)

    else:
        return render_template("check.html")






