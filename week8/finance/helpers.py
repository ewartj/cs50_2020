import os
import requests
import urllib.parse
from flask_sqlalchemy import SQLAlchemy
from string import ascii_letters, digits
import pandas as pd

from flask import redirect, render_template, request, session
from functools import wraps

# configure CS50 Library to use SQLite database

def apology(message, code=400):
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
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
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
        api_key = os.environ.get("API_KEY")
        response = requests.get(f"https://cloud-sse.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

def SQLalchemy_query_pandas(query):
    """
    Takes a sqlalchemy resultProxy and converts it into a dataframe
    """
    df = pd.DataFrame(query.fetchall())
    df.columns = query.keys()
    return df

def resultProxy_2_dict(proxy):
    d, a = {}, []
    for rowproxy in proxy:
        # rowproxy.items() returns an array like [(key0, value0), (key1, value1)]
        for column, value in rowproxy.items():
            # build up the dictionary
            d = {**d, **{column: value}}
        a.append(d)
    return d

# def index_portfolio(df):
#     """
#     Input
#         Takes a df with 3 columns (stock, number and value)
#     Output
#         A db with X columns (adds company, cur_price, cur_total, total, profit)
#     """
#     ticker_name = df.loc[0, 'stock']
#     print("Ticker name:" + ticker_name)
#     print("Type " + str(type(ticker_name)))
#     print("Len " + ticker_name + ":" + str(len(ticker_name)))
#     print(df["stock"]) # write a test to check that the ticker_name is a single cell
#     stock = lookup(str(ticker_name))
#     print("STOCK name:")
#     print(stock)
#     df["company"] = stock["name"]
#     df["cur_price"] = stock["price"]
#     print(df)
#     print(df.shape)
#     print(df.dtypes)
#     df["cur_total"] = stock["price"] * df["number"]
#     df["total"] = df["value"]
#     df["profit"] = df["cur_total"] - df["total"]
#     return df

def hasNumbers(inputString):
    """
    From:
    https://stackoverflow.com/questions/31083503/how-do-i-check-if-a-string-contains-any-numbers
    """
    if any(str.isdigit(c) for c in inputString) == True:
        return True
    else:
        return False

def hasSpecialCharecters(inputString):
    if set(inputString).difference(ascii_letters + digits):
        return True
    else:
        return False


def index_add_currentdets(df):
    stocks = df["stock"].tolist()
    number = df["number"].tolist()
    value = df["value"].tolist()

    current_price = []
    profit = []
    current_total = []
    price_paid = []
    total = [] # I think this is
    for i in range(len(stocks)):
        stock = lookup(str(stocks[i]))
        pp = round((value[i] / number[i]),2)
        price_paid.append(pp)
        current_price.append(stock["price"])
        cur_total = stock["price"] * number[i]
        current_total.append(cur_total)
        total_paid = value[i] * number[i]
        total.append(total_paid)
        profit.append((stock["price"] - pp))
    df["price_paid"] = price_paid
    df["cur_price"] = current_price
    df["cur_total"] = current_total
    df["total"] = total
    df["profit"] = profit
    df = df.groupby(['stock']).mean()
    df.reset_index(inplace=True)
    return df

def index_comp_name(df):
    stocks = df["stock"].tolist()
    company = []

    for i in range(len(stocks)):
        stock = lookup(str(stocks[i]))
        company.append(stock["name"])

    df["company"] = company
    return df

def index_portfolio(df):
    """
    Input
        Takes a df with 3 columns (stock, number and value)
    Output
        A db with X columns (adds company, cur_price, cur_total, total, profit)
    """
    # for i in len(df
    # #ticker_name = df.lon[i, "stock"]
    ticker_name = df.loc[0, 'stock'] # This is the problem not always 0 need to make a list
    # of atock names
    print("Ticker name:" + ticker_name)
    print("Type " + str(type(ticker_name)))
    print("Len " + ticker_name + ":" + str(len(ticker_name)))
    print(df["stock"]) # write a test to check that the ticker_name is a single cell
    df = index_add_currentdets(df)
    print(df)
    df = index_comp_name(df)
    return df
    
