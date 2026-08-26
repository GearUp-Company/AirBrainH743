# 2026-08-26: Andy Piper reply, contention hypothesis refuted

Reply within 8 minutes (DM): "on an H7 the _UP channel and _CH channels
are shared. There should be no contention." + "per timer".

Meaning: on H743, each timer's UP and CH DMA channels are one shared
resource per timer, so DMA_NOSHARE on the UP streams already isolates the
capture side. Consequences:
- capture-stream DMA contention is NOT a plausible group-loss path (refuted
  by subsystem maintainer);
- no hwdef change warranted (CH streams in noshare = no-op);
- group-collapse machinery (stuck dshot_state) remains, but trigger must be
  elsewhere; probability shifted toward non-software causes (ESC desync,
  power/wiring per arm, telemetry glitch).

Investigation fully blocked on customer data: .param (bdshot yes/no) + two
crash logs (RCOU commanded-vs-actual). Requested by mail 2026-08-26.
