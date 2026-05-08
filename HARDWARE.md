# AirBrain H743 hardware overview

This document is a quick orientation. The full electrical, mechanical, and pinout reference is in the [datasheet PDF](datasheet/Datasheet_AirBrain.pdf).

## At a glance

| | |
|---|---|
| **MCU** | STM32H743VIH6, 480 MHz Cortex-M7, 2 MB Flash, 1 MB RAM |
| **IMU** | InvenSense ICM-42688-P, 6-axis, clock-synchronised |
| **Magnetometer** | STMicroelectronics LIS2MDL |
| **Barometer** | Infineon DPS368 |
| **Logging** | Winbond W25N01GVZEIT, 128 MB on-board NAND |
| **Connectivity** | USB-C (GCT USB4730-GF-A-KIT, IP67 panel-mount with gasket) |
| **Power** | 3S to 10S input, switching-IC topology, BEC 5V 2A + BEC 10V 2.5A |
| **UARTs** | 7 |
| **PWM outputs** | 9 (8 motor outputs, 1 LED) |
| **Form factor** | 36 × 31 × 10 mm, 8 g, 20 × 20 mm mounting (30 × 30 adapter STEP in `/3D`) |
| **USB** | USB-C panel-mount with gasket, IP67 connector spec |
| **Origin** | Designed and assembled in Belgium |

## What this board is for

Universal flight controller for UAVs and small autonomous platforms where a single hardware target needs to flash any of the three major open-source flight stacks (Betaflight, ArduPilot, PX4) without forking firmware.

Common platforms: race cine FPV, autonomous mapping, fixed-wing inspection, indoor research drones, robotic vehicles using ArduPilot Rover, ROV builds using ArduSub.

## Per-firmware target name

| Stack | Target |
|---|---|
| Betaflight | `AIRBRAINH743` |
| ArduPilot | `AIRBRAINH743` |
| PX4 | `gearup_airbrainh743_default` |

See the [Switching firmware stacks](README.md#switching-firmware-stacks) section of the README for end-to-end transition workflows.

## Per-firmware default behaviour

Status LED, ESC protocol defaults, UART role mapping, and LED Strip behaviour differ per firmware. The datasheet documents defaults per stack; the integrator can remap any of these via the stack's configurator.

## Compatibility

- **ESCs**: BLHeli_32 / AM32 over DShot150/300/600/1200, bidirectional DShot supported on M1 to M8.
- **Receivers**: any UART-based serial protocol (CRSF, ELRS, SBUS, F.Port, SRXL2). PPM and parallel PWM RX are legacy formats and not the recommended integration path on this board.
- **OSD**: no on-board OSD chip.
  - **Analog video, plug-and-play**: use a VTX with built-in OSD such as the [TBS Unify EVO](https://www.team-blacksheep.com/products/prod:unify_evo). Self-contained graphics; CRSF link-data overlay (RSSI / LQ / SNR / TX power) works when the FC has a CRSF-speaking RX wired in (ELRS, Crossfire, Ghost). "CRSF" here is the FC-to-VTX wire protocol, the VTX has no RF receiver. Compatible with MAVLink GCS telemetry on a separate UART.
  - **Analog video, FC-rendered OSD**: add an inline MAX7456 / AT7456E OSD module to overlay the firmware's native OSD elements (battery voltage, GPS, BF-style elements).
  - **HD video**: use a digital VTX (DJI, Walksnail, HDZero) over MSP DisplayPort.
- **GPS**: any UART-based GPS module.
- **Telemetry**: MAVLink (ArduPilot, PX4) on any UART. ESC telemetry on UART7 (default across Betaflight, ArduPilot, and PX4).

## Physical reference

| Dimension | Value |
|---|---|
| PCB outline | 36 × 31 mm |
| Stack height | 10 mm |
| Mounting pattern | 20 × 20 mm, M2 |
| 30 × 30 adapter | STEP file in [`/3D`](/3D), printable in any FDM resin |
| Connector face | One short edge (USB-C, motor connectors), opposite edge has BOOT button + RGB LED |

For the full pinout (numbered pads + colour-legend), see the [datasheet PDF, page 2](datasheet/Datasheet_AirBrain.pdf).

## Compliance posture

- **CE conformity** declared by EUnify BV (manufacturer declaration model). Integrator declares for the final UAV.
- **Pre-compliance EMC** sweeps run at Würth Elektronik eiSos lab before each board revision.
- **NDAA** compliant on the bill of materials (EU/US/JP/TW component sourcing).
- **Origin** Belgium (designed + final assembly + functional test).

For the formal Declaration of Conformity, contact [info@takeyourgear.com](mailto:info@takeyourgear.com).

## More

- [Datasheet PDF](datasheet/Datasheet_AirBrain.pdf), full electrical + mechanical reference
- [README](README.md), firmware-stack switching guide and integrator workflows
- [BUILD.md](BUILD.md), build-from-source guide for all three firmware families
- [LICENSE.md](LICENSE.md), license terms
