// Text decoder
function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};
  decoded.myVal = String.fromCharCode.apply(null, bytes);
  return decoded;
}

// TinyLoRa - DHT11 Decoder
function Decoder(bytes, port) {
  var decoded = {};
 
  // Decode bytes to int
  var celciusInt = (bytes[0] << 8) | bytes[1];
  var humidInt = (bytes[2] << 8) | bytes[3];
  
  // Decode int to float
  decoded.celcius = celciusInt / 100;
  decoded.humid = humidInt / 100;
 
  return decoded;
}