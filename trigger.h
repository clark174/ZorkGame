#ifndef Trigger_H
#define Trigger_H
#define XML_USE_STL
#include <string>
#include <vector>
#include "condition.h"

using namespace std;
class trigger
{
  public:
  condition aCondition; //for the sake of simplicity, there is only one condition per trigger.
  string type; //type of trigger (single or permanent)
  string print;
  string action;
  string command;

  trigger(XMLNode aNode);

  private:

};
#endif
