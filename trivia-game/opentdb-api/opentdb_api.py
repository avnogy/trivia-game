import requests, json, sqlite3, base64
import sys

OPENTDB_URL = r'https://opentdb.com/api.php?amount=3&type=multiple&encode=base64'
DATABASE_PATH = sys.argv[1] if len(sys.argv) > 1 else r"..\\"
DATABASE_PATH += r"bin\database.sqlite"

def base64_string_decode(string):
    string = string.encode('utf-8')
    string = base64.b64decode(string)
    string = string.decode('utf-8')
    return string

def decode_question(question):
    question['question']        = base64_string_decode(question['question']).replace('"', '""')
    question['correct_answer']  = base64_string_decode(question['correct_answer']).replace('"', '""')

    for i, incorrect_answer in enumerate(question['incorrect_answers']):
        question['incorrect_answers'][i] = base64_string_decode(incorrect_answer).replace('"', '""')

def get_questions():
    #getting questions from api
    result = requests.get(OPENTDB_URL).text

    #parsing result to json
    result = json.loads(result)

    #getting all questions from json
    questions = [question for question in result['results']]

    #deleting unneccecery things from questions and decoding base64 content
    for question in questions:
        del question['category']
        del question['type']
        del question['difficulty']

        decode_question(question)

    return questions

def update_database(questions):
    #openning database
    conn = sqlite3.connect(DATABASE_PATH)
    database = conn.cursor()

    database.execute('DELETE FROM questions;') #deleting old table questions
    database.execute('DELETE FROM sqlite_sequence WHERE name="questions";') #resetting the question_id auto increment

    #inserting new questions
    for question in questions:
        database.execute(f'''INSERT INTO questions (question, correctAnswer, possibleAnswer1, possibleAnswer2, possibleAnswer3) VALUES ("{question['question']}", "{question['correct_answer']}", "{question['incorrect_answers'][0]}", "{question['incorrect_answers'][1]}", "{question['incorrect_answers'][2]}");''')

    #commiting changes to database
    conn.commit()
    conn.close()

def print_question(question):
    print(f"""
question : {question['question']}
correct  : {question['correct_answer']}
incorrect: {question['incorrect_answers']}
    """)

def main():
    questions = get_questions()
    update_database(questions)

    for question in questions:
       print_question(question)
        


if __name__ == '__main__':
    main()