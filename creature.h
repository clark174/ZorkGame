#ifndef Creature_H
#define Creature_H
#define XML_USE_STL
#include <string>
#include <vector>
#include "trigger.h"

using namespace std;
class creature
{
  public:
  string name;
  string description;
  string status;
  string attack;
  string vulnerability;
  vector<trigger> triggers;

  creature(XMLNode aNode);
  creature();
  void killCreature();
  //Postcondition: status = "dead".

  void updateStatus(string newStatus);
  //Postcondition: status = newStatus.

  private:

};

#endif
