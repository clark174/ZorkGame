#include "trigger.h"
#include <iostream>

using namespace std;

trigger::trigger(XMLNode aNode)
{
  int i=0;
  XMLNode bNode = aNode.getChildNode(i++);
  do{
    string tag = bNode.getName();
    if (tag == "type")
     type = bNode.getText(0);
    else if (tag == "condition"){
     aCondition = condition(bNode);
    }
    else if (tag == "print"){
     print = bNode.getText(0);
    }
    else if (tag == "action"){
     action = bNode.getText(0);
    }
    else if (tag == "command"){
     command = bNode.getText(0);
    }
    bNode = aNode.getChildNode(i++);
   }while (!bNode.isEmpty());
}
