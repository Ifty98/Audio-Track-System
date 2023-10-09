#include <string>
#include <iostream>
#include <fstream>
#include "audio_track.h"

class HashTable {

 private:
  static const int table_size = 10000;
  struct Node {
    AudioTrack* track;
    Node* next;
  };
  Node* table[table_size];

 public:
  HashTable() {
    for (int i = 0; i < table_size; i++) {
       table[i] = nullptr;
    }
  }

  int hashCode(std::string key) {
    int code = 0;
    for (std::string::size_type k = 0; k < key.length(); k++) {
      code = code + static_cast<int>(key[k]);
    }
    code = code * key.length() * 31;
    code = code % table_size;
    return code;
  }

  bool keyCheck(std::string key) {
    int code = hashCode(key);
    Node* entry = table[code];
    while (entry != nullptr) {
        if (entry->track->getArtist() == key) {  
            return true;
        }
        entry = entry->next;
    }
    return false;
  }

  bool addTrack(AudioTrack* track) {
    std::string key = track->getArtist();
    bool keyStored = keyCheck(key);
    if (!keyStored) {
        int code = hashCode(key);

	
        Node* newNode = new Node();
        newNode->track = track;
        newNode->next = nullptr;

        if (table[code] == nullptr) {
            table[code] = newNode;
	    std::cout << "Saved succesfully!!";
	    return true;
        }
        else {
            Node* thisNode = table[code];
            while (thisNode->next != nullptr) {
                thisNode = thisNode->next;
            }
            thisNode->next = newNode;
	    std::cout << "Saved succesfully!!";
	    return true;
        }  
    }
    else {
      return false;
    }
  }

  bool removeTrack(std::string key) {
    int code = hashCode(key);
    Node* current = table[code];
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->track->getArtist() == key) {
            if (previous == nullptr) {
                // the track is the head of the linked list
                table[code] = current->next;
            } else {
                // the track is in the middle or end of the linked list
                previous->next = current->next;
            }
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
  }

   AudioTrack* findTrack(std::string key) {
    int code = hashCode(key);
    Node* entry = table[code];
    while (entry != nullptr) {
        if (entry->track->getArtist() == key) {  
            return entry->track;
        }
        entry = entry->next;
    }
    std::cout << "Artist/band not found";
    return nullptr;
  }
};
