function Decoder(bytes, port) {
    const codeString = bin2String(bytes);
    
    const [
      gas,
      hum,
      temp,
    ] = codeString.split(";")
    
    return {
      gas: Number(gas),
      hum: Number(hum),
      temp: Number(temp)
    };
  }
  
  function bin2String(array) {
    var result = "";
    for (var i = 0; i < array.length; i++) {
      result += String.fromCharCode(array[i]);
    }
    return result;
  }