# Example SD
Example files for using SD Card

### IWA & IIA
The examples uses the IWA and IIA xChips:
Install them by downloading the .zip files of:
- [IWA](https://github.com/domino4com/IWA)
- [IIA](https://github.com/domino4com/IIA)
If you don't know how, follow these [instructions](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/)

### ArduinoJSON
xChips also uses the ArduinoJSON library v7. [Installation guide](https://arduinojson.org/v7/how-to/install-arduinojson/)

### Other libraries
... are installed when you install the ESP32S3 board files: 
- (Official Guide)[https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html]
- (Easier Guide)[https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/]


# Two projects avaialble:
- domino4_SD_card_BuiltIn
- domino4_SD_card_Expansion_port

## domino4_SD_card_Expansion_port
This runs on both the CWA V2+ and the CWV/CWN V5+ cores using the SD Card Expansion Port module. Since both cores are allocating the same pins to both xChips (I2C) and the Expansion Port (SPI, etc), the code will compile and work on both withour modifications.

## domino4_SD_card_BuiltIn
This only runs on the CWV/CWN V5+ cores using the builtin SD Card slot.

