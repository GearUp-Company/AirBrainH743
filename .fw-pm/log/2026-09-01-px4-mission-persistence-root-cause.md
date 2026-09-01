# PX4 mission persistence: root cause found (2026-09-01)

**Reported by:** LuxUAV, PX4 1.18.0 build 80, git `e8ea98b`, built 2026-08-18.
Mission uploads and executes correctly; full sequence Mission -> RTL -> auto
landing flown. After a full power-down (battery disconnect) the mission is gone
and must be re-uploaded. NAND/littlefs is healthy: `.ulg` logging writes fine.

## Root cause (code-read, verified at source)

`boards/gearup/airbrainh743/init/rc.board_defaults`:

```
# Store missions in RAM
param set-default SYS_DM_BACKEND 1
```

- `SYS_DM_BACKEND` enum, `src/modules/dataman/parameters.yaml`: `-1` disabled,
  `0` default storage (file on persistent storage), `1` RAM. **PX4 default is 0.**
- `DATAMAN_PERSISTENT_STORAGE`, `src/modules/dataman/Kconfig`: `default y`.
  airbrainh743 does not disable it, so the persistent path IS available.
- Introduced by commit `2df92cc` (Julian Oes, 2026-04-22) inside a logger-tuning
  commit. Stated reason: "no SD on this board". True, but the board has
  persistent storage as littlefs on W25N NAND, which the customer's own working
  logging proves.

## Assessment

Defect in our board default. Not a PX4 bug, not customer error. Affects every
AirBrain PX4 user who flies missions. Not billable work.

## Not yet verified

The fix is a code-read diagnosis. `SYS_DM_BACKEND 0` has NOT been bench-tested on
our hardware, and the reason RAM was chosen may go beyond "no SD" (NAND write
pattern, wear, or a bring-up issue not recorded in the commit message).

## Next

1. Ask Julian Oes why RAM, before changing his default upstream.
2. Bench: set `SYS_DM_BACKEND 0`, reboot, upload mission, full power cycle,
   confirm persistence AND that logging still works.
3. If clean: one-line board-default change plus upstream PR under the phase_9
   gate (build-verify, CONTRIBUTING at source, strip internal provenance).
