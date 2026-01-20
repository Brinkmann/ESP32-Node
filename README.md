# Football Eye Q - Node Firmware

## Description

This repository houses the **Node** firmware for the Football Eye Q project. It is **node-only** firmware and will not build as a Hub/Controller.

These Node devices act as the receivers in the system. They connect via a low-latency **ESP-NOW** mesh network to the main **Hub Controller**. Their primary function is to receive commands from the Hub and drive the attached RGB LED strips accordingly.

**Note:** This firmware is designed to work in tandem with the Hub Controller. You can find the Hub firmware repository here: [Football Eye Q - Hub/Main Repo](https://github.com/Brinkmann/ESP32-Main)

## Table of Contents

- [Features](#features)
- [Materials](#materials)
- [IDE_Installation](#IDE_Installation)
- [Libraries_Installation](#Libraries_installation)
- [Usage](#usage)
- [Node Identity in the Mesh](#node-identity-in-the-mesh)

## Features

- **ESP-NOW Receiver:** Listens for low-latency broadcast or unicast commands from the Hub.
- **LED Control:** Drives WS2813 RGB LED strips (up to 60 LEDs).
- **Auto-Timeout:** Automatically turns off LEDs after inactivity to save power.
- **Long Range Wi-Fi:** Configured for `WIFI_PROTOCOL_LR` for extended range communication.

## Materials

- ESP32-S3 N16R8 Development board.
- WS2813-5V-RGB-LED-STRIP.

## IDE_Installation

- Download and install Arduino IDE version 1.8.15 or newer: https://www.arduino.cc/en/software
- Start Arduino and open the preferences window.
- Enter this link ( `https://espressif.github.io/arduino-esp32/package_esp32_index.json` ) into the **Additional Board Manager URLs** field.
- Open **Boards Manager** from `Tools > Board` menu and install the **esp32** platform from Espressif (version 2.0.11 recommended).
- Open `Tools > Board` and select **ESP32S3 Dev Module**. Keep board settings as default.

## Libraries_Installation

Open the Sketch tab and the Library Manager. Install the following library:

- **FastLED** (version 3.6.0)

*(Note: The WiFi and ESP-NOW libraries are included in the ESP32 board package installed above.)*

# Usage

1.  **Download** (Clone) this repository.
2.  **Open** the `.ino` file in the Arduino IDE.
3.  **Connect** your Node device via the USB-C port.
    - **IMPORTANT:** Connect to the USB port labeled **USB** (next to the charging port), not the dedicated charging port.
4.  **Select Port:** In Arduino IDE, select `Tools > Port > COMx` corresponding to your device.
5.  **Upload:** Click the upload button to flash the firmware.
6.  **MAC Address Registration:**
    - Once flashed, open the **Serial Monitor** (Baud Rate 115200).
    - Reset the device.
    - Copy the **MAC Address** displayed in the logs (e.g., `34:85:18:6D:37:B0`).
    - **Crucial Step:** You must add this MAC address to the `devicesMacAddress` list in `src/meshNetwork/MeshNetwork.cpp` in **this** Node repo (and the Hub repo for pairing).

## Node Identity in the Mesh

Each Node determines its identity by comparing its own MAC address against the ordered list in `devicesMacAddress` (in `src/meshNetwork/MeshNetwork.cpp`). The **index** that matches becomes the node's `meshId`. If no MAC matches, the firmware logs an error and resets. This is how the Node "knows" which device it is in the mesh.

To assign a new Node ID:
1. Flash the firmware and read the device MAC from Serial Monitor.
2. Add that MAC to `devicesMacAddress` at the correct index for the strip/label mapping you want.
3. Reflash the Node so it can match its MAC and set the `meshId`.
