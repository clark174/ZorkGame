#ifndef Room_H
#define Room_H
#define XML_USE_STL
#include <string>
#include <vector>
#include "border.h"
#include "trigger.h"

using namespace std;
class Room
{
  public:
  string name;
  string description;
  string type;
  string hint; //A hint to help the player out in tough rooms.
  vector<string> items;
  vector<string> containers;
  vector<string> creatures;
  vector<Border> borders;
  vector<trigger> triggers;

  Room();
  Room(XMLNode aNode);
  string checkBorder(string c);
  string describe();
  //Postcondition: description is displayed on the screen.

  string listItems();
  //Postcondition: the elements of items are displayed on the screen.

  private:

};
#endif
