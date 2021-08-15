![](banner.jpg)

# Arduino LoRaWAN Introduction
This repository contains the example code for The Things Summer Academy workshop about LoRaWAN devices.

# Provided Code
The following list explains for each sketch / code what it's intended for.

- **[ENVBlinkDemo](./ENVBlinkDemo)**:
A blink Arduino sketch that works also when the MKR ENV shield is connected to the MKR WAN 1300 board. The regular blink sketch from the IDE doesn't work in this scenario because some additional configuration needs to be done.

- **[ReadSensors](./ReadSensors)**:
An Arduino sketch that shows how to read from the MKR ENV shield sensors.
See: https://www.arduino.cc/en/Reference/ArduinoMKRENV

- **[LoRa-Dev-EUI](./LoRa-Dev-EUI)**:
An Arduino sketch that helps you to find out the device EUI which you will need to register your device with The Things Stack.

- **[LoRaWAN-Print-Channel-Mask](./LoRaWAN-Print-Channel-Mask)**:
An Arduino sketch that helps you to find out the channel mask for your desired channels to be enabled. This mask can then be used for joining a LoRaWAN network.

- **[LoRaWAN-Channel-Mask-Join](./LoRaWAN-Channel-Mask-Join)**:
An example Arduino sketch that shows you how to use channel masking to join The Things Stack. This may be required depending on where you're based. (E.g. US or AU).
More info can be found here: 
    - https://docs.arduino.cc/tutorials/mkr-wan-1310/lorawan-regional-parameters
    - https://www.thethingsnetwork.org/docs/lorawan/frequency-plans/
    - https://www.thethingsnetwork.org/docs/lorawan/regional-parameters/

- **[LoRaWAN-Message](./LoRaWAN-Message)**:
An Arduino sketch that shows how to send a simple string message to a LoRaWAN backend (e.g. The Things Stack).
See: https://www.arduino.cc/en/Reference/MKRWAN

- **[payload-formatter-string.js](./payload-formatter-string.js)**:
A javascript snippet that shows an implementation of a Payload Decoder which converts a bytes stream back into a human readable ASCII string.
See: https://www.thethingsindustries.com/docs/integrations/payload-formatters/javascript/

- **[ReadSensors-LoRaWAN](./ReadSensors-LoRaWAN)**:
An Arduino sketch that shows how to read from the MKR ENV shield sensors and send those values as floats to a LoRaWAN backend.

- **[payload-formatter-float.js](./payload-formatter-float.js)**:
A javascript snippet that shows an implementation of a Payload Decoder that unpacks float values from a byte stream and converts them into a javascript object.
See: https://www.thethingsnetwork.org/docs/devices/bytes/

- **[LoRaWAN-Downlink](./LoRaWAN-Downlink)**:
An Arduino sketch that shows you how to use downlink messages to control your Arduino board. In this sketch, a message with the data `01` turns the on-board LED on, a message with `00` turns it off. Keep in mind that downlink messages won't be received instantly. You may have to wait a few minutes until they are delivered to your device.

- **[ReadSensors-LoRaWAN-LowPower](./ReadSensors-LoRaWAN-LowPower)**:
An Arduino sketch that shows how to read from the MKR ENV shield sensors and send those values as floats to a LoRaWAN backend while using sleep modes to ensure maximum battery life.
See: https://www.arduino.cc/en/Reference/ArduinoLowPower

# Assignment
Will be uploaded when the workshop starts :-)


# Troubleshooting
If you encounter any errors in the Arduino IDE, please refer to the Arduino help center: https://support.arduino.cc/hc/en-us

# Relevant Links

- https://docs.arduino.cc/foundations/
- https://www.arduino.cc/reference/en/
- https://docs.arduino.cc/hardware/mkr-env-shield
- https://docs.arduino.cc/hardware/mkr-wan-1300