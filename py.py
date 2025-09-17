import csv
import sqlite3

# Crear base de datos
conn = sqlite3.connect("animes.db")
db = conn.cursor()

rating = "N/A"

db.execute("""
CREATE TABLE animes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    name TEXT,
    type TEXT,
    status TEXT,
    rating TEXT
)
""")


# Leer CSV y añadir user_id = 1
with open("animes.csv", newline='', encoding='utf-8-sig') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        db.execute("""
            INSERT INTO animes (user_id, name, type, status, rating)
            VALUES (?, ?, ?, ?, ?)
        """, (1, row["name"], row["type"], row["status"], rating))

# Guardar cambios
conn.commit()
conn.close()
