#include <iostream>
#include <iostream>
#include <bits/stdc++.h>
#include "world.h"
#include "game.h"


using namespace std;

string bookFile = "game.xml";

vector<string> parseStr(string s) {
  vector<string> words;

  stringstream ss(s);

  while (ss.good()) {
      string substr;
      getline(ss, substr, ' ');
      words.push_back(substr);
  }
  return words;
}

Game::Game(string fileName, string id) {

  // Yuo will have to use the game ID to identify which game to use
  gameId=id;

  XMLNode aNode=XMLNode::openFileHelper(fileName.c_str(),"map");

  world=World(aNode);
}

Game::Game() {
}

string Game::processCommand(string id, string command) {
  vector<string> words;
  string message="";

  cout << "processCommand:" << id <<":" << command << endl;
  words = parseStr(command);

  if (words[0] == "go") {
    if (words.size() > 1) {
      string nextRoom=world.rooms[world.location].checkBorder(words[1]);
      if (nextRoom!="")
        world.location=nextRoom;
        message+= world.rooms[world.location].describe();
    } else {
      message+="Can't go there?\n";
    }
  } else if (words[0] == "look") {
    message+= world.rooms[world.location].describe();
  } else if (words[0] == "i" || words[0] == "inventory") {
    message+="Inventory not implemented\n";
  }
  cout << "game:" << message << endl;
  return message;
}

string Game::start(string id) {
  // your will need to ue ID for multiuser
  return world.rooms[world.location].describe();
}
