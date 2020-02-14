const nativeoop = require("bindings")("nativeoop");

console.log("-=Server is starting=-"); //Log also into file and with current time
//Start
console.log("-=Server has started=-");


console.log(nativeoop.Start("Hello1"));
console.log(nativeoop.Update("Hello2"));
console.log(nativeoop.Signal("Hello3"));
console.log(nativeoop.Destroy("Hello4"));







console.log("-=Server has stopped=-");