#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
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
using namespace cgicc; // Needed for AJAX functions.

// fifo for communication
string receive_fifo = "Namereply";
string send_fifo = "Namerequest";

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  // Create AJAX objects to recieve information from web page.
  form_iterator idit = cgi.getElement("id");
  form_iterator commandit = cgi.getElement("command");

  string id = **idit;
  string command = **commandit;

  // Output header for CGI
  cout << "Content-Type: text/plain\n\n";

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);

  string message = id+"$" + command;
  //	message = "$FEMALE*" + name;
  sendfifo.openwrite();
  sendfifo.send(message);

  /* Get a message from a server */

  string reply;
  recfifo.openread();
  reply = recfifo.recv();
    
  recfifo.fifoclose();
  sendfifo.fifoclose();
  cout  << reply << endl;

return 0;
}
