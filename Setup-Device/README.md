---

# ESP32 M5Atom Lite Setup with Arduino IDE

This guide provides instructions for setting up the Arduino IDE to work with the ESP32 M5Atom Lite microcontroller. It includes steps for installing necessary boards, libraries, and uploading code to the device.

## Prerequisites

- A computer with Arduino IDE installed.
- ESP32 M5Atom Lite microcontroller.
- USB cable for connecting the ESP32 to your computer.

## Arduino IDE Setup

### Step 1: Install Arduino IDE

If you haven't already installed the Arduino IDE, download it from the [Arduino website](https://www.arduino.cc/en/software) and follow the installation instructions for your operating system.

### Step 2: Install ESP32 Board in Arduino IDE

1. **Open Arduino IDE**, go to `File > Preferences`.
2. In the "Additional Board Manager URLs" field, add the following URL:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
   Click "OK" to close the preferences window.
3. Go to `Tools > Board > Boards Manager`, search for "ESP32", and install the latest version of the "ESP32 by Espressif Systems" board.

### Step 3: Install Required Libraries

1. **Open Arduino IDE**, go to `Sketch > Include Library > Manage Libraries`.
2. Search and install the following libraries:
   - `WiFi`
   - `PubSubClient`
   - `ArduinoJson`
   - You may also need specific libraries for M5Atom Lite if your project requires them.

### Step 4: Selecting the Board and Port

1. Connect your ESP32 M5Atom Lite to your computer via a USB cable.
2. In the Arduino IDE, go to `Tools > Board` and select "M5Stick-C" (as it's compatible with M5Atom Lite).
3. Select the correct COM port in `Tools > Port`. (The COM port number will vary and can be identified in the Device Manager on Windows or by using `ls /dev/tty.*` in the Terminal on macOS.)

## Uploading the Code

1. **Copy the provided code** into a new sketch in the Arduino IDE. Maintain the directory structure same for secrets where you keep Secrets.h
2. **Ensure that your ESP32 is still connected** to your computer.
3. Click the "Upload" button (right arrow icon) in the Arduino IDE. This will compile the code and upload it to your ESP32 M5Atom Lite.
4. Once uploaded, the ESP32 will execute the code. Monitor the output using the Serial Monitor in the Arduino IDE.

## Troubleshooting

- If the upload fails, check that you've selected the correct COM port and board.
- Some ESP32 boards require pressing a boot button on the board during the upload process.
- Make sure all required libraries are correctly installed.

---
