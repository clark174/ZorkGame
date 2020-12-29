/***************************************************************************
 * gameserver.cpp  -   game server
 *
 * copyright : (C) 2020 by Jim Skon
 *
 * This program runs as a background server to a CGI program, providinging US Census
 * Data on the frequency of names in response to requestes.  The rational for this
 * is to demonstrait how a background process can serve up information to a web program,
 * saving the web program from the work of intiallizing large data structures for every
 * call.
 *
 *
 *
 ***************************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "fifo.h"
#include "game.h"

using namespace std;

/* Fifo names */
string receive_fifo = "Namerequest";
string send_fifo = "Namereply";

/* Name of name data files */
string gamefile = "game.xml";

std::string
replaceAll( std::string const& original, std::string const& from, std::string const& to )
{
    std::string results;
    std::string::const_iterator end = original.end();
    std::string::const_iterator current = original.begin();
    std::string::const_iterator next = std::search( current, end, from.begin(), from.end() );
    while ( next != end ) {
        results.append( current, next );
        results.append( to );
        current = next + from.size();
        next = std::search( current, end, from.begin(), from.end() );
    }
    results.append( current, next );
    return results;
}

/* Server main line,create name MAP, wait for and serve requests */
int main() {

  string inMessage, outMessage;

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);

  string command;
  Game *theGame;


  while (1) {
    size_t pos;
    string gameId;

    /* Get a message from a client */
    recfifo.openread();
    inMessage="";
    inMessage = recfifo.recv();
    /* Parse the incoming message */
    /* Form:  $type*name  */
    pos=inMessage.find_first_of("$");
    if (pos!=string::npos) {
      gameId = inMessage.substr(0,pos);
      pos++;
    } else {
      cout << "Bad Message " << inMessage << endl;
      continue;
    }
    command = inMessage.substr(pos,2000);
    cout << "Message:" << command << ":" << gameId << endl;
    outMessage = "";

    if (command == "Start") {
      theGame = new Game(gamefile,gameId);
      outMessage = theGame->start(gameId);
    } else {
      outMessage = theGame->processCommand(gameId,command);
    }

    outMessage=replaceAll( outMessage, "\n", "<br/>" );
    cout << " Results: " << outMessage << endl;

    sendfifo.openwrite();
    sendfifo.send(outMessage);
    sendfifo.fifoclose();
    recfifo.fifoclose();

  }
}
