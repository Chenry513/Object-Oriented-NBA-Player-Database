import sqlite3
import json

# Connect to the SQLite database
conn = sqlite3.connect('playerdata.db')
c = conn.cursor()

# Create the table
c.execute('''
CREATE TABLE IF NOT EXISTS Players (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    Team TEXT NOT NULL,
    Position TEXT,
    Salary INTEGER,
    JerseyNumber INTEGER,
    RookieYear INTEGER
);
''')

# Open and load the JSON file
with open('nba_players.json') as file:
    players = json.load(file)

# Insert data into the database
for player in players:
    c.execute('''
        INSERT INTO Players (Name, Team, Position, Salary, JerseyNumber, RookieYear)
        VALUES (?, ?, ?, ?, ?, ?)
    ''', (player['name'], player['team'], player['position'], player['salary'], player['number'], player['draft_year']))

# Commit the changes and close the connection
conn.commit()
conn.close()
