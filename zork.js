// you will need to generate a unique id for each user
var id="jimmyclark"

var world;
// Actions to get things started
$(document).ready(function () {

    $('#command-btn').click(command);

    var input = document.getElementById("command");
    // Respond to enter key
    input.addEventListener("keyup", function(event) {
      // Number 13 is the "Enter" key on the keyboard
      if (event.keyCode === 13) {
        // Cancel the default action, if needed
        event.preventDefault();
        // Trigger the button element with a click
        command();
      }
    });

    processCommand("Start");
});



// Print to terminal, and clear the input
function printLine(text) {
  $('#term').append(text+"<br />");
  var objDiv=$('#term')[0];
  objDiv.scrollTop = objDiv.scrollHeight;
}

//Input and process Command
// Called from submit button or enter
function command() {
  com=$('#command').val();
  $('#command').val("");
  printLine("<span style='color:blue'>>>> "+com+"</span>");
  processCommand(com.toLowerCase());
}

function processCommand(command) {
    if (command.length<1) {
      return;
    }
    command = command.split(' ').join('+');
    console.log(command,id);
    $('#command').val("");
    $.ajax(
    {
    type: "get",
    url: "/cgi-bin/clark1_gamewebclient.cgi?id=" + id + "&command=" + command,
    dataType: "text",
    success:  processResults,
    error: function(request, ajaxOptions, thrownError)
    {
        $("#debug").text("error with get:"+request+thrownError);
    }
  });
}

function processResults(results) {
  console.log(results);
  printLine(results);
}
