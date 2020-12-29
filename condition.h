#ifndef Condition_H
#define Condition_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include <vector>

using namespace std;

class condition{

  public:
  string owner;
  string object;
  string status;
  string has; //yes or no.

  condition(XMLNode aNode);
  condition();

  private:

};
#endif
