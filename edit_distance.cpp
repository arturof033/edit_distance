/*
	Arturo Flores
    CWID: 886352491
	Spring 2025
	CPSC 485
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include "edit_distance.h"


// directional graph values
//    each represent the direction of an arrow for the 
//    directional graph
#define MISMATCH_UPPER_LEFT "mis_upper_left"
#define MATCH_UPPER_LEFT "match_upper_left"
#define UP "upper"
#define LEFT "left"


// node containing a coordinates value and what node it used
//      to assign its value
struct graph_node{

    int value;
    string direction;

    graph_node(int new_value, string new_direction){

        value = new_value;
        direction = new_direction;

    }

    graph_node& operator=(const graph_node& other) {

        if (this != &other) {

            value =  other.value;
            direction = other.direction;

        }

        return *this;
    }

};

// initalizes an empty graph based on the given words length
vector< vector<graph_node> > create_graph_using(string first_word, string second_word){

    // length of first and second word
    int first_word_length = first_word.length() + 1;
    int second_word_length = second_word.length() + 1;

    // initializes graph with zeros and no direction
    vector< vector<graph_node> > new_graph = 
                                    vector< vector<graph_node> > \
                                    (first_word_length, vector<graph_node>
                                    (second_word_length, graph_node(0, "")));

    // sets value of first node
    new_graph[0][0] = graph_node(0, MATCH_UPPER_LEFT);

    // initializes first column of the graph
    for(int y_axis = 1; y_axis < first_word_length; y_axis++){

        new_graph[y_axis][0] = graph_node(y_axis, UP);

    }

    // initalizes first row of the graph
    for(int x_axis = 1; x_axis < second_word_length; x_axis++){

        new_graph[0][x_axis] = graph_node(x_axis, LEFT);

    }

    return new_graph;

}

// returns the smallest node surrounding a given coordinate
graph_node find_smallest_node_in_near(vector<vector <graph_node> > edit_distance_graph, int x_axis, int y_axis) {

    // creates nodes based on the currection position in the graph
    graph_node upper_left_node(edit_distance_graph[y_axis - 1][x_axis - 1].value + 1, MISMATCH_UPPER_LEFT);
    graph_node left_node(edit_distance_graph[y_axis][x_axis - 1].value + 1, LEFT);
    graph_node upper_node(edit_distance_graph[y_axis - 1][x_axis].value + 1, UP);

    // finds smallest value out of each node
    int smallest_value = min(upper_left_node.value, min(left_node.value, upper_node.value));

    // case where smallest value is in the left node
    if(smallest_value == left_node.value){

        return left_node;

    }
    // case where smallest value in the right node
    else if(smallest_value == upper_node.value){
        
        return upper_node;

    }
    // case where smallest value in the upper left node
    else{

        return upper_left_node;

    }

}


// creates edit distance graphs given words from user input
//    'first_word' will be vertical
//    'second_word' will be horizontal
vector< vector<graph_node> > create_edit_distance_graph_between(string first_word,
                                         string second_word) {

    // creates pair of graphs
    vector< vector<graph_node> > edit_distance_graph = create_graph_using(first_word, second_word);

    // length of first and second word
    int row_size = first_word.length() + 1;
    int column_size = second_word.length() + 1;

    // filling in edit distance matrix
    //    begins at 1 since first row has already by initialized 1 -> word length
    for(int y_axis = 1; y_axis < row_size; y_axis++) {

        // filling in horizontal rows
        for(int x_axis = 1; x_axis < column_size; x_axis++) {

            // condition if a match occurs
            //      -1 in order to start indexing words at [0]
            if (first_word[y_axis - 1] == second_word[x_axis - 1]) {

                // assigns new node to coordinates
                edit_distance_graph[y_axis][x_axis] = graph_node(
                    edit_distance_graph[y_axis - 1][x_axis - 1].value, MATCH_UPPER_LEFT);

            }
            // condition if there is a mismatch
            else {

                // finds the smallest value out of:
                //      upper left, left, and upper value
                graph_node smallest_node = find_smallest_node_in_near(edit_distance_graph, x_axis, y_axis);

                // assigns new node to coordinates
                edit_distance_graph[y_axis][x_axis] = smallest_node;

            }
        }
    }

    return edit_distance_graph;

}

// finds the last element in the edit distance graph and prints it
void print_edit_distance_from(vector< vector <graph_node> > edit_distance_graph){

    // finding dimensions of the graph
    int row_count = edit_distance_graph.size();
    int column_count = edit_distance_graph[0].size();

    // indexing last value in the edit distance graph
    int edit_distance = edit_distance_graph[row_count - 1][column_count - 1].value;

    // printing edit distance
    cout << "\n";
    cout << "The edit distance is: " << edit_distance << endl;
    cout << "\n";

}


// prints numerical edit distance graph
void print_edit_distance_graph_from_using(vector< vector <graph_node> > edit_distance_graph, string first_word, string second_word){

    // finding the dimensions of the graph
    int row_count = edit_distance_graph.size(); 
    int column_count = edit_distance_graph[0].size();

    // line break to sepearate rows
    string line_break(column_count * 6 + 8, '-');

    // starting to construct the graph
    cout << line_break << endl;
    cout << "|" << setw(3) << "" << setw(3);
    cout << "|" << setw(3) << "-" << setw(3);

    // printing the second word on x-axis
    for(int x_axis = 1; x_axis < column_count; x_axis++){

        cout << "|" << setw(3) << second_word[x_axis - 1] << setw(3);

    }

    cout << "|" << endl;
    cout << line_break << endl;

    // printing values in each row
    for(int y_axis = 0; y_axis < row_count; y_axis++){

        // printing the first word on y-axis
        if(y_axis != 0){
            cout << "|" << setw(3) << first_word[y_axis - 1] << setw(3) << "|";
        }
        else {
            cout << "|" << setw(3) << '-' << setw(3) << "|";
        }

        // printing values in each column
        for(int x_axis = 0; x_axis < column_count; x_axis++){

            cout << setw(3) << to_string(edit_distance_graph[y_axis][x_axis].value) << setw(3) << "|";

        }

        // line break between each row
        cout << endl;
        cout << line_break << endl;

    }

}


// prints alignment between words from user input
void print_alignment_from_using(vector< vector <graph_node> > edit_distance_graph, string first_word, string second_word){

    // finding graph dimensions 
    int row_count = edit_distance_graph.size();
    int column_count = edit_distance_graph[0].size();
    
    // initializing edited words
    string first_word_modified = "";
    string second_word_modified = "";

    // setting bounds for parsing the graph
    int x_axis = column_count - 1;
    int y_axis = row_count - 1;

    // loop stops when each word in complete 
    while(x_axis >= 0 && y_axis >= 0){

        // condition where we have a match or mismatch for upper left
        //     add letter from each word
        if(edit_distance_graph[y_axis][x_axis].direction == MATCH_UPPER_LEFT || 
           edit_distance_graph[y_axis][x_axis].direction == MISMATCH_UPPER_LEFT){

            first_word_modified = first_word[y_axis - 1] + first_word_modified;
            second_word_modified = second_word[x_axis - 1] + second_word_modified;

            x_axis -= 1;
            y_axis -= 1;

        }
        // condition where we have a mismatch choosing upper value
        //     add letter from first word
        //     add underscore to second word
        else if (edit_distance_graph[y_axis][x_axis].direction == UP){

            first_word_modified = first_word[y_axis - 1] + first_word_modified;
            second_word_modified = "_" + second_word_modified;

            y_axis -= 1;

        }
        // condition where we have a mismatch choosing upper value
        //     add underscore to first word
        //     add letter from second word
        else{
            
            first_word_modified = "_" + first_word_modified;
            second_word_modified = second_word[x_axis - 1] + second_word_modified;

            x_axis -= 1;

        }

    }

    // printing alignment sequences 
    cout << "The Alignment is: " << endl;
    cout << first_word_modified << endl;
    cout << second_word_modified << endl;
    
}


// fuction to be called from external file to find edit distance
void find_edit_distance_between(string first_word, string second_word){

    // creates the numerical and directional edit distance graphs
    vector< vector<graph_node> > edit_distance_graph = create_edit_distance_graph_between(first_word, second_word);

    // prints the edit distance matrix calculations
    print_edit_distance_graph_from_using(edit_distance_graph, first_word, second_word);

    // prints the edit distance between the two words
    print_edit_distance_from(edit_distance_graph);

    // prints the alignment sequnce to verify the edit distance
    print_alignment_from_using(edit_distance_graph, first_word, second_word);

}

