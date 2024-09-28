// Main methodvimplementation for PLayList classs CMPT 225 assignment
// Author: Jordan Ko
// Date: Sept 19
// Worst-case running time for the following methods and command functions:
// PlayList Methods
    // Default constructor: O(1)
        // Assigns private variable to nullptr in constant time
    // Destructor: O(n)
        // Loops through list to deallocate each node in linear time
    // Copy constructor: O(n)
        // Needs to traverse and copy each node over in linear time
    // Overloaded assignment operator: O(n)
        // First requires deallocation of any stored memory in LHS list, then copies over RHS list through a loop, 
        // thus 2*n time but simplifies down to O(n)
    // Insert: O(n)
        // Traverse list to get to one minus position to insert in linear time
    // Remove: O(n)
        // Traverse list to get to one minus position to remove in linear time
    // Get: O(n)
        // Traverse list to get to node position in linear time
    // Swap: O(n)
        // First loops to get to the node one minus first position, then second loops to get to one minus second position
        // thus 2*n time but simplifies to O(n)
    // Size: O(1)
        // Insert and remove method increments the private variable count_size, size() simply returns it
// Main Function Commands
    // Enter a song: O(n)
        // insert() is in O(n) time likewise with this function
    // Remove a song: O(n)
        // remove() is in O(n) time likewise with this function
    // Swap two songs: O(n)
        // swap() is in O(n) time likewise with this function
    // Print all the songs: O(n^2)
        // Loop throuh all indices of list O(n) time, but get() is in O(n) to traverse each node to get required position node
        // thus a loop-within-a-loop or O(n^2) time

#include <iostream>
#include "PlayList.h"
#include <string>
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::string;


int main() {
    PlayList* user_playlist = new PlayList();

    cout << "Menu: \n 1 - Enter a song in the play list at a given position \n 2 - Remove a song from the play list at a given position \n 3 - Swap two songs in the play list \n 4 - Print all the songs in the play list \n 5 - Quit" << endl;

    while(true){
        int option;
        bool is_quit = false;
        
        unsigned int size_of_pl = (user_playlist->size() == 0) ? 0 : user_playlist->size();

        cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        cin >> option;

        // user enters a non-integer value
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Please enter a value between 1-5 representing the various menu options. \n" << endl;
            continue; 
        }

        switch (option) {
            case 1: {
            string song_name;
            string artist_name;
            int song_length;
            unsigned int input_position;

            cout << "Song Name: ";
            cin.ignore(); 
            getline(cin, song_name); 

            cout << "Artist: ";
            std::getline(cin, artist_name);

            cout << "Length: ";
            cin >> song_length;

            // if user enters a non-integer value
            while (cin.fail() || artist_name.empty() || song_name.empty()){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                // Ensures user doesn't input an empty string
                if (song_name.empty()){
                    cout << "Please enter the artist name: ";
                    getline(cin, song_name); 
                    continue;
                } else if (artist_name.empty()){
                    cout << "Please enter the song name: ";
                    getline(cin, artist_name);
                    continue;
                }

                cout << "Please enter a valid length of the song in seconds: ";
                cin >> song_length;     
            }

            if (size_of_pl == 0){
                cout << "Position (1): ";
            } else {
                cout << "Position (1 to " + std::to_string(size_of_pl + 1) + "): ";
            }
            cin >> input_position;

            // ensure position is within valid range
            while (input_position > size_of_pl + 1 || input_position < 1) {
                if (size_of_pl == 0){
                    cout << "Out of range, please input a valid position to be inserted (1): ";
                } else {
                    cout << "Out of range, please input a valid position to be inserted (1 to " + std::to_string(size_of_pl + 1) + "): ";
                }
                cin >> input_position;
            }

            // Create song object directly on stack and not heap for auto-deallocation
            Song user_song(song_name, artist_name, song_length);
            user_playlist->insert(user_song, input_position);

            cout << "You entered " + song_name + " at position " + std::to_string(input_position) + " in the play list. \n" << endl;

            continue;
        }
            case 2: {
                unsigned int pos_remove;

                if (size_of_pl == 0){
                    cout << "No songs in play list. \n" << endl;
                    continue;
                } else{
                    cout << "Position (1 to " + std::to_string(size_of_pl) + "): ";
                }
                cin >> pos_remove;

                while (pos_remove > size_of_pl || pos_remove < 1){
                    cout << "Out of range, please input a valid position to be removed (1 to " + std::to_string(size_of_pl) + "): ";
                    cin >> pos_remove;
                } 

                Song removed = user_playlist->remove(pos_remove);

                cout << "You removed " + removed.getName() + " from the play list. \n" << endl;
                continue;
            }
            case 3:{
                unsigned int pos1;
                unsigned int pos2;

                if (size_of_pl == 0){
                    cout << "No songs in play list. \n" << endl;
                    continue;
                } else if (size_of_pl == 1){
                    cout << "Only 1 song in play list, add atleast one more song. \n" << endl;
                    continue;
                } else{
                    cout << "Swap song at position (1 to " + std::to_string(size_of_pl) + "): ";
                    cin >> pos1;

                    while (pos1 > size_of_pl || pos1 < 1){
                        cout << "Out of range, please input a valid position to swap song (1 to " + std::to_string(size_of_pl) + "): ";
                        cin >> pos1;
                    }

                    cout << "with the song at position (1 to " + std::to_string(size_of_pl) + "): ";
                    cin >> pos2;

                    while (pos2 > size_of_pl || pos2 < 1){
                        cout << "Out of range, please input a valid position to swap with position " + std::to_string(pos1)+ " " + "(1 to " + std::to_string(size_of_pl) + "): ";
                        cin >> pos2;
                    }
                }

                user_playlist->swap(pos1, pos2);

                cout << "You swapped the songs at position " + std::to_string(pos1) + " and " + std::to_string(pos2) + "\n" << endl;
                continue;
            }
            case 4: {
                // iterate through each node value in list
                for (int i = 1; i < user_playlist->size()+1; i++){
                    Song retrieved = user_playlist->get(i);

                    cout << std::to_string(i) + " " + retrieved.getName() + " (" + retrieved.getArtist() + ") " + std::to_string(retrieved.getLength()) +"s" << endl;
                }
                cout << "There are " + std::to_string(user_playlist->size()) + " songs in the play list. \n" << endl;
                continue;
            }
            case 5:
                cout << "You have chosen to quit the program." << endl;
                
                is_quit = true;
                break;
            default:
                cout << "Please enter a value between 1-5 representing the various menu options. \n" << endl;
                continue;
        }

        if (is_quit){
            delete user_playlist;
            break;
        }
    }

    return 0;
}