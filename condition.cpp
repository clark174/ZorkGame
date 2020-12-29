#include "condition.h"
#include <iostream>
using namespace std;

condition::condition()
{
 status = "";
 has = "";
 owner = "";
 object = "";
}

condition::condition(XMLNode aNode)
{
  int i=0;
  XMLNode bNode = aNode.getChildNode(i++);
  do{
    string tag=bNode.getName();
    if (tag == "status")
     status = bNode.getText(0);
    else if (tag == "has")
     has = bNode.getText(0);
    else if (tag == "owner")
     owner = bNode.getText(0);
    else if (tag == "object")
     object = bNode.getText(0);

    bNode = aNode.getChildNode(i++);
  }while (!bNode.isEmpty());
}
