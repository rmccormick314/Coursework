#Final project for CS 345
#Created by Richard McCormick (RLM443)

#INSTRUCTIONS:
#Most of the program is fairly self-explanatory.
#Running this file with Python will launch the program.
#There is a user menu that can be used to navigate the database.
#An automated demo has been added to showcase the
#various features.

#unfinished

#Program initialization
#Import SQLite3 and error handling
import sqlite3
from sqlite3 import Error

#Create variables for working with database
#Conn variable allows connection to database
conn = sqlite3.connect('Project.db')
#Cur variable creates cursor for database
cur = conn.cursor()

#Functions for making certain things easier

#Create a connection to a given database
def create_connection(db_file):
    print("Connecting to Database File...")
    #Clears connection var, attempts to establish
    #new connection to given file.
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        #Successful connection produces output
        print("Connected to Database File: " + db_file)
    except Error as e:
        #If connection fails, print error code.
        print(e)
    #Return new conn variable with database connected
    print("")
    return conn

#Creates two new tables, one for hottest actresses,
#and one for hottest actors.
def initialize_tables():
    #Attempts to initialize tables, if they
    #do not already exist.
    print("Initializing tables...")
    try:
        #Names are used as primary key, and unique values.
        #Creates actresses table.
        cur.execute('''CREATE TABLE IF NOT EXISTS Actresses(
                    Name TEXT, Age INT,
                    Body INT, Personality INT, Composite INT,
                    Career TEXT,
                    UNIQUE(Name)
                    )''')
        #Confirmation message
        print("'Actresses' table initialized.")

        #Creates actors table.
        cur.execute('''CREATE TABLE IF NOT EXISTS Actors(
                    Name TEXT, Age INT,
                    Body INT, Personality INT, Composite INT,
                    Career TEXT,
                    UNIQUE(Name)
                    )''')
        #Confirmation message
        print("'Actors' table initialized.")

        #Create a table for different types of actors
        cur.execute('''CREATE TABLE IF NOT EXISTS Careers(
                    Career TEXT, UNIQUE(Career))''')

        #Create a table for potential celebrity couples
        cur.execute('''CREATE TABLE IF NOT EXISTS Couples(
                    PersonOne TEXT, PersonTwo TEXT, CombinedScore INT
        )''')

        #Create a table with all people in one place. Should have
        #done this in the first place.
        cur.execute('''CREATE TABLE IF NOT EXISTS All_Celebrities(
                    Name TEXT, AGE INT, Body INT, Personality INT,
                    Composite INT, Career TEXT, UNIQUE(Name)
        )''')

        #Commit changes to database
        conn.commit()

    #If tables already exist, or there is another error,
    #dump information to console.
    except Error as e:
        print(e)

    #Confirmation message
    print("All tables initialized.")
    print("")

#Function for populating tables for the first time.
def populate_tables():
    #Attempts to populate tables with values
    print("Populating database.")
    try:
        #Populates actresses
        cur.execute('''
              INSERT INTO Actresses (Name, Age, Body, Personality)
                    VALUES
                    ('Scarlett Johansson', 38, 9, 9),
                    ('Emma Watson', 31, 8, 10),
                    ('Selena Gomez', 29, 9, 7),
                    ('Michelle Rodriguez', 43, 7, 10),
                    ('Emily Blunt', 38, 9, 9)
              ''')
        #Confirmation message
        print("'Actresses' table populated.")

        #Populates actors
        cur.execute('''
              INSERT INTO Actors (Name, Age, Body, Personality)
                    VALUES
                    ('Tiny Tom Cruise', 59, 9, 8),
                    ('George Clooney', 60, 8, 9),
                    ('Chris Pratt', 42, 9, 10),
                    ('Matt Damon', 51, 9, 7),
                    ('Alec Baldwin', 63, 9, 3)
              ''')
        #Confirmation message
        print("'Actors' table populated.")

        #Populates career types. Each person can have multiple
        cur.execute('''
            INSERT INTO Careers (Career)
                VALUES
                ('Director'),
                ('Actor'),
                ('Producer')
        ''')
        print("'Careers' table populated.")

        #Compiles all actresses into the All table
        query = cur.execute('''SELECT * FROM Actresses''')
        entries = cur.fetchall()
        for row in entries:
            name = row[0]
            age = row[1]
            body = row[2]
            personality = row[3]
            composite = row[4]
            career = row[5]
            cur.execute('''INSERT INTO All_Celebrities(Name, Age, Body,
            Personality, Composite, Career)
                VALUES
                (?, ?, ?, ?, ?, ?)
            ''', (name, age, body, personality, composite, career))

        #Compiles all actors into the All table
        query = cur.execute('''SELECT * FROM Actors''')
        entries = cur.fetchall()
        for row in entries:
            name = row[0]
            age = row[1]
            body = row[2]
            personality = row[3]
            composite = row[4]
            career = row[5]
            cur.execute('''INSERT INTO All_Celebrities(Name, Age, Body,
            Personality, Composite, Career)
                VALUES
                (?, ?, ?, ?, ?, ?)
            ''', (name, age, body, personality, composite, career))

        #Commits new info to database
        conn.commit()
        print("Database populated.")

    #Throws error if already populated.
    except Error as e:
        print(e)

def set_composite_score():
    #Gets the body and personality score from each person,
    #and averages it into a composite score
    query = cur.execute('''SELECT * FROM Actresses''')
    entries = cur.fetchall()
    for row in entries:
        print(row[0])
        composite_score = (row[2]+row[3])/2;
        update_entry("Actresses", row[0], "Composite", composite_score)

    #Same as above
    query = cur.execute('''SELECT * FROM Actors''')
    entries = cur.fetchall()
    for row in entries:
        print(row[0])
        composite_score = (row[2]+row[3])/2;
        update_entry("Actresses", row[0], "Composite", composite_score)



#Function for getting all data from both tables,
#and printing to console.
def get_all_tables_data():
    print("Getting database entries...")
    print("")
    print("ACTRESSES")
    print("NAME, AGE, BODY SCORE, PERSONALITY SCORE")
    #Sets up a query for all entries
    query = cur.execute('''SELECT * FROM Actresses''')
    entries = cur.fetchall()
    print()
    #Prints every entry in table 'Actresses'
    for row in entries:
        print(row)

    print("")
    print("ACTORS")
    print("NAME, AGE, BODY SCORE, PERSONALITY SCORE")
    #Set up a new query
    query = cur.execute('''SELECT * FROM Actors''')
    entries = cur.fetchall()
    print()
    #Print all information in table 'Actors'
    for row in entries:
        print(row)

def add_entry(Table, Name, Age, BodyScore, PersonalityScore):
    #Selects table based on user input
    if (Table == "ACTOR"):
        #Adds person to database
        cur.execute('''
              INSERT INTO Actors (Name, Age, Body, Personality)
                    VALUES(?, ?, ?, ?)
              ''', (Name, Age, BodyScore, PersonalityScore))
    if (Table == "ACTRESS"):
        #Adds person to database
        cur.execute('''
              INSERT INTO Actresses (Name, Age, Body, Personality)
                    VALUES(?, ?, ?, ?)
              ''', (Name, Age, BodyScore, PersonalityScore))
    print("")
    print("Entry successfully added.")
    conn.commit()

def remove_entry(Name):
    #Attempts to remove person from database
    try:
        #Tries to remove from Actors table
        cur.execute('''
            DELETE FROM Actors WHERE name =?
        ''', (Name,))
    except Error as e:
        print(e)

    try:
        #Tries to remove from Actresses table
        cur.execute('''
            DELETE FROM Actresses WHERE name =?
        ''', (Name,))
    except Error as e:
        print(e)

    print("")
    print("Entry [" + Name + "] removed.")
    conn.commit()

def run_query(name):
    try:
        query = cur.execute('''
            SELECT * FROM Actors WHERE Name=?
        ''', (name,))
        entries = cur.fetchall()
        print()
        #Prints every entry in table 'Actors'
        for row in entries:
            print(row)
    except Error as e:
        print(e)

    try:
        query = cur.execute('''
            SELECT * FROM Actresses WHERE Name=?
        ''', (name,))
        entries = cur.fetchall()
        print()
        #Prints every entry in table 'Actors'
        for row in entries:
            print(row)
    except Error as e:
        print(e)

def update_entry(table, entry_name, field_update, field_info):
    if (table == "Actresses"):
        if (field_update == "Name"):
            cur.execute('''UPDATE Actresses SET Name = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Age"):
            cur.execute('''UPDATE Actresses SET Age = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Body"):
            cur.execute('''UPDATE Actresses SET Body = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Personality"):
            cur.execute('''UPDATE Actresses SET Personality = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Composite"):
            cur.execute('''UPDATE Actresses SET Composite = ? WHERE Name = ?''',
            (field_info, entry_name))

    if (table == "Actors"):
        if (field_update == "Name"):
            cur.execute('''UPDATE Actors SET Name = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Age"):
            cur.execute('''UPDATE Actors SET Age = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Body"):
            cur.execute('''UPDATE Actors SET Body = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Personality"):
            cur.execute('''UPDATE Actors SET Personality = ? WHERE Name = ?''',
            (field_info, entry_name))
        if (field_update == "Composite"):
            cur.execute('''UPDATE Actors SET Composite = ? WHERE Name = ?''',
            (field_info, entry_name))

    conn.commit()

def run_demo():
    create_connection('Project.db')
    print(conn)
    initialize_tables()
    populate_tables()
    get_all_tables_data()
    add_entry("ACTORS", "John Cena", 69, 10, 10)
    run_query("John Cena")
    remove_entry("John Cena")
    get_all_tables_data()

#Main function, contains container for all other functions.
#Also contains simple menu for navigation, etc.
def run_main():
    print()
    print("Welcome to the Database for Hottest Celebrities!")
    menu_select = 0

    while (menu_select != str(9)):
        menu_select = 0
        print("")
        print("=============================================")
        print("1. Connect, Initialize, and Populate Database")
        print("2. Print Database")
        print("")
        print("4. Add, Update, or Remove Entry")
        print("5. Run query")
        print("6. Generate Composite Scores & Couples")
        print("")
        print("8. Run automated demonstration (Recommended)")
        print("9. Exit")
        print("=============================================")

        print("")
        menu_select = input("Select an Option: ")
        print("")
        #Manually initialize connection to database.
        if (menu_select == str(1)):
            create_connection("Project.db")
            print(conn)
            initialize_tables()
            populate_tables()

        #Manually print all table entries into console.
        if (menu_select == str(2)):
            get_all_tables_data()

        if (menu_select == str(4)):
            print("")
            #Determine if user wants to add or remove an entry
            add_or_remove = None
            while (add_or_remove not in ("ADD", "REMOVE", "UPDATE")):
                #Loops until user selects a valid choice
                add_or_remove = input("ADD, UPDATE, REMOVE entry?: ")
                if (add_or_remove not in ("ADD", "REMOVE", "UPDATE")):
                    print("Please select valid option.")
                    print()

            #If user wants to add entry, get entry data
            if (str(add_or_remove) == "ADD"):
                table_select = None
                #Get whether entry is an actor or actress
                while (table_select not in ("ACTOR", "ACTRESS")):
                    #Loops until user selects valid choice
                    table_select = input("Are you adding an ACTOR or ACTRESS?: ")
                    if (table_select not in ("ACTOR", "ACTRESS")):
                        print("Please select valid option.")
                        print()

                #Gets name of entry
                new_name = input("Please type " + table_select + "'s name: ")
                #Gets age of entry
                new_age = input("Please type " + new_name + "'s age: ")

                #Gets body score of entry. Must be between 1 and 10
                new_body_score = -1;
                while (int(new_body_score) > 10 or int(new_body_score) < 1):
                    #If score is outside given range, prompt for new score
                    new_body_score = input("Please type " + new_name + "'s body score (1 to 10): ")
                    if (int(new_body_score) > 10 or int(new_body_score) < 1):
                        print("Please select valid option.")
                        print()

                #Gets personality score of entry. Must be between 1 and 10
                new_personality_score = -1;
                while (int(new_personality_score) > 10 or int(new_personality_score) < 1):
                    #If score is outside given range, prompt for new score.
                    new_personality_score = input("Please type " + new_name + "'s personality score (1 to 10): ")
                    if (int(new_personality_score) > 10 or int(new_personality_score) < 1):
                        print("Please select valid option.")
                        print()

                #Once all data is given, run function to add entry to
                #corresponding data table.
                add_entry(table_select, new_name, new_age, new_body_score, new_personality_score)

            if (str(add_or_remove) == "REMOVE"):
                #If user wants to remove entry, ask for entry name.
                remove_entry_name = input("Type name of entry to remove: ")
                #With name, run function to remove name.
                remove_entry(remove_entry_name)

            if (str(add_or_remove) == "UPDATE"):
                update_entry_name = input("Type name of entry to update: ")
                update_entry_field = input("Type name of field to update: ")
                update_entry_data = input("Type new value for "+update_entry_field+": ")
                update_entry_table = input("Type table name for entry: ")
                update_entry(update_entry_table, update_entry_name,
                update_entry_field, update_entry_data)

        if (menu_select == str(5)):
            print("")
            query_select = input("Select name of entry to search for: ")
            run_query(query_select)

        if (menu_select == str(6)):
            set_composite_score()


        #Run an automated demonstration of all key functions.
        if (menu_select == str(8)):
            run_demo()

run_main()
