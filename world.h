#ifndef World_H
#define World_H
#define XML_USE_STL
#include <string>
#include <vector>
#include <map>
#include "room.h"
#include "item.h"
#include "creature.h"
#include "container.h"

using namespace std;
class World
{
  public:
  string location;
  map<string,Room> rooms;
  map<string,item> items;
  map<string,creature> creatures;
  map<string,container> containers;
  vector<string> inventory;

  World();
  World(XMLNode aNode);

  private:

};
#endif
