# Sabena "Dory" crash-log analysis — TIM-timer hypothesis TESTED and REJECTED

Date: 2026-08-27. Target: AIRBRAINH743 / ArduPilot 4.8.0-dev. Log: "2026-08-14 14-05-10.bin" (Sabena, delivered 2026-08-27). Analyst: fw-pm.

## Question
Is the in-flight output failure caused by a TIM timer / DMA output-group fault on the AirBrain, per the 26/08 hypothesis (outputs grouped TIM1=1-4, TIM3=5-6, TIM2=7-8)?

## Conclusion: NO. Single-channel thrust loss on output ch2 (frame Motor 5). FC output stage exonerated.

## Evidence
1. hwdef groups: TIM1=out1-4, TIM3=out5-6, TIM2=out7-8. Config: OCTA-X, MOT_PWM_TYPE=5 (DShot600), bidir DShot all 8 (BDMASK=255), so per-motor RPM telemetry available.
2. Primary event: ERR subsys=25 THRUST_LOSS_CHECK ecode=1 at t=185.1s — FIRST error, BEFORE any EKF/compass error.
3. Commanded (RCOU) vs actual (ESC RPM), failure window 185-190s:
   - out ch2 RPM collapses ~7900 -> ~3200 from 186.0s; FC then pins ch2 to min (1150).
   - out ch1, ch3, ch4 (SAME TIM1 group as ch2) stay HEALTHY, RPM tracks command throughout.
   - out ch6 "alternates" but RPM TRACKS command (1906->8857, 1150->4714): healthy motor, FC control oscillation, not a fault.
4. Bidir DShot telemetry from ch2's ESC CONTINUES at full rate through the failure (70 msgs 185-190s, same as healthy chans), reporting real low RPM. A TIM1 DMA/signal fault would stop the ESC frames and thus the telemetry. It did not.
5. Cascade: thrust loss (185.1) -> attitude fight -> EKF Failsafe (189.8) + mag-field error (xy diff 277>100, consistent with erratic current disturbing compass) + GPS glitch -> disarm ~193s.

## Why not a timer: ch1/ch2/ch3/ch4 share TIM1 (burst-DShot shares TIM1_UP DMA). A timer/DMA fault fails the whole group together. Only ch2 failed; ch1/ch3/ch4 stayed healthy. A shared-timer group cannot drop one channel and keep three.

## Most likely root cause (downstream of FC, on output ch2 = frame Motor 5): ESC desync or motor/prop/mechanical thrust loss on that single channel. ESC alive + reporting + motor underperforming command == classic desync/mechanical signature.

## Caveats / to confirm
- One crash log analysed (14-05-10). Earlier report mentioned a second incident; request/analyse its log too.
- Confirm on Sabena side: inspect ch2 motor/ESC/prop/solder; check for desync markers; frame config (FRAME_CLASS=4 OCTA but out7-8 show 0 RPM / no telemetry — only 6 active motors, worth confirming).
