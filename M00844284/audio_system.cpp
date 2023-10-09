#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "hash_table.h"


int main() {
  HashTable table;
  std::string fileName;
  std::cout << "Welcome to the new audio streaming service!!" << " \n";
  std::cout << "Please enter the file name to add all tracks to the library >> ";
  std::cin >> fileName;
  std::string doc_line;
  std::fstream tracks_data;
  std::string title;
  std::string artist;
  int duration;
  tracks_data.open(fileName, std::ios::in);
  if (tracks_data.is_open()) {
    while (std::getline (tracks_data, doc_line)) {
      std::istringstream line_obj(doc_line);
      std::getline(line_obj, title, '\t');
      std::getline(line_obj, artist, '\t');
      // convert duration string to int using stoi
      std::string duration_str;
      std::getline(line_obj, duration_str, '\t');
      duration = std::stoi(duration_str);
      AudioTrack* track1 = new AudioTrack(title, artist, duration);
      table.addTrack(track1);
      std::cout << track1->getTitle() << " | " << track1->getArtist() << " | " << track1->getDuration() << " \n";
    }
    std::cout << " \n";
    std::cout << "The following data has been added to the library!! \n";
    tracks_data.close(); // close the file after reading
  }
  else {
    std::cout << "File not found!!";
    exit(EXIT_SUCCESS);
  }

  std::cout << " \n";
  std::cout << "Audio streaming service menu \n";
  std::cout << "-------------------------------------------- \n";
  std::cout << "1. Save tracks in the library to a file. \n";
  std::cout << "2. Search by artist/band name. \n";
  std::cout << "3. Remove specific track. \n";
  std::cout << "0. Exit. \n";
  std::cout << " \n";
  int selectedOpt;
  std::cout << "Enter the option number please >> ";
  std::cin >> selectedOpt;

  while (selectedOpt < 0 || selectedOpt > 3) {
    std::cout << "Invalid input!! \n";
    std::cout << "Select >> ";
    std::cin >> selectedOpt;
  }
  
  switch (selectedOpt) {
    case 0:
      std::cout << "Audio streaming service exited succesfully \n";
      break;
      
    case 1:
      {
	std::cout << "To save tracks you need to provide its details \n";
	std::cout << "Enter the title of the truck >> ";
	std::cin >> title;
	std::cout << "Artist/band name >> ";
	std::cin >> artist;
	std::cout << "Duration of the song >> ";
	std::cin >> duration;
      
        AudioTrack* track2 = new AudioTrack(title, artist, duration);
        bool add = table.addTrack(track2);
	std::string strDuration = std::to_string(track2->getDuration());
	std::string data = track2->getTitle() + "\t" + track2->getArtist() + "\t" + strDuration + "\t";
	if (add) {
	  tracks_data.open(fileName, std::ios::app);
	  tracks_data << data;
	  tracks_data.close();
	}
	else {
	  std::cout << "Track already stored in the library \n";
	}
	
      }
      break;
      
    case 2:
      {
	std::cout << "Enter the name of the artist/band you are looking for >> ";
        std::string artist;
        std::cin >> artist;
        AudioTrack* track3 = table.findTrack(artist);
        if (track3 != nullptr) {
	  std::cout << "Title: " << track3->getTitle() << "| Artist: " << track3->getArtist() << "| Duration: " << track3->getDuration(); 
        }
      }
      break;

    case 3:
      {
	std::cout << "Enter the name of the artist/band you want to remove >> ";
        std::string artist;
        std::cin >> artist;
        bool removeTrack = table.removeTrack(artist);
        if (removeTrack) {
	  std::cout << "The selected track has been removed from library \n";
          std::fstream temp_file;
          std::string temp_data;
          std::string temp_artist;
          temp_file.open("pro_info.dat", std::ios::app);
          std::ifstream tracks_data(fileName);
          while (std::getline(tracks_data, doc_line)) {
            std::istringstream line_obj2(doc_line);
            std::getline(line_obj2, temp_data, '\t');
            std::getline(line_obj2, temp_artist, '\t');
            std::getline(line_obj2, temp_data, '\t');
            if (artist != temp_artist) {
              temp_file << doc_line << " \n";
            }
          }
          std::remove(fileName.c_str());
          std::rename("pro_info.dat", fileName.c_str());
        }
        else {
	  std::cout << "Track not found \n";
        }
    }
    break;

  }
  
  return 0;
}






























