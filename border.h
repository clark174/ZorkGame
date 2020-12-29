#ifndef Border_H
#define Border_H
#define XML_USE_STL
#include "xmlParser.h"
#include <string>
#include <vector>

using namespace std; 
class Border 
{ 
  public: 
  string direction;
  string name;

  Border(XMLNode aNode);
  Border();
  private:

}; 
#endif
