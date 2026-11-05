
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;
struct Joke
{
    string setup;
    string punchline;
};
// Split setup and punchline.
vector<Joke> loadJokes(const string &filename)
{
    vector<Joke> jokes;
    ifstream file(filename);
    if (!file.is_open())
    {
        return jokes;
    }

    string line;
    while (getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        size_t pos = line.find('?');
        if (pos == string::npos || pos == 0 || pos + 1 == line.size())
        {
            continue;
        }
        jokes.push_back({line.substr(0, pos + 1), line.substr(pos + 1)});
    }
    return jokes;
}
// Compare commands without case.
string lowerCase(string text)
{
    for (char &c : text)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return text;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<Joke> jokes = loadJokes("randomJokes.txt");
    if (jokes.empty())
    {
        cout << "No jokes loaded." << endl;
        return 1;
    }

    cout << "Joke Teller\nRequest: Alexa, tell me a joke\nQuit: quit" << endl;

    string input;
    while (true)
    {
        cout << "\n> ";
        if (!getline(cin, input) || lowerCase(input) == "quit")
        {
            cout << "Goodbye!" << endl;
            break;
        }
        if (lowerCase(input) != "alexa, tell me a joke")
        {
            cout << "Unknown request. Try again." << endl;
            continue;
        }

        Joke joke = jokes[rand() % jokes.size()];
        cout << joke.setup << endl;
        cout << "Press Enter for punchline";
        if (!getline(cin, input)) { cout << "\nGoodbye!" << endl; break; }
        cout << joke.punchline << endl;
    }
    return 0;
}
