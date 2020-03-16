import {SocketServer} from './wip/Server';

console.log("-=Server has started=-");

let app = new SocketServer();
export {app};

console.log("-=Server has stopped=-");