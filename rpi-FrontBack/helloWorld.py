from flask import Flask, render_template
from flask import request, redirect
import datetime
from smbus import SMBus
import sqlite3
from flask import g
import sys

addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1
numb = 1

DATABASE = './database/projectrpi.db'

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    return db

def query_db(query, args=(), one=False):
    conection = get_db()
    cur = conection.execute(query, args)
    rv = cur.fetchall()
    cur.close()
    conection.commit()
    return (rv[0] if rv else None) if one else rv

app = Flask(__name__)
@app.route("/",methods=['GET', 'POST'])
def hello():

    rows = query_db('SELECT * FROM DISPOSITIVES')

    list = [
        {'a': 1, 'b': 2},
        {'a': 5, 'b': 10}
    ]
   
    return render_template('index.html', dispositives=rows)
    

@app.route("/addDispositive", methods=['GET', 'POST'])
def addDispositive():
    if request.method == 'POST':
        name = request.form['inputnombre']
        description = request.form['inputdescripcion']
        model = request.form['inputmodelo']
        diri2c='0x8'
        response = query_db('INSERT INTO BOARD (Name,Description,Dir_I2C,Model) VALUES("'+ name + '","' + description +'","' + diri2c + '","' + model +'")')
    return render_template('addDispositive.html')
   
@app.route("/<deviceName>/<action>")
def action(deviceName, action):   
    if action == "on":
        bus.write_byte(addr, 1) # switch it ON
    if action == "off":
        bus.write_byte(addr, 0) # switch it OFF
    return render_template('index.html')

if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80, debug=True)
