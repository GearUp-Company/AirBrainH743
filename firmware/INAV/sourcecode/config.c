#include "fc/config.h"

#include <stdint.h>

#include "fc/fc_msp_box.h"
#include "io/piniobox.h"
#include "platform.h"

void targetConfiguration(void)
{
    // Map first PINIO (PB3) to USER1 in the Modes tab by default
    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;

    // Enable PWM beeper drive (tones instead of just on/off)
    beeperConfigMutable()->pwmMode = true;
}
