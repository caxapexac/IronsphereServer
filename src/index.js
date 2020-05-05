const WebSocket = require("ws");
const nativeoop = require("bindings")("nativeoop");

const DeltaTime = 1111;

console.log("-=Server has started=-");


console.log(nativeoop.Signal("Hello3"));

const wss = new WebSocket.Server({ port: 1109 });
 
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(message) {
    console.log('received: %s', message);
  });

  
  ws.send('something');
});

wss.on('close', function connection(ws) {
    console.log(`${ws} close`);
})

wss.on('error', function connection(ws) {
    console.log(`${ws} error`);
})


function GameLoop() {
    console.log("I'm alive");

    let response = nativeoop.Update();
    let responseObj = JSON.parse(response);
    for (let i in responseObj) {
        console.log(i);
    }
   
}

setInterval(GameLoop, DeltaTime);

//console.log("-=Server has stopped=-");
