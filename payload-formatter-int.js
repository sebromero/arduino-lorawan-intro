function decodeUplink(input) {
  var sensorData = [];
  var intSize = 4; // Size of an int in bytes
  var buffer = new ArrayBuffer(input.bytes.length);
  var dataView = new DataView(buffer);
  input.bytes.forEach(function (value, index) {
    dataView.setUint8(index, value);
  });
  
  // Convert the bytes back into int values
  for (var i = 0; i < input.bytes.length; i += intSize) {
    var intValue = dataView.getInt32(i, true);
    sensorData.push(intValue);
  }

  var data = {
      bytes: input.bytes,
      sensorValue: sensorData[0],
  };

  return {
      data: data,
      warnings: [],
      errors: []
  };
}