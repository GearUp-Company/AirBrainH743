# Upgrading PX4 firmware on AirBrain H743

## Critical step when upgrading from a pre-PR-27227 build

If you are upgrading from any earlier `gearup_airbrainh743_default.px4` build (any binary built before PX4 PR #27227 was merged on 2026-04-28), you MUST format the NAND filesystem after flashing the new firmware. The new build introduces NAND bad block management; without re-formatting, the existing filesystem layout is incompatible.

After flashing the new `.px4` file via QGroundControl or the PX4 update tool, connect to the NSH console and run:

```
mklittlefs /dev/mtd0 /fs/flash
```

This wipes the existing flash filesystem and re-creates it with the new layout. Logs and parameter files stored on flash will be lost; back up parameters via QGroundControl beforehand if needed.

Source: PX4 maintainer Julian Oes, 2026-04-28, in the context of merging [PR #27227](https://github.com/PX4/PX4-Autopilot/pull/27227) (`fix(nuttx): update for NAND bad block management`).

## Where this binary comes from

`firmware/PX4/bin/gearup_airbrainh743_default.px4` is built from PX4 main at the post-PR-27227 commit. As of 2026-05-08, this build is NOT yet in a PX4 stable release; it will be included in PX4 v1.17.0 (currently in pre-release) or a v1.16.x backport.

Once an official PX4 stable release including PR #27227 is published, official builds will be available at the standard PX4 firmware channel. This in-repo binary will be marked as superseded at that point.

## Verifying which build you are running

You can check the running PX4 firmware version in QGroundControl under Vehicle Setup, Summary. The binary in this repo (built from PR-27227) reports a development-build version string.
