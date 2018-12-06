import os
import re
from flask import Flask, jsonify, render_template, request

from cs50 import SQL
from helpers import lookup

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render map"""
    return render_template("index.html")


@app.route("/articles")
def articles():
    """Look up articles for geo"""

    # TODO
    # return jsonify([])

    # source http://flask.pocoo.org/docs/1.0/api/#module-flask.json
    return jsonify(lookup(request.args.get('geo'))[:5])


@app.route("/search")
def search():
    """Search for places that match query"""

    print("\n44. inside search()")

    # TODO
    # return jsonify([])

    # source https://docs.cs50.net/2018/x/psets/8/mashup/mashup.html
    q = request.args.get("q") + "%"
    # data = db.execute("SELECT * FROM places \
    #     WHERE place_name LIKE :q \
    #     OR admin_code1 LIKE :q \
    #     OR admin_name1 LIKE :q \
    #     OR postal_code LIKE :q", q=q)
    data = db.execute("""SELECT * FROM places
        WHERE place_name LIKE :q
        OR admin_code1 LIKE :q
        OR admin_name1 LIKE :q
        OR postal_code LIKE :q""", q=q)
    print("61. data == ", data[0])
    return jsonify(data)


@app.route("/update")
def update():
    """Find up to 10 places within view"""

    print("63. inside update()...")
    # Ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # Ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # Explode southwest corner into two variables
    sw_lat, sw_lng = map(float, request.args.get("sw").split(","))
    print(sw_lat, sw_lng)

    # Explode northeast corner into two variables
    ne_lat, ne_lng = map(float, request.args.get("ne").split(","))
    print(ne_lat, ne_lng)

    # Find 10 cities within view, pseudorandomly chosen if more within view
    if sw_lng <= ne_lng:
        print("sw_lng <= ne_lng")
        # Doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng >= longitude AND longitude >= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    else:
        print("sw_lng !<= ne_lng")
        # Crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # Output places as JSON
    print("\n103. ")
    print(jsonify(rows))
    # print(rows)
    return jsonify(rows)
