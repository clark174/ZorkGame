#include "creature.h"
#include <iostream>

using namespace std;

creature::creature(){}

creature::creature(XMLNode aNode)
{
  int i=0;
  XMLNode bNode = aNode.getChildNode(i++);
  do{
    string tag=bNode.getName();
    if (tag == "name")
      name = bNode.getText(0);
    else if (tag == "description")
      description = bNode.getText(0);
    else if (tag == "status")
      status = bNode.getText(0);
    else if (tag == "vulnerability"){
      vulnerability = bNode.getText(0);
    }
    else if (tag == "trigger"){
      trigger t(bNode);
      triggers.push_back(t);
    }
    else if (tag == "attack")
     attack = bNode.getText(0);

    bNode = aNode.getChildNode(i++);
  }while (!bNode.isEmpty());
}

void creature::killCreature()
{
  status = "dead";
}

void creature::updateStatus(string newStatus)
{
  status = newStatus;
}
