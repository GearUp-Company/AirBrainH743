# 2026-08-26: timer-group crash investigation opened

Trigger: customer on-site meeting 26/08. Two in-flight incidents on an
octocopter running ArduCopter 4.7.0: once motors 5-6 stopped, once motors
7-8, never motors 1-4. Customer hypothesis: software issue tied to timer
groups.

Verified in ardupilot clone (master 1ea89b0, hwdef/AIRBRAINH743/hwdef.dat):
M1-M4 = TIM1 CH1-4 (BIDIR on M1, M3); M5-M6 = TIM3 CH3/CH4 (BIDIR M5);
M7-M8 = TIM2 CH3/CH4 (BIDIR M7); M9 = TIM5_CH3.
DMA_NOSHARE and DMA_PRIORITY both list TIM1_UP TIM3_UP TIM2_UP SPI1*.
Grouping matches the customer's description exactly: incidents sit in the
two non-TIM1 groups.

Actions: upstream sweep agent launched (GitHub issues, Discourse, 4.6/4.7
RCOutput/DShot changes). Crash logs + .param requested from customer.
Dev-check question drafted after sweep results, customer anonymized.
