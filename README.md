<img src="assets/ILC.svg" width=200 align="right">

[![PlatformIO](https://github.com/domino4com/ILC/actions/workflows/platformio.yml/badge.svg)](https://github.com/domino4com/ILC/actions/workflows/platformio.yml)
[![Arduino](https://github.com/domino4com/ILC/actions/workflows/arduino.yml/badge.svg)](https://github.com/domino4com/ILC/actions/workflows/arduino.yml)

# ILC - Input Light C
This is a Light Sensor measuring light power density from each the Red, Green and Blue channel in µW/cm², it measures ambient light intensity in Lux, and calculates correlated color temperature in Kelvin.
| Specifications | |
| --: | :--: |
| Communication | I²C |
| I²C Address | 0x10 |
| ChipSet | Vishay VEML6040|
| Datasheet | [.pdf]([https://.pdf](https://www.vishay.com/docs/84276/veml6040.pdf)) |
| Suggested Arduino Library | [GitHub]([https://github.com/](https://github.com/thewknd/VEML6040)) |
| Resolution per channel (R, G, B, W) | 16 bit |
| Selectable max Lux | 515.4, 1031, 2062, 4124, 8248, or 16 496 |
| Highest sensitivity | 0.007865 lux/step |

## Supported I²C Modes
- [x] 100 kbit/s Standard Mode (SM) 
- [x] 400 kbit/s	Fast Mode	FM
- [ ] 1 Mbit/s	Fast Mode Plus	FM+
- [ ] 3.4Mbit/s	High Speed Mode	HS
- [ ] 5 Mbit/s	Ultra Fast Mode	UFM

# License: 
<img src="assets/CC-BY-NC-SA.svg" width=200 align="right">
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License

[View License Deed](https://creativecommons.org/licenses/by-nc-sa/4.0/) | [View Legal Code](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
