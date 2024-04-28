# Chemical Miller ESP32

In this project of C2 P1 of mechatronics engineering, I made a ball mill, which has the purpose of grinding chemical elements (one or more) with the point of making a uniform and fine union between the two elements.

The objective of the project is to make a uniform and fine mixture of two chemical elements to perform a combustion, the combustion must not have residues, so it must be a well done grinding.

Frontend of this project: [Miller-front](https://github.com/jdic/MIller-front).

## Hardware requirements

- ESP32
- DC Motor
- Bridge H L298
- Buzzer

## Software Requirements

- [VSCode](https://code.visualstudio.com/)
- Extensions:
  - [PlatformIO](https://platformio.org/)
  - [C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- Libraries:
  - ESPAsyncWebServer
  - SPIFFS
  - WiFi

## Configuration

1. Connect the ESP32 to the DC motor and the steering control module, if necessary.
2. Upload the provided code to the ESP32 using the PlatformIO Extensiom.
3. Set the network name (SSID) and WiFi password in the code.
4. Upload the HTML, CSS and JavaScript files to the ESP32's SPIFFS file system.

## Usage

1. Turn on the ESP32.
2. Connect a device to the same network created by the ESP32.
3. Open a web browser on the device and access the IP address assigned to the ESP32.
4. Use the web interface to control the speed, direction and status of the mill.

## Functionalities

- **Speed Control**: Adjusts the motor speed by means of a slider on the web interface.
- **Direction Control**: Changes the direction of rotation of the motor between forward and reverse.
- **Activation Status**: Allows the motor to be activated or deactivated from the web interface.
- **Audible Notifications**: Buzzing sounds are emitted as confirmation of actions performed.

This project was created by JMota during the C2 P1.