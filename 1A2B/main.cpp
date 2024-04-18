#include <bits/stdc++.h>
#define ouo ios_base::sync_with_stdio(false), cin.tie(0)
#define ll long long
#define db double
using namespace std;

string generateRandomNumber();
bool isValidGuess(string guess);
string checkGuess(string secret, string guess);

int main() {
    system("cls");
    cout << "Welcome to 1A2B!" << endl;
    string secretNumber = generateRandomNumber();
    string guess;
    int guesses = 0;

    while (true) {
        cout << "Guess 4 numbers: ";
        cin >> guess;

        if (!isValidGuess(guess)) {
            cout << "Invalid. Try again." << endl;
            continue;
        }

        string result = checkGuess(secretNumber, guess);
        cout << "Result: " << result << endl;
        ++guesses;

        if (result == "4A0B") {
            cout << "Congratulations! The answer is " << secretNumber << endl;
            cout << "U guess " << guesses << ((guesses == 1) ? " time" : " times") << endl;
            break;
        }
    }

    return 0;
}

string generateRandomNumber() {
    string number = "";
    srand(time(NULL));
    for (int i = 0; i < 4; ++i) {
        char digit = '0' + rand() % 10;
        while (number.find(digit) != string::npos) {
            digit = '0' + rand() % 10;
        }
        number += digit;
    }
    return number;
}

bool isValidGuess(string guess) {
    if (guess.length() != 4) {
        return false;
    }
    for (char c : guess) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

string checkGuess(string secret, string guess) {
    int a = 0, b = 0;
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == secret[i]) {
            ++a;
        } else if (secret.find(guess[i]) != string::npos) {
            ++b;
        }
    }
    return to_string(a) + "A" + to_string(b) + "B";
}