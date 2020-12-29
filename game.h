#ifndef Game_H
#define Game_H

#include <string>
#include "world.h"

using namespace std;
class Game
{
  public:
  string gameId;
  string print; //temporary text holder for triggers.
  string gameStatus; //if gameStatus = over, the game ends.
  World world;

  Game(string fileName, string id);
  Game();
  string start(string id);
  //Postcondition: the Entrance location is described.

  string processCommand(string command, string id);
  //Postcondition: any actions associated with the command are executed and a message is displayed to the screen.

  bool checkContainerTrigger(vector<string> command, string name);
  //Function to check if conditions for a container's trigger are met.
  //Precondition: name is the name of the container, command is the command that the user just typed in or it is a blank vector.
  //Postcondition: returns true if the conditions for a trigger have been met, assigns print to the trigger's print value, and executes the trigger's action if there is one.
  //The functions below do the same thing except for the 3 other types of objects in the game.

  bool checkItemTrigger(vector<string> command, string name);
  bool checkRoomTrigger(vector<string> command, string name);
  bool checkCreatureTrigger(vector<string> command, string name);
  private:
  vector <string> blank; //empty vector to send when checking for triggers with no command.

};
#endif
