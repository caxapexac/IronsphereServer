const WebSocket = require("ws");
const nativeoop = require("bindings")("nativeoop");

const DeltaTime = 1111;
const connections = new Map();

console.log("-=Server has started=-");

const wss = new WebSocket.Server({ port: 1109 });
 
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(message) {
    Signal(ws, message);
  });
  ws.send("I'm alive");
});

wss.on('close', function connection(ws) {
    console.log(`${ws} close`);
})

wss.on('error', function connection(ws) {
    console.log(`${ws} error`);
})

function Signal(sender, message) {
  var messageJson = JSON.parse(message);
  if (!connections.has(messageJson.sender)) {
    connections.set(messageJson.sender, sender);
  }

  var response = nativeoop.Signal(message);
  var responseJson = JSON.parse(response);
  console.log (`signal ${message} \nRESPONSE\n ${JSON.stringify(responseJson, null, 2)} \n`);
}

var GameLoop = function() {
  let response = nativeoop.Update();
  let responseObj = JSON.parse(response);
  DeltaTime = responseObj.delta_time;
  console.log(`TODO chat: ${responseObj.chat_buffer}`);
  for (var sessionId in responseObj.sessions) {
    var session = responseObj.sessions[sessionId];
    for (var playerId in session.players_data) {
      var playerData = sessions.players_data[playerId];
      if (connections.has(playerId)) {
        connections.get(playerId).send(JSON.stringify(playerData));
      }
      else {
        console.log(`${playerId} doesn't connected`);
      }
    }
  }

  console.log("Loop");
  setTimeout(GameLoop, DeltaTime);
}

setTimeout(GameLoop, DeltaTime);

//console.log("-=Server has stopped=-");
