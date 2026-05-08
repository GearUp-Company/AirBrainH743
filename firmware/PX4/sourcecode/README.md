<!--
Snapshot of upstream PX4 board folder, refreshed 2026-05-08.
Canonical source: https://github.com/PX4/PX4-Autopilot/tree/main/boards/gearup/airbrainh743
Refresh: cp from upstream sparse-checkout of `boards/gearup/airbrainh743/` (extras/ omitted, see below).
-->

# PX4 target source for `gearup_airbrainh743`

**Snapshot of upstream**, refreshed 2026-05-08 from [`PX4/PX4-Autopilot`](https://github.com/PX4/PX4-Autopilot) at commit `78abda4`.

## Canonical source

The PX4-Autopilot repo is the source of truth:

- Repo: [github.com/PX4/PX4-Autopilot](https://github.com/PX4/PX4-Autopilot)
- Path: [`boards/gearup/airbrainh743/`](https://github.com/PX4/PX4-Autopilot/tree/main/boards/gearup/airbrainh743)

## Folder structure

| Path | Purpose |
|---|---|
| `bootloader.px4board` | Build config, bootloader target |
| `default.px4board` | Build config, default firmware target |
| `firmware.prototype` | Firmware metadata template |
| `init/` | Board startup scripts (`rc.board_defaults`, `rc.board_sensors`, `rc.board_extras`) |
| `nuttx-config/` | NuttX RTOS configuration (defconfig, board.h, linker scripts) |
| `src/` | Board-specific C/C++ (init, USB, SPI, I2C, LED, timer config, hw config) |

## Bootloader binary, version note

Upstream's `extras/gearup_airbrainh743_bootloader.bin` is **not mirrored here** to avoid carrying two copies of the bootloader at different versions.

The bootloader binary actively distributed for the AirBrain is at [`firmware/PX4/bin/bootloader/gearup_airbrainh743_bootloader.bin`](../bin/bootloader/gearup_airbrainh743_bootloader.bin). It is built post-PR-27227 (NAND fix) and is bit-identical to the build distributed by Julian Oes.

## How to refresh

```sh
git clone --depth 1 --filter=blob:none --sparse https://github.com/PX4/PX4-Autopilot.git
cd PX4-Autopilot && git sparse-checkout add boards/gearup/airbrainh743
# Copy boards/gearup/airbrainh743/* (except extras/) over this folder.
```
