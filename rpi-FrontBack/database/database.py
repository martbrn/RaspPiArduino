import sqlite3 as lite
import sys
con = lite.connect('projectrpi.db')
with con: 
    cur = con.cursor() 
    cur.execute("DROP TABLE IF EXISTS DISPOSITIVES")
    cur.execute("CREATE TABLE DISPOSITIVES(id integer PRIMARY KEY AUTOINCREMENT, name text NOT NULL, timestamp DATETIME)")
