# Hands-On Learning Preparation
Prior to hands-on learning to learn how to `control the actuators` and `acquire data from the sensors` on NodeMCU ESP32, we have to make sure the hardware and software (3 things below) is readily accesible on your desk and on your PC:
1. **NodeMCU ESP32** and a **USB cable Type-A to Type-C**.
2. **Arduino IDE**. Download it from it's official website [Arduino Software](https://www.arduino.cc/en/software) page and install it on your PC. Current version is 2.2.3.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-download.png" width="800"></a></p>

Or you can directly download from here:
* [Windows 10 and newers (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Windows_64bit.exe)
* [Linux AppImage (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Linux_64bit.AppImage)
* [Linux Zip File (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Linux_64bit.zip)
* [Mac OS Intel, 10.15: "Catalina" or newer (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_macOS_64bit.dmg)
* [Mac OS Apple Silicon, 11: "Big Sur" or newer (64 bits)](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_macOS_arm64.dmg)

3. **Arduino core for the ESP32** in the Arduino IDE, [Github](https://github.com/espressif/arduino-esp32). If you don't install it yet on your Arduino IDE, follow this [instructions](#install-esp32-arduino-core-using-arduino-ide-boards-manager-7-steps).

### Install ESP32 Arduino Core using Arduino IDE Boards Manager (7 Steps)

1. On the Arduino IDE, go to menu: ***File > Preferences***.
2. Click on ***Window icon*** beside the Additional board manager URLs field.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-menu-preferences-boards.png" width="800"></a></p>

3. Copy the URLs below and paste it into the ***Additional Boards Manager URLs*** field and click the ***OK*** button.
**`https://espressif.github.io/arduino-esp32/package_esp32_index.json`**

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-menu-preferences-board-url.png" width="800"></a></p>

4. Click the ***OK*** button to exit the Preferences window.
5. Open the ***Boards Manager*** on the left panel and search keyword: ***esp32***
6. Look for ***esp32** by Espressif Systems* and click the **INSTALL** button (Current version is 2.0.15).

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32-install.png" width="800"></a></p>

7. Wait until the installation process is done, which would take several minutes, until the status on the board is *`2.0.x installed`*.

<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-hardware-library-esp32-installed.png" width="800"></a></p>

## Download and Install USB Driver in Your PC
Download CH340 USB Driver from their official website [CH341SER.EXE](https://www.wch-ic.com/downloads/CH341SER_EXE.html)

## Connect NodeMCU ESP32 to Your PC (6 Steps)
1. Connect the USB cable Type-C to NodeMCU ESP32 and Type-A to your PC.
2. On the Arduino IDE, choose the correct *COM port* interfaced to CP2104 USB driver on NodeMCU ESP32.

`On Windows OS` Example: *COM5*
<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-com-port.png" width="800"></a></p>

`On Mac OS` Example: */dev/cu.usbserial-XXXXXXXXX*
<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-com-port-mac.png" width="800"></a></p>

3. On the board selection, choose *ESP32 Dev Module*.

`On Windows OS`
<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-com-board.png" width="800"></a></p>

`On Mac OS`
<p align="center"><img src="https://github.com/myinvent/hibiscus-sense/raw/main/references/arduino-ide-com-board-mac.png" width="800"></a></p>