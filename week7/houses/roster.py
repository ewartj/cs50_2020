import pandas as pd
from sys import argv, exit
from sqlalchemy import create_engine

def main():
    if len(argv) != 2:
        print("Please provide a csv file")
        exit(1)

query_name = argv[1]

engine = create_engine("sqlite:///students.db", echo=False)

# Idea of using pandas from:
# https://hackersandslackers.com/connecting-pandas-to-a-sql-database-with-sqlalchemy/

df = pd.read_sql_query(f"SELECT  * FROM students WHERE house == '{query_name}' ORDER BY last, first;",  con=engine)

df["name"] = df["first"] + " " + df["middle"] + " " + df["last"]

# removing Null
# https://stackoverflow.com/questions/23669024/how-to-strip-a-specific-word-from-a-string
df['name'] = df['name'].str.replace("Null ", "")

# combining all the important info into a single column
# https://stackoverflow.com/questions/22005911/convert-columns-to-string-in-pandas
df["Answer"] = df["name"] + ", born " + df["birth"].astype(str)

answer_list = df["Answer"].tolist()

for i in answer_list:
    print(i)