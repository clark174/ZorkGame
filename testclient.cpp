#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "fifo.h"

using namespace std;
string receive_fifo = "Namereply";
string send_fifo = "Namerequest";
string gameId="ZorkCPPSkon";

int main() {
  string message, name;
  string reply;
  string type;

  // create the FIFOs for communication
	Fifo recfifo(receive_fifo);
	Fifo sendfifo(send_fifo);



  // Do the start
  sendfifo.openwrite();
	sendfifo.send(gameId+"$Start");

	/* Get a message from a server */
	recfifo.openread();
	reply = recfifo.recv();
  cout << reply << endl;

	recfifo.fifoclose();
	sendfifo.fifoclose();


  while (1) {
    string command;
    cout << ">>> ";
  	getline(cin,command);
  	transform(command.begin(), command.end(), command.begin(), ::tolower);

  	message = gameId+"$" + command;
  	//	message = "$FEMALE*" + name;
  	sendfifo.openwrite();
  	sendfifo.send(message);

  	/* Get a message from a server */
  	recfifo.openread();
  	reply = recfifo.recv();

  	recfifo.fifoclose();
  	sendfifo.fifoclose();
  	cout  << reply << endl;
  }


}
