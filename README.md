<h1>
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="datasheet/Gearup_White.png">
    <source media="(prefers-color-scheme: light)" srcset="datasheet/Gearup.png">
    <img alt="GearUp Logo" src="datasheet/Gearup.png" height="25" style="vertical-align: middle; margin-right: 8px;">
  </picture>
  AirBrainH743
</h1>

This GitHub repository serves as a backup and documentation hub for the AirBrain H743 flight controller.

All official information and product details are available on our website: [Airbrain Product page](https://takeyourgear.com/pages/products/airbrain)
<div align="center">

![AirBrain_Front](/datasheet/AirBrain_front.png)

</div>

## Overview

The AirBrainH743 is now officially supported by both Betaflight, ArduPilot and PX4, with the target added to their main branches. We also have beta firmware targets available for INAV, and a development framework on Platform IO (Arduino).
This repository exists to provide a secondary reference location for hosting documentation, pinout diagrams, and firmware resources, to ensure the information remains easily accessible.

  For the latest Ardupilot: https://firmware.ardupilot.org/Copter/latest/AIRBRAINH743/

  For the latest Betaflight, click the dropdown list inside Betaflight configurator and select: AIRBRAINH743


## Pinout & Datasheet

The /datasheet folder contains the official datasheet and pinout diagrams for the AirBrain flight controller.

<div align="center">

![AirBrain_Pinout_top](/datasheet/AirBrain_pinoutTop.png)
![AirBrain_Pinout_bottom](/datasheet/AirBrain_pinoutBottom.png)

</div>

## Firmware

The '/firmware' folder contains backup binaries and source files related to the AirBrain target.

Please always use the official AirBrain firmware provided by the Betaflight or ArduPilot communities.

This repository is only for documentation and archival purposes.

Inside the firmware folder:

'/sourcecode' – Gear Up source files used for target creation

'/bin' – precompiled binary files that can be flashed to the AirBrain


### PX4

These instructions are only for when you would like to build PX4 AirBrainH743 target yourself. If you would just like to install PX4 on the board, please see the '/firmware/PX4/bin' folder that contains PX4 firmware files for the AirBrainH743.

Following instructions expect you have a working PX4 development environment. Copy the contents of '/firmware/PX4/sourcecode' inside your PX4 environment under 'gearup/airbrainh743'.


#### Make PX4 bootloader

```cli
make gearup_airbrainh743_bootloader
```

#### Flash PX4 bootloader 

```cli
dfu-util -a 0 -s 0x08000000:leave   -D boards/gearup/airbrainh743/extras/gearup_airbrainh743_bootloader.bin
```

#### Make PX4 FW

```cli
make gearup_airbrainh743_default
```

#### Flash PX4 FW

```cli
dfu-util -a 0 -s 0x08020000:leave \
  -D build/gearup_airbrainh743_default/gearup_airbrainh743_default.bin
```

#### Tip

```cli
make clean
```

#### Missing feature in PX4

Support for NAND flash ⇒ PX4/PX4-Autopilot#22490

=> WIP

## 3D files

The /3D folder contains step files for an optional mounting bracket to go from 30x30 to 20x20mm.


## Contact & More Info

<div align="center">

For additional details or support:

<info@takeyourgear.com>

![AirBrain Logo](datasheet/Gearup.png#gh-light-mode-only)
![AirBrain Logo](datasheet/Gearup_White.png#gh-dark-mode-only)

[Website Gear Up](https://takeyourgear.com/)

</div>

