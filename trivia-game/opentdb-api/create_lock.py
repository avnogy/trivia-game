import sqlite3
import sys

OPENTDB_URL = r'https://opentdb.com/api.php?amount=3&type=multiple&encode=base64'
DATABASE_PATH = sys.argv[1] if len(sys.argv) > 1 else r"..\\"
DATABASE_PATH += r"bin\database.sqlite"

def create_marker():
    with open(DATABASE_PATH+".lock","w") as lockfile:
        lockfile.write("locked")

def clean():
    #openning database
    conn = sqlite3.connect(DATABASE_PATH)
    database = conn.cursor()

    #cleaning the questions
    database.execute('DELETE FROM questions;') 

    #commiting changes to database
    conn.commit()
    conn.close()

if __name__ == '__main__':
    clean()
    create_marker()