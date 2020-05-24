const WebSocket = require("ws");
const fs = require("fs");
const path = require("path");
const query = require("cli-interact").getYesNo;
const nativeoop = require("bindings")("nativeoop");

// Default data

if (!fs.existsSync("database.json")) {
    fs.writeFileSync("database.json", JSON.stringify({
        users : []
    }, null, 2));
}

if (!fs.existsSync("config.json")) {
    fs.writeFileSync("config.json", JSON.stringify({
        title: "Ironsphere Game Server",
        version: 104,
        port: 1109,
        delta_time: 1111,
        chat_capacity: 100
    }, null, 2));
}

// Server

console.log("Server is loading...");

const database = JSON.parse(fs.readFileSync("database.json", "utf8"));
console.log(`Database loaded. ${Object.keys(database.users).length} users was registred so far.`);

const config = JSON.parse(fs.readFileSync("config.json", "utf8"));
console.log(`Config of ${config.title} was loaded. Opening ${config.port} port. Server tick every ${config.delta_time} ms`);
nativeoop.Start(JSON.stringify(config));

const connections = {};
const wss = new WebSocket.Server({ port: config.port });

console.time("uptime");
console.log(`-=${config.title} has started=-`);

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
    let messageJson = JSON.parse(message);

    if (messageJson.version != config.version) {
        console.log(`! Message with version ${messageJson.version} from player ${messageJson.sender}`);
        ws.send({error: "Please download the latest version of the game"});
    }

    if (!messageJson.has("sender")) {
        if (!messageJson.has("nickname")) {
            console.log(`! Message from unknown socket: ${message}`);
            ws.send({error: "Please send your nickname and then uid"});
            return;
        }

        let nickname = messageJson.nickname;
        if (!database.users.has(nickname)) {
            // Register
            database.users.push(nickname);
        }

        let result = {users: database.users};
        ws.send(result); // SecurEEty
        return;
    }

    // Login
    connections[messageJson.sender] = ws;

    // Logic
    let response = nativeoop.Signal(message);
    ws.send(response);

    // TODO temporary
    let responseJson = JSON.parse(response);
    console.log(
        `signal ${message} \nRESPONSE\n ${JSON.stringify(responseJson, null, 2)} \n`
    );
    // TODO
}

const GameLoop = function () {
    let response = nativeoop.Update();
    let responseObj = JSON.parse(response);

    // Server handling:
    config.delta_time = responseObj.delta_time;
    console.log(`Loop ${config.delta_time}`);

    // Broadcast handling:
    wss.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(responseObj.broadcast));
        }
    });

    // Players handling:
    for (let sessionId in responseObj.players_sessions) {
        for (let playerId in responseObj.players_sessions[sessionId]) {
            if (connections.has(playerId)) {
                connections[playerId].send(JSON.stringify(responseObj.players_sessions[sessionId][playerId]))
            }
            else {
                console.log(`${playerId} (session ${sessionId}) doesn't connected`);
            }
        }
    }

    setTimeout(GameLoop, config.delta_time);
};

setTimeout(GameLoop, config.delta_time);

console.log("Server is working. Ctrl+C to stop the server");

function Stop() {
    console.log("Saving database...");
    fs.writeFileSync("database.json", JSON.stringify(database, null, 2));
    
    console.log("Saving config...");
    fs.writeFileSync("config.json", JSON.stringify(config, null, 2));
    
    console.timeLog("uptime")
    console.log(`-=${config.title} has stopped=-`);
    process.exit(0);
}

process.on('SIGINT', Stop);
process.on('SIGQUIT', Stop);
process.on('SIGTERM', Stop);