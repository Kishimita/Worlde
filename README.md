# Worlde
Wordle
    
    /*
    wordle.cpp
    ****NOTE ONLY RUNS ON WINDOWS!!!****
    
    Menu-driven interface program that is a word-guessing game that allows
    the user to guess a randomly selected five-letter word. Keep in mind this program
    grabs the words randomly from a txt file. It allows the 
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
