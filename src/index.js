const WebSocket = require("ws");
const fs = require("fs");
const path = require("path");
const query = require("cli-interact").getYesNo;
const nativeoop = require("bindings")("nativeoop");

// Default data

if (!fs.existsSync("database.json")) {
    fs.writeFileSync("database.json", {
        users : []
    });
}

if (!fs.existsSync("config.json")) {
    fs.writeFileSync("config.json", {
        title: "Ironsphere Game Server",
        port: 1109,
        delta_time: 1111,
    });
}

// Server

console.log("Server is loading...");

const database = JSON.parse(fs.readFileSync("database.json", "utf8"));
console.log(`Database loaded. ${Object.keys(database.users).length} users was registred so far.`);

const config = JSON.parse(fs.readFileSync("config.json", "utf8"));
console.log(`Config of ${config.title} was loaded. Opening ${config.port} port. Server tick every ${config.delta_time} ms`);

const connections = {};
const wss = new WebSocket.Server({ port: config.port });

console.time(`${config.title} has started`);


wss.on("connection", function connection(ws) {
    ws.on("message", function incoming(message) {
            Signal(ws, message);
    });
    ws.send("I'm alive");
});

wss.on("close", function connection(ws) {
    // TODO remove connections with value ws or maybe check ws.readyState === WebSocket.OPEN
    //nativeoop.OnDisconnect(connections where player_uid : ws)
    console.log(`${ws} close`);
});

wss.on("error", function connection(ws) {
    console.log(`${ws} error`);
});


function Signal(ws, message) {
    var messageJson = JSON.parse(message);

    if (!messageJson.has("sender")) {
        if (!messageJson.has("nickname")) {
            console.log(`! Message from unknown socket: ${message}`);
            return;
        }

        var nickname = messageJson.nickname;
        if (!database.users.has(nickname)) {
            // Register
            database.users.push(nickname);
        }

        var result = {users: database.users};
        ws.send(result); // SecurEEty
        return;
    }

    // Login
    connections[messageJson.sender] = ws;

    // Logic
    var response = nativeoop.Signal(message);
    ws.send(response);

    // TODO temporary
    var responseJson = JSON.parse(response);
    console.log(
        `signal ${message} \nRESPONSE\n ${JSON.stringify(responseJson, null, 2)} \n`
    );
    // TODO
}

var GameLoop = function () {
    let response = nativeoop.Update();
    let responseObj = JSON.parse(response);
    config.delta_time = responseObj.delta_time;

    // TODO
    console.log(`TODO chat: ${responseObj.chat_buffer}`);

    for (var sessionId in responseObj.sessions) {
        var session = responseObj.sessions[sessionId];
        for (var playerId in session.players_data) {
            var playerData = sessions.players_data[playerId];
            if (users.has(playerId)) {
                users.get(playerId).send(JSON.stringify(playerData));
            } else {
                console.log(`${playerId} doesn't connected`);
            }
        }
    }
    console.log("Loop");
    // TODO

    setTimeout(GameLoop, config.delta_time);
};

setTimeout(GameLoop, config.delta_time);

var answer = query("Server is working. Type 'Y' to stop the server");

console.log("Saving database...");
fs.writeFileSync("database.json", JSON.stringify(database));

console.log("Saving config...");
fs.writeFileSync("config.json", JSON.stringify(config));

console.timeLog("Uptime: ")
console.log(`-=${config.title} has stopped=-`);
