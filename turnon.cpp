#include "turnon.h"
#include <iostream>
using namespace std;

turnon::turnon(XMLNode aNode)
{
  int i=0;
  XMLNode bNode = aNode.getChildNode(i++);
  do {
    string tag = bNode.getName();
    if (tag == "print")
     print = bNode.getText(0);
    else if (tag == "action"){
     action = bNode.getText(0);
    }
    bNode = aNode.getChildNode(i++);
  }while (!bNode.isEmpty());
}

turnon::turnon()
{
  print = "";
}
