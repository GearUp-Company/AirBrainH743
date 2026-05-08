# License

This repository documents the AirBrain H743 flight controller from GearUp Company (a brand of EUnify BV, Belgium). It collects firmware binaries, firmware source mirrors, datasheet, mechanical adapter files, and integration documentation. Different parts of this repository carry different licenses.

## Hardware design

The AirBrain H743 hardware design (schematics, PCB layout, design files, full bill of materials, supplier-specific component selection) is proprietary to GearUp Company. It is not part of this repository and is not published.

## Firmware binaries (`firmware/<flavor>/bin/`)

Pre-built firmware binaries in the `firmware/Ardupilot/`, `firmware/Betaflight/`, `firmware/INAV/`, and `firmware/PX4/` subdirectories are derivative works of their respective upstream firmware projects and are subject to the upstream licenses:

- ArduPilot: GPL-3.0
- Betaflight: GPL-3.0
- INAV: GPL-3.0
- PX4: BSD-3-Clause

Refer to each upstream project for the canonical license text.

## Firmware source mirrors (`firmware/<flavor>/sourcecode/`)

Files in `firmware/Ardupilot/sourcecode/`, `firmware/Betaflight/sourcecode/`, `firmware/INAV/sourcecode/`, and `firmware/PX4/sourcecode/` are derivative works of upstream firmware projects (ArduPilot hwdef, Betaflight target configs, INAV target sources, PX4 board definitions). They are licensed under the same upstream licenses listed above.

These files are mirrored here for convenience. Canonical versions live upstream:

- ArduPilot: https://github.com/ArduPilot/ardupilot/tree/master/libraries/AP_HAL_ChibiOS/hwdef/AIRBRAINH743
- Betaflight: https://github.com/betaflight/config/tree/master/configs/AIRBRAINH743
- PX4: https://github.com/PX4/PX4-Autopilot/tree/main/boards/gearup/airbrainh743

## Documentation (datasheet, pinout images, README, BUILD.md, UPGRADING.md, this LICENSE)

All Rights Reserved by EUnify BV. Limited grant for the following uses without further permission:

- Personal evaluation of the AirBrain H743
- Integration into your own UAV or robotics product (commercial use included)
- Internal redistribution within your own organization or project team

The following require written permission from GearUp Company:

- Republication on third-party websites, marketing materials, or product catalogs
- Use as training data for AI or ML systems
- Derivative branding or rebadging
- Commercial reproduction of the datasheet or pinout images

## Mechanical adapter STEP files (`3D/`)

The 30x30 to 20x20 mounting adapter STEP files in `3D/` are licensed under Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0). Free to download, modify, and 3D-print for non-commercial use. Commercial reproduction (e.g. selling the adapter as part of a product) requires written permission.

## Trademarks

"AirBrain", "Gear Up", and "EUnify" are trademarks of EUnify BV. Use of these names in connection with related hardware, firmware, or marketing requires written permission. Use in technical documentation, integration guides, customer-facing communications, or news articles for genuine reference (e.g. "we use the AirBrain H743 in our system") is permitted without further permission.

## Contact

For licensing questions, partnership inquiries, OEM arrangements, or written-permission requests: info@takeyourgear.com
