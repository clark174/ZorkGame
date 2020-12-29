#include <iostream>
#include <iostream>
#include <bits/stdc++.h>
#include "world.h"
#include "game.h"


using namespace std;

string bookFile = "game.xml";

vector<string> parseStr(string s) {
  vector<string> words;

  stringstream ss(s);

  while (ss.good()) {
      string substr;
      getline(ss, substr, ' ');
      words.push_back(substr);
  }
  return words;
}

Game::Game(string fileName, string id) {

  // Yuo will have to use the game ID to identify which game to use
  gameId=id;

  XMLNode aNode=XMLNode::openFileHelper(fileName.c_str(),"map");

  world=World(aNode);
}

Game::Game() {
}

string Game::processCommand(string id, string command) {
  vector<string> words;
  string message="";

// cout << "processCommand:" << id <<":" << command << endl;
  words = parseStr(command);
  
  if (gameStatus == "over") //If the ring has been destroyed, don't let the user make any more commands.
   message += "You beat the game! Restart the webpage to play again.\n";
  else if (words[0] == "go" || words[0] == "walk") {
    if (words.size() > 1) {
      string nextRoom=world.rooms[world.location].checkBorder(words[1]);
      if (nextRoom!="")
      {
        if (checkRoomTrigger(words, world.location)) //check the room triggers.
        {
          message += print + "\n";
        }
        else
        {
          world.location=nextRoom;
          message+= world.rooms[world.location].describe();
          if (checkRoomTrigger(blank, world.location)){ //check room triggers again.
           message += print + "\n";
          }
          message += world.rooms[world.location].listItems();
        }
       }
      else
       message += "There is nothing that way...\n";
    } else {
      message+="Go where?\n";
    }
  } else if (words[0] == "look") {
    message+= world.rooms[world.location].describe();
  } else if (words[0] == "i" || words[0] == "inventory") {
     if(world.inventory.size() == 0)
       message+="Nothing in inventory\n";
     else{
      message+= "Inventory: \n";
      for(int i=0; i<world.inventory.size();i++){
         message+= world.inventory[i];
         message+= "\n";
      }
     }
    }
    else if (words[0] == "take"){
     if (words.size()>1){
       //iterate through the current room's items list to see if the item is there.
       vector<string>::iterator it;
       it = find(world.rooms[world.location].items.begin(),world.rooms[world.location].items.end(),words[1]);
       if (it == world.rooms[world.location].items.end()){//if item is not in the room.
         if (checkItemTrigger(words, words[1])){
           message += print + ".\n";
         }
         else if (checkContainerTrigger(words, words[1])){
           message += print + ".\n";
         }
         else
          message += "Cannot take " + words[1] + ".\n";
       }
       else {
        world.inventory.push_back(world.items[words[1]].name); //add item to inventory.
	world.rooms[world.location].items.erase(it);  //remove item from the room.
        message+= words[1] + " added to inventory.\n";
        world.items[words[1]].addToInventory();
       }
     }
     else
      message+= "Take what?\n";
    }
    else if (words[0] == "read" || words[0] == "examine"){
     if(words.size()>1){
     //see if the item is in inventory.
      vector<string>::iterator it;
      it = find(world.inventory.begin(), world.inventory.end(), words[1]);
      if (it == world.inventory.end())
        message += words[1] + " not in inventory.\n";
      else
        message += world.items[words[1]].writing + "\n";
     }
     else
      message += "Read what?\n";
    }
    else if (words[0] == "drop"){
     if(words.size()>1){
       vector<string>::iterator it;
       it = find(world.inventory.begin(), world.inventory.end(), words[1]);
       if (it == world.inventory.end())
        message += words[1] + " is not in inventory.\n";
       else if (checkItemTrigger(words, words[1])){
        message += print + "\n";
       }
       else{
         world.inventory.erase(it); //remove item from inventory.
         world.rooms[world.location].items.push_back(words[1]); //add item to room.
         message += words[1] + " dropped\n";
         if (words[1] == "ring" && world.location == "MountDoom"){
          message += "You destroyed the One Ring! Victory!!!\n";
          gameStatus = "over";
         }
       }
      }
      else
        message += "Drop what?\n";
    }
    else if (words[0] == "open"){
     if(words.size()>1){ //see if container is in the room.
      vector<string>::iterator it;
      it = find(world.rooms[world.location].containers.begin(), world.rooms[world.location].containers.end(), words[1]);
      if (it == world.rooms[world.location].containers.end())
        message += words[1] + " is not in the room.\n";
      else if (checkContainerTrigger(words, words[1]))
      {
        message += print + "\n";
      }
      else{
       message += words[1] + " contains ";
       for (int i=0; i<world.containers[words[1]].items.size(); i++){
         message += world.containers[words[1]].items[i];
         world.rooms[world.location].items.push_back(world.containers[words[1]].items[i]); //add the items in the container to the room.
         world.items[world.containers[words[1]].items[i]].updateOwner(world.location); //change the item's owner to the room.
         if (i!=world.containers[words[1]].items.size()-1)
           message += ", ";
        }
        message += "\n";
        world.containers[words[1]].status = "unlocked";
        world.containers[words[1]].items.clear(); //remove all items from the container.
       }
      }
      else
       message += "Open what?\n";
     }
     else if (words[0] == "put"){
       if (words.size()>3){
         //first see if the item is in your inventory.
         vector<string>:: iterator it;
         it = find(world.inventory.begin(), world.inventory.end(), words[1]);
         if (it == world.inventory.end())
           message += words[1] + " not in inventory.\n";
         else{
          //second see if the container is in the room.
          vector<string>:: iterator it2;
          it2 = find(world.rooms[world.location].containers.begin(), world.rooms[world.location].containers.end(), words[3]);
          if (it2 == world.rooms[world.location].containers.end())
            message += words[3] + " not in room.\n";
          else{
           if(world.containers[words[3]].status == "unlocked"){
            world.inventory.erase(it);
            world.containers[words[3]].items.push_back(words[1]);
            message += words[1] + " added to " + words[3] + "\n";
            world.items[words[1]].owner = words[3];
           }
           else
            message += words[3] + " is locked.\n";
          }
         }
        }
        else
         message += "Put command requires four arguments (put (item) in (container)\n";
      }
      else if (words[0] == "activate" || words[0] == "use" ||  words[0] == "drink" || words[0] == "eat" || words[0] == "smoke" || words[0] == "wear"){
       if (words.size()>1){
        //see if item is in inventory.
        vector<string>::iterator it;
        it = find(world.inventory.begin(),world.inventory.end(),words[1]);
        if (it == world.inventory.end())
         message += words[1] + " not in inventory.\n";
        else if (checkItemTrigger(words, words[1])){
         message += print + "\n";
        }
        else{
         message += world.items[words[1]].turnons[0].print + "\n";
         if (world.items[words[1]].turnons[0].action != "")
          processCommand("jimmyclark", world.items[words[1]].turnons[0].action); //if the turnon has an action element, execute that action.
        }
       }
       else
        message += "Turn on what?\n";
      }
      else if (words[0] == "attack"){
       if (words.size() > 3){
         //check if creature is in the room.
         vector<string>::iterator it;
         it = find(world.rooms[world.location].creatures.begin(), world.rooms[world.location].creatures.end(), words[1]);
         if (it == world.rooms[world.location].creatures.end())
           message += words[1] + " is not in the room.\n";
         else{
          //check if item is in your inventory.
          vector<string>::iterator it2;
          it2 = find(world.inventory.begin(), world.inventory.end(), words[3]);
          if (it2 == world.inventory.end())
           message += words[3] + " is not in inventory.\n";
          else{
           if (checkCreatureTrigger(words, words[1]))
             message += print + "\n";
           else if (world.creatures[words[1]].vulnerability != words[3])
              message += words[3] + " is ineffective here. Need something else...\n";
           else{
             message += world.creatures[words[1]].attack + "\n"; //print out the attack message.
             world.rooms[world.location].creatures.erase(it); //remove the creature from the room.
             world.creatures[words[1]].killCreature(); //change creature status to dead.
             if (checkCreatureTrigger(blank, words[1]))
              message += print + "\n";
           }
          }
         }
        }
       else{
        message += "Error: Attack command requires four arguments (attack (creature) with (item)).\n";
       }
      }
    else if (words[0] == "hint"){
     message += world.rooms[world.location].hint + "\n";
    }
    else if (words[0] == "Add"){ //behind the scenes add function.
     if (words.size() > 4){
       if (words[1] == "item"){
        world.rooms[words[4]].items.push_back(words[2]);
       }
       else if (words[1] == "container"){
        world.rooms[words[4]].containers.push_back(words[2]);
       }
       else if (words[1] == "creature"){
        world.rooms[words[4]].creatures.push_back(words[2]);
       }
     }
    }
    else if (words[0] == "Update"){ //behind the scenes update function.
     if (words.size()>4){
       if (words[1] == "item"){
        world.items[words[2]].updateStatus(words[4]);
       }
       else if (words[1] == "container"){
        world.containers[words[2]].updateStatus(words[4]);
       }
       else if (words[1] == "creature"){
        world.creatures[words[2]].updateStatus(words[4]);
       }
      }
     }
    else
     message += "Error: Command not supported\n"; //default message.
  //cout << "game: " << message << endl;
  return message;
}

string Game::start(string id) {
  // your will need to ue ID for multiuser
  return world.rooms[world.location].describe() + world.rooms[world.location].listItems();
}

bool Game::checkContainerTrigger(vector<string> command, string name){
 for(int i=0; i<world.containers[name].triggers.size();i++) //iterate through all the triggers of the container.
  {
    vector<string> newWords = parseStr(world.containers[name].triggers[i].command);
    if (newWords == command)
    {
      string object = world.containers[name].triggers[i].aCondition.object;
      //check if object is a container.
      map<string, container>::iterator it;
      it = world.containers.find(object);
      if (it != world.containers.end())
      {
        if (world.containers[object].status == world.containers[name].triggers[i].aCondition.status) //if the status condition is met.
          {
          print = world.containers[name].triggers[i].print;
          return true;
          }
      }
      
      //check if object is an item.
      map<string, item>::iterator it2;
      it2 = world.items.find(object);
      if (it2 != world.items.end())
      {
        if (world.items[object].status == world.containers[name].triggers[i].aCondition.status || world.items[object].owner == world.containers[name].triggers[i].aCondition.owner)
          {
          print = world.containers[name].triggers[i].print;
          world.containers[name].status = world.containers[name].triggers[i].action;
          return true;
          }
      }

      //check if object is a creature.
      map<string, creature>::iterator it3;
      it3 = world.creatures.find(object);
      if (it3 != world.creatures.end())
      {
        if (world.creatures[object].status == world.containers[name].triggers[i].aCondition.status)
          {
          print = world.containers[name].triggers[i].print;
          return true;
          }
      }
    }
  }
 return false;
}

bool Game::checkItemTrigger(vector<string> command, string name){
 for(int i=0; i<world.items[name].triggers.size();i++)
  { 
    vector<string> newWords = parseStr(world.items[name].triggers[i].command);
    if (newWords == command || world.items[name].triggers[i].command == "")
    {
      string object = world.items[name].triggers[i].aCondition.object;
      //check if object is a container.
      map<string, container>::iterator it;
      it = world.containers.find(object);
      if (it != world.containers.end())
      {
        if (world.containers[object].status == world.items[name].triggers[i].aCondition.status)
          {
          print = world.items[name].triggers[i].print;
          return true;
          }
      }
      
      //check if object is an item.
      map<string, item>::iterator it2;
      it2 = world.items.find(object);
      if (it2 != world.items.end())
      {
        if (world.items[object].status == world.items[name].triggers[i].aCondition.status || world.items[object].owner == world.items[name].triggers[i].aCondition.owner)
          {
          print = world.items[name].triggers[i].print;
          if (world.items[name].triggers[i].action != "")
            processCommand("jimmyclark", world.items[name].triggers[i].action);
          return true;
          }
      }

      //check if object is a creature.
      map<string, creature>::iterator it3;
      it3 = world.creatures.find(object);
      if (it3 != world.creatures.end())
      {
        if (world.creatures[object].status == world.items[name].triggers[i].aCondition.status)
          {
          print = world.items[name].triggers[i].print;
          if (world.items[name].triggers[i].action != "")
           processCommand("jimmyclark", world.items[name].triggers[i].action);
          return true;
          }
      }
    }
  }
 return false;
}

bool Game::checkRoomTrigger(vector<string> command, string name){
 for(int i=0; i<world.rooms[name].triggers.size();i++)
  {
    vector<string> newWords = parseStr(world.rooms[name].triggers[i].command);
    if (newWords == command || command == blank && world.rooms[name].triggers[i].command == "") //had to revise the second argument since some room triggers don't have command elements.
    {
      string object = world.rooms[name].triggers[i].aCondition.object;
      //check if object is a container.
      map<string, container>::iterator it;
      it = world.containers.find(object);
      if (it != world.containers.end())
      {
        if (world.containers[object].status == world.rooms[name].triggers[i].aCondition.status)
          {
          print = world.rooms[name].triggers[i].print;
          return true;
          }
      }
      
      //check if object is an item.
      map<string, item>::iterator it2;
      it2 = world.items.find(object);
      if (it2 != world.items.end())
      {
        if (world.items[object].status == world.rooms[name].triggers[i].aCondition.status || world.items[object].owner == world.rooms[name].triggers[i].aCondition.owner)
          {
          print = world.rooms[name].triggers[i].print;
          return true;
          }
      }

      //check if object is a creature.
      map<string, creature>::iterator it3;
      it3 = world.creatures.find(object);
      if (it3 != world.creatures.end())
      {
        if (world.creatures[object].status == world.rooms[name].triggers[i].aCondition.status)
          {
          print = world.rooms[name].triggers[i].print;
          return true;
          }
      }
    }
  }
 return false;
}

bool Game::checkCreatureTrigger(vector<string> command, string name){
if (command.size()>0){
 if (command[0] == "attack"){
  command.erase(command.begin()+2, command.end());
 }
}
 for(int i=0; i<world.creatures[name].triggers.size();i++)
  {
    vector<string> newWords = parseStr(world.creatures[name].triggers[i].command);
    if (newWords == command || command == blank && world.creatures[name].triggers[i].command == "")
    {
      string object = world.creatures[name].triggers[i].aCondition.object;
      //check if object is a container.
      map<string, container>::iterator it;
      it = world.containers.find(object);
      if (it != world.containers.end())
      {
        if (world.containers[object].status == world.creatures[name].triggers[i].aCondition.status)
          {
          print = world.creatures[name].triggers[i].print;
          return true;
          }
      }
      
      //check if object is an item.
      map<string, item>::iterator it2;
      it2 = world.items.find(object);
      if (it2 != world.items.end())
      {
        if (world.items[object].status == world.creatures[name].triggers[i].aCondition.status || world.items[object].owner == world.creatures[name].triggers[i].aCondition.owner)
          {
          print = world.creatures[name].triggers[i].print;
          return true;
          }
      }

      //check if object is a creature.
      map<string, creature>::iterator it3;
      it3 = world.creatures.find(object);
      if (it3 != world.creatures.end())
      {
        if (world.creatures[object].status == world.creatures[name].triggers[i].aCondition.status)
          {
          print = world.creatures[name].triggers[i].print;
          if (world.creatures[name].triggers[i].action != ""){
           processCommand("jimmyclark",world.creatures[name].triggers[i].action);
          }
          return true;
          }
      }
    }
  }
 return false;
}

