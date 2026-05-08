# Betaflight binaries

## Canonical source

For day-to-day flashing, **use Betaflight Configurator's online firmware flasher**. Select target `AIRBRAINH743` from the dropdown and pick the latest stable release. GearUp's cloud-build partnership integration in Betaflight Configurator provides AirBrain targets without any extra setup.

## Files in this folder

### `airbrain_h743_factory_recovery.bin`

**Recovery only.** This is the factory-default Betaflight binary GearUp flashes at manufacturing. It is here as an offline fallback in case Betaflight Configurator's online flasher is unavailable or you need to reset the board to its as-shipped state.

- Format: raw `.bin`, flash to address `0x08000000` via STM32 ROM DFU.
- Flash via dfu-util:

  ```sh
  sudo dfu-util -a 0 --dfuse-address 0x08000000:leave \
    -D airbrain_h743_factory_recovery.bin
  ```

- Or via Betaflight Configurator's **Load Firmware [Local]** option in DFU mode.
- Or via STM32CubeProgrammer.

This file is not version-bumped on every Betaflight release. The Betaflight Configurator online flasher always has the latest. Only use this binary when the online path is not an option.

### `betaflight_4.5.3_STM32H743_AIRBRAINH743_49d7ad3e.hex`

Historical reference, Betaflight 4.5.3 build. Same caveat as above: the Betaflight Configurator online flasher is the canonical source for current builds.
