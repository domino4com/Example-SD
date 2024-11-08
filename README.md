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
- [Official Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
- [Easier Guide](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

# Two projects avaialble:
- domino4_SD_card_BuiltIn
- domino4_SD_card_Expansion_port

## domino4_SD_card_Expansion_port
This runs on both the CWA V2+ and the CWV/CWN V5+ cores using the SD Card Expansion Port module. Since both cores are allocating the same pins to both xChips (I2C) and the Expansion Port (SPI, etc), the code will compile and work on both without modifications.

With no delay in the loop, this sketch reads sensor data and writes them to the SD Card every ~13ms.
It is possible to speed up this by only open and closing the file, say every 10000 loops, to ~8ms.
It could possibly be faster by using the second core to just do SD Card functions.

## domino4_SD_card_BuiltIn
This only runs on the CWV/CWN V5+ cores using the builtin SD Card slot.

With no delay in the loop, this sketch reads sensor data and writes them to the SD Card every ~19ms.

# Button Usage

## Native PROGRAM/DOWNLOAD mode
In certain instances the CWA/CWV/CWN will not enter PROGRAM/DOWNLOAD by itself when Arduino uploads a sketch. Typically first time you want to program the core, if for example a UF2 bootloader have been installed. It might also show a Serial/USB port that says something else than `...(ESP32 Family Device)`. If that happens, you can force the core into PROGRAM/DOWNLOAD mode:
- Press and keep holding &#x25B6; down
- Click &#x21BB;
- Release &#x25B6;
- :red_circle: will illuminate **_continuously_**, verifying that the core is in PROGRAM/DOWNLOAD mode

If you have manually entered PROGRAM/DOWNLOAD as per above, you also need to manually reset the circuit:
- Click &#x21BB;
- :red_circle: will stop illuminating, verifying that the core is in EXECUTION/RUN mode (unless your program purposefully are illuminating the LED!)

## UF2 Bootload mode
The core arrives with a UF2 bootloader installed, making it easier to just drag-and-drop a readymade application to the core.
The bootloader is in bootloading mode, if you see this:
- A drive on your computer saying `CWA`
- :red_circle:  illuminated by **_pulsing_**.
- :green_circle:  illuminated **_continuously_**.

If you **haven't** loaded any application onto the core, it will illuminate the LEDs as per above. If you **have** loaded an application onto the core, it will be running that application.
To reactivate the bootloader:
- Double-click on &#x21BB;
- The above LEDs and drive should now be visible.

### More about the UF2 Bootloader and readymade applications: 
[apps.maxiq.space](https://apps.maxiq.space/)

## Programming in Arduino or PlatformIO
When you program the core in Arduino or using PlatformIO, you will overwrite the UF2 bootloader, which is perfectly allright, unless you want to use it to load applications:
- Reload UF2 Bootloader, go to [apps.maxiq.space](https://apps.maxiq.space/)

All GPIO pins for the CWA v2 is listed here: [domino4.com/CWA](domino4.com/CWA), but for the CWN v5, here is a short list of the extra defined pins:
- CAN-bus:
  - CAN_RX = 6
  - CAN_TX = 7
- SD Card ChipSelect:
  - SD_CS = 3

# Troubleshooting
## This software was tested using:
- Arduino v2.3.3
- Board Manager: **Arduino ESP32 Boards** by Arduino v.2.0.18-20240930.arduino3
## Debug
You can debug the code 3 different ways:
- In the Arduino menu, choose `Tools → Core Debug Level → Verbose`
- By using the USB-C port on the core, you also have access to the [Arduino Debugger](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-debugger/). Give it a try, it is a powerful tool to master!
- Go old school, and insert a stack of `Serial.println(...variable...);` into your code
## SD Card ?  
If you have inserted a SD Card, but it says `Card Mount Failed.`, it is very likely the SD-card that is problematic:
- Make sure the SD-Card is maximum 32Gb
- Make sure it is formatted as it arrived out of the box:
   - Use this formatter only: [SD Memory Card Formatter for Windows/Mac](https://www.sdcard.org/downloads/formatter/). Any other formatter does not guarantee correct formatting!
   - Do **not** use the `Quick format`, make sure you use the `Overwrite format`. It takes longer, but it is the only way to guarantee correct formatting

