<h1>
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="datasheet/Gearup_White.png">
    <source media="(prefers-color-scheme: light)" srcset="datasheet/Gearup.png">
    <img alt="GearUp Logo" src="datasheet/Gearup.png" height="25" style="vertical-align: middle; margin-right: 8px;">
  </picture>
  AirBrainH743
</h1>

GearUp **AirBrain H743** flight controller. STM32H743VIH6 (480 MHz Cortex-M7), 36 × 31 × 10 mm, 8 g. Designed and made in Belgium.

This repository hosts the datasheet, pinouts, mechanical resources, and integration guides for the board. **Schematics and full bill of materials are not published here.** Source-of-truth for the product is the [Airbrain product page](https://takeyourgear.com/pages/products/airbrain).

<div align="center">

![AirBrain_Front](/datasheet/AirBrain_front.png)

</div>

## Firmware support

The AirBrain H743 is **officially supported upstream** by Betaflight, ArduPilot, and PX4. Targets live in each project's main branch.

| Stack | Target | Canonical source |
|---|---|---|
| **Betaflight** | `AIRBRAINH743` | Betaflight Configurator, Firmware Flasher, board dropdown |
| **ArduPilot** | `AIRBRAINH743` | Latest builds for [Copter](https://firmware.ardupilot.org/Copter/latest/AIRBRAINH743/), [Plane](https://firmware.ardupilot.org/Plane/latest/AIRBRAINH743/), [Rover](https://firmware.ardupilot.org/Rover/latest/AIRBRAINH743/), [Sub](https://firmware.ardupilot.org/Sub/latest/AIRBRAINH743/) |
| **PX4** | `gearup_airbrainh743_default` | [Latest CI build (.px4)](https://px4-travis.s3.amazonaws.com/Firmware/master/gearup_airbrainh743_default.px4) |

Boards ship pre-flashed with **Betaflight**.

INAV is in beta. Targets are present in this repo's `firmware/INAV/` folder for testing but are not advertised as production-supported.

## Pinout & Datasheet

Latest datasheet and pinouts: [`/datasheet`](/datasheet).

<div align="center">

![AirBrain_Pinout_top](/datasheet/AirBrain_pinoutTop.png)
![AirBrain_Pinout_bottom](/datasheet/AirBrain_pinoutBottom.png)

</div>

## Switching firmware stacks

Boards ship with Betaflight. Switching to ArduPilot or PX4 is a one-time operation on a desktop computer. After switching, you can switch back with the same procedure.

### Entering DFU mode

DFU (Device Firmware Update) is the STM32's built-in ROM bootloader. It's required for the first install of any firmware family, for switching bootloaders (PX4, ArduPilot), and for recovery. Two routes into DFU:

- **Hardware (BOOT button)**: hold the on-board **BOOT** button while plugging in the USB cable. Release after the board enumerates. This route works regardless of which firmware is currently on the board, including a bricked board.
- **From Betaflight Configurator**: with Betaflight running, click **Activate Boot Loader** in the top right. The board reboots into DFU. *Only works while Betaflight is running.* If the board has ArduPilot or PX4 on it, use the BOOT button.

In DFU mode the board enumerates as a USB DFU device ("STM32 BOOTLOADER" or "DFU in FS Mode") and no longer responds as a serial device until you flash and exit.

---

### Betaflight, to ArduPilot

ArduPilot uses its **own bootloader** (different from Betaflight's monolithic flash layout). For a clean first install on an AirBrain that's running Betaflight, we recommend flashing the **with-bootloader** ArduPilot variant first; subsequent updates can use the no-bootloader `.apj` via Mission Planner over USB-MAVLink.

1. Go to [firmware.ardupilot.org/Copter/latest/AIRBRAINH743/](https://firmware.ardupilot.org/Copter/latest/AIRBRAINH743/) (replace `Copter` with `Plane`, `Rover`, `Sub`, etc. for your vehicle type).
2. Two files are published per release (vehicle-prefixed, e.g. `arducopter`, `arduplane`):
   - `<vehicle>_with_bl.hex`: contains the ArduPilot bootloader **and** firmware as a multi-region Intel HEX file. Use this for the first flash from a Betaflight board.
   - `<vehicle>.apj`: firmware only. Use this for over-MAVLink updates once the ArduPilot bootloader is on the board.
3. Put the AirBrain in **DFU mode** (BOOT button + USB).
4. Open **Mission Planner** (or QGroundControl).
5. Use the GCS's custom-firmware install option and select the `_with_bl.hex` file. Follow the on-screen prompts.
6. Wait for the flash to complete. The board reboots into ArduPilot.

For subsequent ArduPilot version bumps, you can connect the GCS to the running ArduPilot board over USB and flash the no-bootloader `.apj` directly.

---

### Betaflight, to PX4

PX4 uses its **own bootloader**, distinct from the Betaflight/ArduPilot bootloader. So switching to PX4 is a two-step flash: bootloader, then firmware.

#### Step 1: Flash the PX4 bootloader

Get the PX4 bootloader binary from this repo: [`firmware/PX4/bin/bootloader/gearup_airbrainh743_bootloader.bin`](firmware/PX4/bin/bootloader/gearup_airbrainh743_bootloader.bin).

Pick whichever flashing tool you're most comfortable with. The board needs to be in **DFU mode** for all three.

##### Option A: Betaflight Configurator (cross-platform, GUI)

Betaflight Configurator's Firmware Flasher can load any local `.bin` and write it via the STM32 ROM DFU. Works in both the desktop app and the web Configurator at [app.betaflight.com](https://app.betaflight.com).

1. Open Betaflight Configurator.
2. Put the AirBrain in DFU mode (see "Entering DFU mode" above).
3. Go to the **Firmware Flasher** tab.
4. Click **Load Firmware [Local]** and select `gearup_airbrainh743_bootloader.bin`.
5. Click **Flash Firmware**.

> Reported to work by upstream maintainers; not yet self-verified by GearUp end-to-end. If it fails, fall back to Option B (STM32CubeProgrammer) or Option C (dfu-util).

##### Option B: STM32CubeProgrammer (official ST tool, GUI, cross-platform)

[Download STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) from ST.

1. Put the AirBrain in DFU mode.
2. Open STM32CubeProgrammer.
3. Connection dropdown (top right): select **USB**, then your DFU device, click **Connect**.
4. Click the **Erasing & Programming** tab on the left.
5. Browse to `gearup_airbrainh743_bootloader.bin`.
6. Set start address to `0x08000000`.
7. Click **Start Programming**.

##### Option C: dfu-util (CLI, Linux/macOS)

```sh
dfu-util -a 0 -s 0x08000000:leave \
  -D gearup_airbrainh743_bootloader.bin
```

#### Step 2: Flash the PX4 firmware

After flashing the bootloader, the board reboots and enumerates as a PX4 device.

1. Download the **latest PX4 firmware**: [gearup_airbrainh743_default.px4](https://px4-travis.s3.amazonaws.com/Firmware/master/gearup_airbrainh743_default.px4).
   This is the official PX4 CI build, automatically rebuilt from PX4's `master` branch.
2. Open **QGroundControl**.
3. Connect the AirBrain via USB.
4. Use **Vehicle Setup, Firmware** and follow the prompts to load custom firmware.
5. Select the `.px4` file you downloaded.
6. Wait for the flash to complete.

> **Migrating from a pre-PR-27227 PX4 build?** The NAND filesystem layout changed. See [`firmware/PX4/UPGRADING.md`](firmware/PX4/UPGRADING.md) for the one-line `mklittlefs` reformat command.

---

### ArduPilot or PX4, back to Betaflight

Betaflight is a monolithic image flashed directly at `0x08000000` via STM32 ROM DFU. Going back from ArduPilot or PX4 wipes the previous bootloader and replaces it with Betaflight in one operation.

The "Activate Boot Loader" button in Betaflight Configurator only exists when Betaflight is already running. From ArduPilot or PX4 you must use the **hardware BOOT button** to enter DFU.

1. Put the AirBrain in DFU mode (hold BOOT button + plug in USB).
2. Open **Betaflight Configurator** (desktop app or web Configurator at [app.betaflight.com](https://app.betaflight.com)).
3. Go to the **Firmware Flasher** tab.
4. Select target `AIRBRAINH743` from the dropdown.
5. Pick the latest stable Betaflight release.
6. Check **Full chip erase** (recommended; clears any leftover ArduPilot bootloader area or PX4 NAND filesystem state).
7. Click **Load Firmware [Online]**, then **Flash Firmware**.

GearUp has a **cloud-build partnership integration in Betaflight Configurator**, so AirBrain targets are available in the official Configurator dropdown without any extra setup.

> **Offline recovery**: if Betaflight Configurator's online flasher is unavailable, the factory-default Betaflight binary is at [`firmware/Betaflight/bin/airbrain_h743_factory_recovery.bin`](firmware/Betaflight/bin/airbrain_h743_factory_recovery.bin). Recovery only, see that folder's [README](firmware/Betaflight/bin/README.md) for flashing instructions.

## ArduPilot integration notes

Common gotchas when running ArduPilot on the AirBrain H743, based on upstream maintainer feedback.

### ArduPilot 4.7 parameter rename, QGroundControl error

ArduPilot 4.7 renamed a large number of parameters. Notably, `ARMING_CHECK` was removed and replaced with `ARMING_SKIPCHK` (the meaning is inverted). QGroundControl has not yet been updated to recognise the new 4.7 parameter set, which surfaces as "missing parameter" errors after a fresh flash from the latest ArduPilot build.

Workaround: use the **beta version of Mission Planner**, which tracks the latest ArduPilot parameter set.

The AIRBRAINH743 target was added to ArduPilot after the stable-4.6 branch was cut, so the standard 4.6 stable downloads do not include AirBrain. The latest CI build is the canonical source.

### SBUS receiver on RX5 (UART5)

To run an SBUS receiver on the AirBrain's RX5 pin (UART5 in ArduPilot), disable RCIN on the default UART (UART2) and enable it on UART5:

```text
SERIAL2_PROTOCOL = -1
SERIAL5_PROTOCOL = 23
```

After setting these and rebooting, the RX5 pin will accept SBUS input.

## Building from source

If you want to build PX4, ArduPilot, or Betaflight firmware yourself, see [`BUILD.md`](BUILD.md). The repo's `firmware/<stack>/` folders contain target definitions and source where applicable, but **upstream is canonical**: please contribute target changes upstream.

## 3D files

The [`/3D`](/3D) folder contains a STEP file for the 30 × 30 to 20 × 20 mm mounting adapter.

Additional printable mounts, brackets, and housings are published on our **[MakerWorld page](https://makerworld.com/en/@GearUp)**.

## Repo layout

| Path | Contents |
|---|---|
| [`/datasheet`](/datasheet) | Latest datasheet PDF + pinout images |
| [`/firmware/PX4/bin/bootloader/`](/firmware/PX4/bin/bootloader/) | PX4 bootloader binary |
| [`/firmware/PX4/sourcecode/`](/firmware/PX4/sourcecode/) | PX4 target source (mirror of upstream) |
| [`/firmware/Ardupilot/`](/firmware/Ardupilot/) | ArduPilot target source (mirror of upstream) |
| [`/firmware/Betaflight/`](/firmware/Betaflight/) | Betaflight target source (mirror of upstream) + factory-default `.bin` for offline recovery |
| [`/3D`](/3D) | STEP file for 30 × 30 to 20 × 20 mounting adapter |
| [`BUILD.md`](BUILD.md) | Build-from-source guide for all three firmware families |
| [`LICENSE.md`](LICENSE.md) | License terms |

## License

See [`LICENSE.md`](LICENSE.md). Hardware design files (schematics, PCB layout, full BOM) are **not** published in this repository.

## Contact

- Website: [takeyourgear.com](https://takeyourgear.com/)
- Email: [info@takeyourgear.com](mailto:info@takeyourgear.com)
- Issues: please use this repo's [Issues](https://github.com/GearUp-Company/AirBrainH743/issues) for documentation and integration questions

<div align="center">

![AirBrain Logo](datasheet/Gearup.png#gh-light-mode-only)
![AirBrain Logo](datasheet/Gearup_White.png#gh-dark-mode-only)

</div>
