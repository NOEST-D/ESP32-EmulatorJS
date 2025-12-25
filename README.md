# ESP32-EmulatorJS

A web-based NES and SNES emulator served by the **M5 Cardputer (ESP32)**,  
running locally in the user's browser using **EmulatorJS**.

The ESP32 hosts a web interface and game files, while all emulation is
performed on the client device inside the browser.

---

## Features

- 📟 Designed for the M5 Cardputer (ESP32)
- 🌐 Browser-based NES and SNES emulation
- 🧠 Emulation runs locally in the browser
- 🎮 ROM selection via web UI
- 📦 ROMs stored on the ESP32 (SD)
- ⚡ No emulation performed on the ESP32 itself
- 📱 Works on desktop and mobile browsers

---

## How It Works

1. The ESP32 runs a local web server
2. The user connects to the Cardputer via Wi-Fi
3. A web interface is loaded in the browser
4. The user selects a game from the available ROM list
5. The selected ROM and the emulator files are transferred to the browser
6. The emulator runs **entirely on the client device**

---

## Limitations

- Performance depends on the client device
- Input latency may vary by browser
- Large ROMs may load slowly over Wi-Fi

---

## ROMs and Legal Notice

⚠️ **This repository does NOT include any ROM files.**

ROMs must be:
- Legally obtained
- Dumped from cartridges you own
- Added manually to the ESP32’s filesystem

The ROMs are served **only over the local network** and are never
distributed through this repository.

---

## Setup

| Step | Describtion | Image |
|------|-------------|-------|
| 1. | Copy the ESP32EJS folder into your Cardputer's SD root | <img src="Images/ESP32EJSFolder.png" width="500"> |
| 2. | Prepare your legally obtained NES/SNES ROM files and add them to the ESP32 filesystem (SD:\ESP32EJS\roms\)| <img src="Images/roms.png" width="500"> |
| 3. | Add your WiFi Credentials in the creds.txt file (SD:\ESP32EJS\creds.txt)<br>The AP credentials are used in Access Point Mode (AP-MODE)| <img src="Images/CredentialFile.png" width="500"> |
| 4. | Flash the .bin file from the Firmware folder<br>There is also a .ino file under "Firmware/ArduinoIDE/ESP32EJS/" if you want to check out the code | <img src="Images/FirmwareFile.png" width="500"> |
| 5. | Turn on the Cardputer<br>For AP-MODE press the G0 button when its prompted on the Cardputer| |
| 6. | Open the device’s IP address in your browser and select a ROM from the web interface | <img src="Images/SelectingROM.png" width="500"> |
| 7. | The selected ROM will now be executed by EmulatorJS<br>Have fun playing! | <img src="Images/Playing.png" width="500"> |

- The Cardputer's screen will go blank after 60s. To turn it back on press G0.
---

## Custom Favicon

This project does not include a favicon by default.

If you want, you can add your own `favicon.ico` in the ESP32EJS folder (the same folder where `index.html` is).
Browsers will automatically use it when loading the page.

<img src="Images/FilesInESP32EJS.png" width="800">

---

## Third-Party Software

This project uses **EmulatorJS**, an open-source web emulator framework.

- EmulatorJS repository:  
  https://github.com/EmulatorJS/EmulatorJS

Please refer to the EmulatorJS license for details.

---

## License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for more information.
