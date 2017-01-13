function str2ab(str) {
  var buf = new ArrayBuffer(str.length*2); // 2 bytes for each char
  var bufView = new Uint16Array(buf);
  for (var i=0, strLen=str.length; i<strLen; i++) {
    bufView[i] = str.charCodeAt(i);
  }
  return buf;
}
let connectionId

$(document).ready(function(){
  chrome.serial.getDevices(function(devices){
    $devices = $('#devices')
    devices.forEach(function(device){
      $devices.append('<div>' + device.path + '</div>')
    })

    $devices.on('click', '> div', function(){
      link = $(this)
      chrome.serial.connect(link.text(), function(info){
        if(info){
          connectionId = info.connectionId
          link.html(link.text() + ' <strong style="color:red">CONNECTED</strong>')
        }
      })

      chrome.serial.onReceive.addListener(function(received){
        console.warn('received', received)
      })
    })
  })

  $('#drive, #steer').on('change', function(){
    chrome.serial.send(connectionId, str2ab('left'), function(info){
      console.warn('cb send', info)
    })
    $(this).parent().find('.debug').text($(this).val())
  })
})
