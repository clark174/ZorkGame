#ifndef Turnon_H
#define Turnon_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include <vector>

using namespace std;
class turnon
{
  public:
  turnon();
  turnon(XMLNode aNode);
  string print;
  string action;

  private:

};
#endif
