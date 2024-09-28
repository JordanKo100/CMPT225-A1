// Play list method implementation for CMPT 225 assignment
// Author: Jordan Ko
// Date: Sept 19
#include "PlayList.h"
#include <stdexcept>
#include <string>
#include <iostream>

using std::out_of_range;

PlayListNode* traverseList(PlayListNode* node, unsigned int pos){
    for (int i = 1; i < pos-1 && node != nullptr; i++){
        node = node->next;
    }
    return node;
}

// PlayList method implementations go here

PlayList::PlayList(){
    header = nullptr; 
    count_size = 0;
}

// PARAM: address to PlayList object
// DESCRIPTION: Deep copies the PlayList object by iteratively traversing through its linked list (header is pl) 
// First checks if the playlist copying is null if so the header of this PlayList object is also null
// Need to allocate pl memory address to variable temp for deep copying, and to not change/affect its constant header value pl, 
// Header of this playlist obj is allocated new memory of the data containing the copied first node of pl and later its next pointer
PlayList::PlayList(const PlayList& pl){
    if (pl.header == nullptr){
        header = nullptr;
        return;
    }

    PlayListNode* temp = pl.header;
    header = new PlayListNode(temp->song);
    PlayListNode* current = header;

    temp = temp->next;

    while (temp != nullptr){
        current->next = new PlayListNode(temp->song);
        current = current->next;
        temp = temp->next;
    }

    count_size = pl.count_size;
}

// deep copy the parameter value to calling object -> deallocate memory of calling obj. LL-> returns ref to calling obj
PlayList& PlayList::operator=(const PlayList & pl){
    // checks on self-assignment by looking at address value
    if (this == &pl){
        return *this;
    }

    // deallocate any pre-existing dynamic memeory stored in calling object if assigned to a nullptr
    while (this->header != nullptr){
        PlayListNode* temp = this->header->next;
        delete this->header;
        this->header = temp;
    }

    if (pl.header == nullptr){
        this->header = nullptr;
        return *this; // dereference the pointer to calling object to reference a PlayList& value
    }

    PlayListNode* temp = pl.header;
    this->header = new PlayListNode(temp->song);
    PlayListNode* current = this->header;

    temp = temp->next;

    while (temp != nullptr){
        current->next = new PlayListNode(temp->song);
        current = current->next;
        temp = temp->next;
    }

    count_size = pl.count_size;

    return *this;
}

PlayList::~PlayList(){
    PlayListNode* current = header;

    while (current != nullptr){
        PlayListNode* next_node = current->next;
        delete current;
        current = next_node;
    }
}

void PlayList::insert(Song sng, unsigned int pos){
    PlayListNode* current = header; 

    // if user wants to replace the first node of playlist
    if (pos == 1 || current == nullptr){
        PlayListNode* new_header = new PlayListNode(sng,current);
        header = new_header;
    }
    else{
        // moves node till index pos-1 to get the LHS and RHS of new node 
        current = traverseList(current, pos);

        // new node points to current->next (RHS of new node) and current node (LHS of new node) points to new node
        PlayListNode* new_node = new PlayListNode(sng, current->next);
        current->next = new_node;
    }
    count_size++;
}

Song PlayList::remove(unsigned int pos){
    PlayListNode* current = header;

    if (pos == 1){
        Song first_song_removed = current->song;
        header = current->next;
        delete current;

        count_size--;

        return first_song_removed;
    } else{
        current = traverseList(current,pos);
        
        PlayListNode* node_removed = current->next;
        Song song_removed = node_removed->song;

        // if removal was on the last node (hence if next is nullptr), otherwise connect current node to the node after the removed node
        if (node_removed->next == nullptr) {
            current->next = nullptr;
        } else {
            current->next = node_removed->next;
        }
        delete node_removed;

        count_size--;

        return song_removed;
    }
}

void PlayList::swap(unsigned int pos1, unsigned int pos2){
    PlayListNode* current = header;

    if (pos1 == pos2) {
        return;
    } 
    // swap pos values to keep consistency of always pos1 < pos2
    if (pos1 > pos2){
        unsigned int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }

    current = traverseList(current, pos1);
    PlayListNode* first_prev_node = current;
    
    current = header; // reset list for second loop

    current = traverseList(current,pos2);
    PlayListNode* second_prev_node = current;

    PlayListNode* first_swap_node = (pos1 == 1) ? header : first_prev_node->next;
    PlayListNode* second_swap_node = second_prev_node->next;

    if (pos1 == 1){
        // if pos1 = 1, pos2 > 2
        header = second_swap_node;

        // if pos1 = 1, pos2 = 2
        if (pos2 == 2){
            PlayListNode* temp = second_swap_node->next;
            second_swap_node->next = first_swap_node;
            first_swap_node->next = temp;
            
            return;
        } 
    // if the swap is adjacent
    } else if (abs(pos1-pos2) == 1){
        first_prev_node->next = second_swap_node;
        first_swap_node->next = second_swap_node->next;
        second_swap_node->next = first_swap_node;
        
        return;
    // if the node distance is >= 2
    } else{
        first_prev_node->next = second_swap_node;
    } 

    // Common operation for if node distance is >= 2, and if pos1 = 1, pos2 > 2
    second_prev_node->next = first_swap_node;
    
    PlayListNode* temp = first_swap_node->next;
    first_swap_node->next = second_swap_node->next;
    second_swap_node->next = temp;

    return;
}

Song PlayList::get(unsigned int pos) const{
    PlayListNode* current = header;
    unsigned int count = 0;

    // pos was 1-based, but in this get method count is 0-based
    while (count != pos-1 && current != nullptr){
        current = current->next;
        count++;
    }

    if (count < pos-1){
        throw out_of_range("out of range, playlist has " + std::to_string(this->size()) + " songs");
    }
    else {return current->song;}

    delete current;
}

unsigned int PlayList::size() const{
    return count_size;
}