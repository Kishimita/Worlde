/*

    wordle.cpp

    Menu-driven interface program that is a word-guessing game that allows
    the user to guess a randomly selected five-letter word. It allows the 
    user to:
        1. See the Rules.
        2. Play the Game.
        3. Quit.

    Input:  User's choice
            Five-letter word entered by user

    Processing: 1. Display menu.
                2. Prompt user for choice.
                3. Drive menu options
                    Case 1 - RULES
                        Display the rules of the Wordle game.
                    Case 2 - PLAY
                        Open the "OneHundredWords.txt" file for reading.
                        Load the words into an array of 100 strings called "wordPool".
                        Randomly selcect one of the words stored in the wordPool array.
                            While there are words in the file:
                                Prompt player to enter a guessed five-letter word.
                                Provide feedback with colors to player's guess.
                                    Green – The letter is in the word and in the correct spot. 
                                    Yellow – The letter is in the word but in the wrong spot.
                                    Gray – The letter is not in the word in any spot. 
                    Case 3 - QUIT

    Output: ------------

*/

// Header Files
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>        // To customize console attributes

using namespace std;

// Function Prototypes
string getWord(string []);                                                  // Function to get word from file
bool dispWordle(string word, string storeGuess[], const HANDLE COUT_H, int numWords);    // Function to display Wordle grid 
void dispRules();
void NewGuess(string word, string userGuess, int currentGuess, string storeGuess[], int &totalWordsGuessed, bool &correctGuess);

int main()
{
    // Variables & Constants
    const int RULES = 1,
            PLAY = 2,
            QUIT = 3;
    
    string wordPool[100],
        storeGuess[6] = {"     ",  "     ", "     ", "     ", "     ","     "},
        guess,
        word,                 // Stores five letter word generated from file
        filename;             // Stores name of txt file that contains the random words
    ifstream inFile;
    int count = 0,
        choice,
        wordsGuessed = 0;               // Stores integer input from user for menu choice
    
    bool rightGuess = false;
    // Seed random function
    srand(time(0));

    // Open file
    inFile.open("OneHundredWords.txt");

     if (!inFile)
    {
        cout << "\nFatal Error ... Could not open OneHundredWords.txt file." << endl;
        exit(EXIT_FAILURE);
    }

    while (inFile >> wordPool[count])
    {
        count++;
    }
        
    // Close file
    inFile.close();

    // Call function
    word = getWord(wordPool);
    cout << endl << word; // TESTING

    // Intro - Menu
    do 
    {
        // Display menu and prompt user for choice
        cout << "\nChoose one of the following options:" << endl
            << "\t1. See the Rules." << endl
            << "\t2. Play the Game." << endl
            << "\t3. Quit." << endl
            << "Option: ";
        cin >> choice;
    
        // Drive menu options
        switch (choice)
        {
            case RULES: 
                dispRules();
                break;
            case PLAY:
            {
                

                cout << "\nWordle ..." << endl;

                // Prompt user for their guess and stores each guess in storeGuess 
                // after each iteration.

                for (int i = 0; i < 6; i++)
                {
                    if (!rightGuess)
                    {
                        NewGuess(word, guess, i, storeGuess, wordsGuessed, rightGuess);
                    }
                    else
                    {
                        break;
                    }
                    
                }
                break;
            }
            case QUIT:
                break;
            default:
                cout << "Invalid Option...Try Again." << endl;
                continue;
        }
    } while (choice != QUIT);

    return 0;
}

void dispRules()
{
    cout << "\n- - - - - - - - - - - - - - - - - - - - - - " << endl
        << "Rules of The Game ..." << endl
        << "\nGuess the WORDLE in six tries." << endl
        << "Each guess must be a valid five-letter word. Hit the enter button to submit." << endl
        << "After each guess, the color of the tiles will change to show how close your guess was to the word." << endl
        << "- The color 'Green' means the letter is in the word." << endl
        << "- The color 'Yellow' means the letter is in the word but in the wrong spot." << endl
        << "- The color 'Grey' means the letter is not in the word." << endl;
}

void NewGuess(string word, string userGuess, int currentGuess, string storeGuess[], int& totalWordsGuessed, bool& correctGuess)
{
    // Get access to the cout output handle
    const HANDLE COUT_H = GetStdHandle(STD_OUTPUT_HANDLE);

    do
    {
        cout << "\nRound " << currentGuess + 1 << endl
            << "Enter word (5-letters): ";
        cin >> userGuess;
        totalWordsGuessed++;

        // Validate
        if (userGuess.length() < 5 || userGuess.length() > 5)
            cout << "Error ... Invalid word. Try again." << endl;

    } while (userGuess.length() < 5 || userGuess.length() > 5);

    storeGuess[currentGuess] = userGuess;
    // cout << storeGuess[i] << endl;

    // Calls function to display grid
    correctGuess = dispWordle(word, storeGuess, COUT_H, totalWordsGuessed);
}

/*
    string getWord(string wordPool [])

    Generates random word from 'txt' file
    and stores the word in the variable 'word'.

    Return Value: A word item
*/
string getWord(string wordPool [])
{
    string word;

    // Generate a random word (0 - 99)
    int randNum; 

    randNum = rand() % 100;
    word = wordPool[randNum];

    return word;
}

/*
    void dispWordle(string word, string storeGuess[],const HANDLE COUT_H)

    Displays Wordle grid after each round and validates letters with colors.
*/
bool dispWordle(string word, string storeGuess[],const HANDLE COUT_H, int numWords)
{
    // Colors based on ANSI hexadecimal color codes
    // The first digit indicates the background color
    // The second digit indicates the foreground color
    const int GRAY = 0x8F,
            YELLOW = 0x6F,
            RESET = 0x07,
            GREEN = 0x2F;

    int Color_Value= RESET;
    bool wordFound = false;
    int correctLetters;
    

    for (int i = 0; i < 6; i++)
    {
        correctLetters = 0;
        cout<< "\n---------------------" << endl;
        //Color_Value = RESET;

        for (int j = 0; j < 5; j++)
        {
            if (word[j] == storeGuess[i][j])
            {
                Color_Value = GREEN;
                correctLetters++;

                if (correctLetters == 5)
                {
                    wordFound = true;
                }
            }
            else
            {
                for (int l = 0; l < 5; l++)
                {
                    if (storeGuess[i][j] == word[l])
                    {
                        Color_Value = YELLOW;
                        break;
                    }
                    else
                    {
                        if (i + 1 > numWords)
                            Color_Value = RESET;
                        else
                            Color_Value = GRAY;
                    }
                }
            } 

            SetConsoleTextAttribute(COUT_H, Color_Value);
            cout << "| " <<storeGuess[i][j] << " ";
            Color_Value = RESET;
            SetConsoleTextAttribute(COUT_H, Color_Value);
        }
        cout << "|";
    }
    cout << "\n---------------------" << endl;

    if (wordFound)
    {
        cout << "Magnificent! (" << numWords << "/6)" << endl;
    }
    return wordFound;
}

