/*
	Arturo Flores
    CWID: 886352491
	Spring 2025
	CPSC 485
*/

#include <iostream>
#include <string>
#include <cctype>
#include "edit_distance.h"
using namespace std;

// function definitions
bool prompt_end_condition();
void prompt_user_input_for(string &first_word, string &second_word);
void line_break();

int main(int argc, char* argv[]) {

    cout << endl;
    line_break();

    cout << "Welcome to Edit Distance Demonstration." << endl;

    // determines when the program ends
    bool program_continues = true;

    while(program_continues){

        line_break();
        cout << endl;

        // values to be replaced by user input
        string first_word;
        string second_word;

        // prompts user for input of first and second word
        prompt_user_input_for(first_word, second_word);

        // find edit distance between given words
        find_edit_distance_between(first_word, second_word);

        // prompts user to continue or end program
        program_continues = prompt_end_condition();

        cout << endl;

    }

	return 0;

}

// promts user for input 
void prompt_user_input_for(string &first_word, string &second_word){

    cout << "Please input two words for the edit distance: \n" << endl;

    // prompts user for first word
    cout << "Enter first word: ";
    cin >> first_word;

    // prompts user for second word
    cout << "Enter second word: ";
    cin >> second_word;
    cout << endl;

}

// returns true if user wants to continue program, else otherwise
bool prompt_end_condition(){

    string end_prompt = "";

    // continues asking for user input until a valid response is provided
    while (true)
    {

        cout << endl;
        line_break();
        cout << endl;

        cout << "Would you like to continue? ('yes'/'no'): " << endl;
        cin >> end_prompt;

        if(end_prompt == "yes")
        {
            return true;
        }
        else if(end_prompt == "no")
        {
            return false;
        }
    }
}

// line break used to separate each program sequence
void line_break(){

    cout << "--------------------------------------------------------" << endl;

}