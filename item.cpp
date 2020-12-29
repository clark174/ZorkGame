#include <iostream>
#include "item.h"

item::item(){}

item::item(XMLNode aNode){
  int i=0;
  XMLNode bNode=aNode.getChildNode(i++);
  do{
     string tag = bNode.getName();
     if (tag == "name")
       name = bNode.getText(0);
     else if (tag == "status")
       status = bNode.getText(0);
     else if (tag == "writing")
       writing = bNode.getText(0);
     else if (tag == "trigger"){
      trigger t(bNode);
      triggers.push_back(t);
     }
     else if (tag=="turnon"){
      turnon tu(bNode);
      turnons.push_back(tu);
     }
     else if (tag == "owner"){
      owner = bNode.getText(0);
     }
     bNode=aNode.getChildNode(i++);
  }while (!bNode.isEmpty());
}

void item::readItem()
{
  cout << writing << endl;
}

void item::addToInventory()
{
  owner = "inventory";
}

void item::updateOwner(string newOwner)
{
  owner = newOwner;
}

void item::updateStatus(string newStatus)
{
  status = newStatus;
}
