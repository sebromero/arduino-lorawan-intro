/*
Sample data:
Temperature = 27.03 °C
Humidity    = 56.49 %
Pressure    = 97.51 kPa
Illuminance = 40.00 lx
*/

function decodeUplink(input) {
    var sensorData = [];
    var floatSize = 4; // Size of a float in bytes
    var buffer = new ArrayBuffer(input.bytes.length);
    var dataView = new DataView(buffer);
    input.bytes.forEach(function (value, index) {
      dataView.setUint8(index, value);
    });
    
    // Convert the bytes back into float values
    for (var i = 0; i < input.bytes.length; i += floatSize) {
      var floatValue = dataView.getFloat32(i, true);
      var roundedValue = Math.round(floatValue * 100) / 100;
      sensorData.push(roundedValue);
    }

    var data = {
        bytes: input.bytes,
        temperature: sensorData[0] + " °C",
        humidity: sensorData[1] + " %",
        pressure: sensorData[2] + " kPa",
        illuminance: sensorData[3] + " lx"
    };

    var warnings = [];
    if (sensorData.temperature < -5) {
        warnings.push("It's freezing cold 🥶");
    }

    return {
        data: data,
        warnings: warnings,
        errors: []
    };
}