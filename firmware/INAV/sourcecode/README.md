<!--
NOT a snapshot of upstream. INAV target for AIRBRAINH743 has not been merged into iNavFlight/inav as of 2026-05-08.
These files are GearUp's local target definition, used to produce the beta INAV builds in `firmware/INAV/bin/`.
-->

# INAV target source for AIRBRAINH743

**Status: beta, not upstreamed.** As of 2026-05-08, the AIRBRAINH743 INAV target has not been merged into [iNavFlight/inav](https://github.com/iNavFlight/inav). The files in this folder are GearUp's local target definition, used to produce the beta builds in [`firmware/INAV/bin/`](../bin/).

If and when the target is merged upstream, this folder will be refreshed from `iNavFlight/inav` and this README replaced with a snapshot pointer.

## Files

| File | Purpose |
|---|---|
| `target.h` | Pin map and feature flags |
| `target.c` | Timer / DMA / pin assignments |
| `config.c` | Default INAV configuration |
| `CMakeLists.txt` | INAV build target wiring |
