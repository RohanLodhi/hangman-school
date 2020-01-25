#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

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

int categories()
{
    cout << "Enter 1 for random words, 2 for foods and related word, 3 for countries" << endl;
    int choice;
    cin >> choice;
	if(choice == 1 or 2 or 3){
		return choice;
	}
	else{
		cout << "Incorrect input";
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

string alreadyPresent(char guess, vector<char> guessed)
{
	for(int i; i<=sizeof(guessed)/sizeof(guessed[0]); i++){
		if(guessed[i] == guess){
			return "True";
		}
	}
	return "False";
}

void printOptions(vector<char> guessed, char wordArray[], int wordLength)
{
	for(int i; sizeof(wordArray)/sizeof(wordArray[0]); i++){
		int j = 0;
	repeat:
		if(wordArray[i]== guessed[j]){
			cout << guessed[j];
		}
		else if(j<sizeof(guessed)){
			j++;
			goto repeat;
		}
		else
		{
			cout << "_";
		}
		
		
	}
}

bool checkWin(vector<char> guessed, char wordArray[], bool win){
	for(int i; sizeof(wordArray)/sizeof(wordArray[0]); i++){
		int j = 0;
	repeat:
		if(wordArray[i]== guessed[j]){
			win = "True";
		}
		else if(j<sizeof(guessed)){
			j++;
			goto repeat;
		}
		else{
			win = "False";
		}
	}
	return win;
}

int main()
{
	srand(time(0));
	char guess;
	string wordToGuess;

    int choice = categories();
    string chosenCategory = loadFile(choice);
	wordToGuess = LoadRandomWord(chosenCategory);
	
	int wordLength = wordToGuess.size();
	//string wordArray[wordLength+1];
	//strcpy(wordArray, wordToGuess.c_str());
	char wordArray[wordToGuess.length()]; 
  
    int i; 
    for (i = 0; i < sizeof(wordArray); i++) { 
        wordArray[i] = wordToGuess[i]; 
    }

	int tries = 0;
	bool win = false;
	vector<char> guessed;

	cout << "Welcome to Hangman!" << endl;
	do
	{
		system("clear"); //cls for windows
		cout << "The word is " << wordLength << " letters long." << endl;
		
	again:
		cout << endl << "please enter your guess: ";
		cin >> guess;
		if(alreadyPresent(guess, guessed) == "True"){
			goto again;
		}
		else{
			guessed.push_back(guess);
			printOptions(guessed, wordArray, wordLength);
		}
		win = checkWin(guessed, wordArray, win);
		if(win){
			cout << "CONGRATS! YOU WON!";
			break;
		}
		

	} while (tries < 10);
	if(win){}
	else
	{
		cout << "Sorry, you lost. Word was: " << wordToGuess;
	}
	
	
	return 0;
}