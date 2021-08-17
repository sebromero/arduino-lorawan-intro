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

      // The following line rounds the value to two digits
      // by multiplying it by 100, rounding the integer and
      // then dividing it again by hundred.
      var roundedValue = Math.round(floatValue * 100) / 100;
      sensorData.push(roundedValue);
    }

    var data = {
        bytes: input.bytes,
        temperature: sensorData[0] + " °C",
        humidity: sensorData[1] + " %",
        pressure: sensorData[2] + " kPa",
        illuminance: illuminance + " lx"
    };

    return {
        data: data,
        warnings: [],
        errors: []
    };
}