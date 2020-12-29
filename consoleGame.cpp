#include <iostream>
#include <sstream>
#include "game.h"

using namespace std;

string gamefile = "game.xml";
string gameId="jimmyclark";  //This will need to be generated unique for each game



int main() {
  string command;
  Game theGame(gamefile,gameId);
  cout << theGame.start(gameId);

  while (1) {
    cout << ">>> ";
    getline(cin,command);
    //if you drop the ring in Mount Doom, end the game.
    if(command == "drop ring" && theGame.world.location == "MountDoom" && theGame.world.creatures["gollum"].status == "dead")
    {
      cout << "You have destroyed the One Ring! Victory!!!\n";
      break;
    }
    cout << theGame.processCommand(gameId,command);
  }


}
