#ifndef container_H
#define container_H
#define XML_USE_STL
#include <string>
#include <vector>
#include "trigger.h"
#include "item.h"
#include <algorithm>

using namespace std;
class container
{
  public:
  string name;
  string status; //locked or unlocked
  string description;
  vector <string> items; //names of items in the container.
  vector <trigger> triggers; //triggers of the container.

  container(XMLNode aNode);
  container();
  void openContainer();
  //Postcondition: status is changed to unlocked.

  void gainItem(string name);
  //Postcondition: name is added to items.

  void loseItem(string name);
  //Postcondition: name is removed from items.

  void updateStatus(string newStatus);
  //Postcondition: status = newStatus.
  private:

};
#endif
