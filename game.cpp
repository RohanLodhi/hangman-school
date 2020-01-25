#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void DrawHangman(int guessCount = 0)
{
    cout << "You have " << 10-guessCount << " tries left." << endl;
}
void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    cout << s;
}
void PrintAvailableLetters(string taken)
{
    cout << "Available letters" << endl <<endl;
    PrintLetters(taken, 'A', 'M');
    cout << endl;
    PrintLetters(taken, 'N', 'Z');
    cout << endl <<endl;
}
bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    cout << s;
    return won;
}
string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);
 
        int randomLine = rand() % v.size();
 
        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
int TriesLeft(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}

int categories()
{
    cout << "Enter 1 for random words, 2 for foods and related word, 3 for countries" << endl;
    int choice;
    cin >> choice;
	if(choice == 1 or 2 or 3){
		return choice;
	}
	else{
		cout << "Incorrect input" << endl;
		categories();
	}
    
}

string loadFile(int choice)
{
    string chosenCategory;
    switch(choice) {
        case 1:
            chosenCategory = "randomwords.txt";
            break;
            
        case 2:
            chosenCategory = "food.txt";
            break;

        case 3:
            chosenCategory = "countries.txt";
            break;

    }
    return chosenCategory;
    
}

int main()
{
    srand(time(0));
    string guesses;
    string wordToGuess;
    int choice = categories();
    string chosenCategory = loadFile(choice);
    wordToGuess = LoadRandomWord(chosenCategory);
    int tries = 0;
    bool win = false;
    do
    {
        system("clear"); //cls in windows
        cout << endl;
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        cout <<endl << "Guess the word" << endl <<endl;
        win = PrintWordAndCheckWin(wordToGuess, guesses);
 
        if (win)
            break;
 
        char x;
        cout << " > "; cin >> x;
 
        if (guesses.find(x) == string::npos)
            guesses += x;
 
        tries = TriesLeft(wordToGuess, guesses);
 
    } while (tries < 10);
 
    if (win)
        cout <<endl <<"YOU WON!";
    else
        cout <<endl << "GAME OVER. The word was: " <<wordToGuess << endl;

    getchar();
    return 0;
}