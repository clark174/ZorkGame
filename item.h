#ifndef Item_H
#define Item_H
#define XML_USE_STL
#include <string>
#include "trigger.h"
#include "turnon.h"
#include <vector>

using namespace std;
class item
{
  public:
  string name;
  string owner;
  string status;
  string writing = "Nothing written.";
  vector<turnon> turnons;
  vector<trigger> triggers;

  item(XMLNode aNode);
  item();
  void readItem();
  //Postcondition: writing is displayed to the screen.

  void addToInventory();
  //Postcondition: owner = "inventory".

  void updateOwner(string newOwner);
  //Postcondition: owner = "newOwner".

  void updateStatus(string newStatus);
  //Postcondition: status = newStatus.
  private:

};
#endif
