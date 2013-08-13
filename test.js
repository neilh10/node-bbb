var bbb = require('./build/Release/bbb');

console.log("P8_28 => GPIO(" + bbb.getGpio("P8_28") + ")");
console.log("P8_28 => Header(" + bbb.getHeader("P8_28") +") Pin(" + bbb.getPin("P8_28") + ")");
