#include <iostream>
#include "border.h"

Border::Border(XMLNode aNode) {
  int i=0;
  XMLNode bNode=aNode.getChildNode(i++);
  do {
    string tag=bNode.getName();
    //cout << "Border:" << tag << ":" << bNode.getText(0) << endl;
    if (tag == "name") {
      name=bNode.getText(0);
    } else if (tag == "direction") {
      direction=bNode.getText(0);
    }
    bNode=aNode.getChildNode(i++);
  } while (!bNode.isEmpty());
}

Border::Border(){
  name = "";
  direction = "";
}
