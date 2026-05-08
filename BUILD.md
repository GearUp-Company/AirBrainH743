# Building firmware for AirBrain H743

Pre-built firmware for the AirBrain H743 is available from each upstream project's official channels (links below per firmware family). Build from source if you need:

- A custom firmware version (apply your own patches, integrate with proprietary modules)
- A bleeding-edge build between official upstream releases
- A specific feature flag combination not covered in the official build

This page documents the per-family target strings, upstream config paths, and AirBrain-specific notes. For full build environment setup (toolchains, dependencies), refer to each upstream project's own build documentation.

## ArduPilot

- **Target string**: `AIRBRAINH743`
- **Upstream hwdef**: https://github.com/ArduPilot/ardupilot/tree/master/libraries/AP_HAL_ChibiOS/hwdef/AIRBRAINH743
- **Build (after standard ArduPilot environment setup)**:

  ```
  ./waf configure --board AIRBRAINH743
  ./waf copter
  ```

- Build other vehicle types by substituting the second command (`./waf plane`, `./waf rover`, `./waf sub`).
- **Official pre-built binaries**: https://firmware.ardupilot.org/Copter/latest/AIRBRAINH743/
- **Help**: ArduPilot Discuss (https://discuss.ardupilot.org), GitHub Issues on this repo.

Reference: ArduPilot build docs at https://ardupilot.org/dev/docs/building-the-code.html

## PX4

- **Target string**: `gearup_airbrainh743_default`
- **Upstream board definition**: https://github.com/PX4/PX4-Autopilot/tree/main/boards/gearup/airbrainh743
- **Build (after standard PX4 environment setup)**:

  ```
  make gearup_airbrainh743_default
  ```

- **Official pre-built binaries**: https://docs.px4.io/main/en/flight_controller/gearup_airbrainh743 (links to firmware download)
- **In-repo reference binary**: `firmware/PX4/bin/gearup_airbrainh743_default.px4`. Built from PX4 main post-PR-27227 (NAND bad block management fix). See [UPGRADING.md](firmware/PX4/UPGRADING.md) for the `mklittlefs` step required when upgrading from a pre-PR-27227 build.
- **Help**: PX4 Discuss (https://discuss.px4.io), GitHub Issues on this repo.

Reference: PX4 build docs at https://docs.px4.io/main/en/dev_setup/building_px4.html

## Betaflight

- **Target string**: `AIRBRAINH743`
- **Upstream config** (modern, Betaflight 4.5+): https://github.com/betaflight/config/tree/master/configs/AIRBRAINH743
- **Pre-built binaries**: select `AIRBRAINH743` in the Betaflight Configurator board dropdown at https://app.betaflight.com. The Configurator downloads the pre-built binary automatically.
- **Documentation**: https://www.betaflight.com/docs/wiki/boards/current/AIRBRAINH743
- **Help**: Betaflight Discord (link from https://betaflight.com), GitHub Issues on this repo.

Reference: Betaflight build docs at https://github.com/betaflight/betaflight/blob/master/README.md

## Where to file issues

For AirBrain-specific issues (target config, board behaviour, hardware integration), use this repo's issue tracker: https://github.com/GearUp-Company/AirBrainH743/issues

For upstream firmware bugs (regardless of AirBrain), file in the relevant upstream project. We track upstream changes that affect the AirBrain target and update this repo's binaries accordingly.
