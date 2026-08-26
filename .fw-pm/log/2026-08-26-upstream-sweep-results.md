# 2026-08-26: upstream sweep results (agent, 39 tool-uses, all URLs in entry)

Well-supported negative: NO upstream issue describes in-flight loss of
exactly one timer group on H743 in 4.6/4.7. 4.7.0 contains every known
DShot/DMA fix (incl. PR 31398 cache flush/invalidate, first shipped in
4.7.0; 4.6.x never got it). Zero RCOutput/bdshot/shared_dma commits after
the Copter-4.7.0 tag: nothing to upgrade to.

Precedent proving the mechanism class: PR 20442 (tridge 2022, "vehicles
falling out of the sky", H743 flash-storage lockups; 32-bit timer TIM2/TIM5
timeout wraparound made stalls catastrophic; fixed 4.2/4.4-era).

Leading hypothesis from 4.7.0 code reading (hypothesis, not documented
incident): bidirectional-DShot capture contention collapsing a 2-motor
group. Mechanics: (a) dshot_send refuses per-group when group.dshot_state
is stuck mid-transaction: the whole group silently misses frames while
others run; (b) bdshot does whole-group pwmStop/pwmStart each cycle, so a
capture problem on the single BIDIR pin (M5 on TIM3, M7 on TIM2) disturbs
both motors of that group; (c) hwdef DMA_NOSHARE covers only UP streams;
the bdshot input-capture streams (TIM3_CH3, TIM2_CH3, TIM1_CH1/CH3) are
shareable and un-prioritized. TIM1 group is most robust (2 BIDIR channels,
APB2 advanced timer, first in allocation order): matches "1-4 never failed".

Evidence that decides it (what devs ask for): full .bin with RCOU vs
ESC[5..8] telemetry (FC stopped commanding vs ESC dropped), @SYS/dma.txt +
timers.txt, bdshot error rates before the event, params MOT_PWM_TYPE,
SERVO_BLH_BDMASK, SERVO_DSHOT_ESC, SERVO_DSHOT_RATE.

Discriminating experiments: SERVO_BLH_BDMASK=0 on a test frame (bdshot off:
losses stop => capture/reset path implicated); hwdef variant with TIM2/TIM3
CH streams added to DMA_NOSHARE, or BIDIR moved off the 2-motor groups.

Next: customer params first (protocol config decides everything), crash
logs, then targeted dev question to andyp1per (drafted, awaiting user ok).
