import pandas as pd
from sys import argv, exit
import sqlalchemy

def main():
    if len(argv) != 2:
        print("Please provide a csv file")
        exit(1)

df = pd.read_csv(argv[1])

# split the full name into seperate names

first_name = []
second_name = []
last_name = []

full_name = df.name.tolist()

for i in range(len(full_name)):
    name_list = full_name[i].split(" ")
    if len(name_list) == 2:
        first = name_list[0]
        second = "Null"
        third = name_list[1]
    else:
        first = name_list[0]
        second = name_list[1]
        third = name_list[2]
    first_name.append(first)
    second_name.append(second)
    last_name.append(third)

df["first"] = first_name
df["middle"] = second_name
df["last"] = last_name

df.drop(columns="name", inplace = True)

# converted pandas dataframe to an sqlite file
# From:
# https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.to_sql.html

from sqlalchemy import create_engine
engine = create_engine("sqlite:///students.db", echo=False)
df.to_sql('students', con=engine, if_exists='replace')
print(engine.execute("SELECT * FROM students").fetchall())

main()
