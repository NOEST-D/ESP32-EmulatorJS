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
5. The selected ROM is transferred to the browser
6. The emulator runs **entirely on the client device**

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

1. Prepare your legally obtained NES/SNES ROM files
2. Add them to the ESP32 filesystem (SD:\ESP32EJS\roms\)
3. Add your WiFi Credentials in the creds.txt file (SD:\ESP32EJS\creds.txt)
4. Flash the firmware
5. Power on the Cardputer
6. Open the device’s IP address in your browser
7. Select a ROM from the web interface and play

---

## Limitations

- Performance depends on the client device
- Input latency may vary by browser
- Large ROMs may load slowly over Wi-Fi

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
