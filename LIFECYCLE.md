# AirBrain H743 lifecycle commitments

## Production and availability

For **multi-year procurement programmes**, defence or institutional contracts requiring assured supply, please contact us directly. We can discuss private letter-of-supply, MOQ-backed reservations, and component-buffer arrangements on a case-by-case basis.

## End-of-life notice

If we plan to discontinue the AirBrain H743, we commit to:

- **6 months minimum advance notice** before the last-time-buy window closes.
- A **last-time-buy window of 3 months** during which integrators can place final stocking orders.
- A **public end-of-life announcement** posted to this repository (LIFECYCLE.md update + GitHub release tagged `eol-airbrain-h743`).

## Firmware-update commitment

We commit to:

- **Maintaining the upstream AIRBRAINH743 / `gearup_airbrainh743_default` targets** in Betaflight (`betaflight/config`), ArduPilot (`ardupilot/ardupilot`), and PX4 (`PX4/PX4-Autopilot`) as long as the board is in active production.
- **Reviewing, testing, and contributing fixes upstream** when AirBrain-specific issues are reported.
- **Not forking or maintaining a private firmware branch.** All AirBrain firmware lives in the public upstream projects. If upstream support for the STM32H743 line is dropped at the project level (we do not anticipate this), we will assess and communicate alternatives at that point.

After end-of-life, the upstream targets remain available indefinitely from the upstream projects. We do not commit to actively backporting fixes after EOL but the targets do not disappear.

## Hardware-revision policy

- **All hardware revisions are documented** in the datasheet's Hardware changelog (page near the back of the PDF).
- **Pinout, mounting pattern, and connector positions are stable across revisions** within a major hardware version (v1.x). A pinout or connector change triggers a major version bump (v2.0).
- **BOM changes for component-availability reasons** (e.g. a passive supplier substitution) are not considered revisions and are not separately announced.
- **Functional changes** (added feature, dropped feature, performance shift) are documented and announced via this LIFECYCLE.md and a GitHub release.

## Spares and repair

The AirBrain H743 is not designed as a field-repairable unit. Replacement boards are the standard remedy for a defective unit under warranty. Outside warranty, replacement boards remain orderable as long as the board is in production.

The following accessories are orderable separately:

- JST-SH cables (replacement, in the lengths supplied with the board).
- M3 silicone soft-mounting standoffs.

We do not stock individual electronic components for field repair.

## Contact

Lifecycle questions, multi-year programme inquiries, or formal letter-of-supply requests:

- [info@takeyourgear.com](mailto:info@takeyourgear.com)
- Mention "AirBrain lifecycle" in the subject

For urgent supply-continuity discussions tied to a defence or institutional programme, mention the programme name and timeline in the first email so we can route appropriately.
