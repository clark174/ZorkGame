#include "container.h"
#include <iostream>
using namespace std;

container::container(){}

container::container(XMLNode aNode)
{
  int i=0;
  XMLNode bNode = aNode.getChildNode(i++);
  do{
    string tag = bNode.getName();
    if (tag == "name")
     name = bNode.getText(0);
    else if (tag == "status")
     status = bNode.getText(0);
    else if (tag == "description")
     description = bNode.getText(0);
    else if (tag == "item"){
     string i = bNode.getText(0);
     items.push_back(i);
    }
    else if (tag == "trigger"){
     trigger t(bNode);
     triggers.push_back(t);
    }
    bNode = aNode.getChildNode(i++);
  }while (!bNode.isEmpty());
}

void container::openContainer()
{
  status = "unlocked";
}

void container::gainItem(string name)
{
  items.push_back(name);
}

void container::loseItem(string name)
{
  vector<string>::iterator it;
  it = find(items.begin(), items.end(), name);
  if(it == items.end())
    cout << name << " not in container." << endl;
  else
   items.erase(it);
}

void container::updateStatus(string newStatus)
{
  status = newStatus;
}
