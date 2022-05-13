from server import Server
import json

REQUEST_IDS = {
    "login": 0,
    "signup": 1
    }

def main():
    print(" ----- python client ----- ")

    #conneting to server
    server = Server('127.0.0.1', 4206)

    login_request = {
        "username": "Donald Trump",
        "password": "123456"
        }
    signup_request = {
        "username": "Donald Trump",
        "password": "123456",
        "email": "DonaldTrump@america.com"
        }

    server.send(REQUEST_IDS['login'], json.dumps(login_request))
    server.send(REQUEST_IDS['signup'], json.dumps(signup_request))


if __name__ == '__main__':
    main()