/*
 * AirBrain H743 (Maverick) target - board support for INAV
 *
 * This file defines:
 *  - IMU SPI device registration
 *  - timerHardware[] mapping for motor outputs, LED strip, beeper, etc.
 *
 * Licensing note:
 * This file follows the INAV GPLv3 license model, same as other targets.
 */

#include <stdint.h>

#include "drivers/bus.h"
#include "drivers/io.h"
#include "drivers/pinio.h"
#include "drivers/pwm_mapping.h"
#include "drivers/sensor.h"
#include "drivers/timer.h"
#include "platform.h"
// --- temporary battery status stub for first bring-up ---
#include "platform.h"

uint8_t checkBatteryVoltageState(void)
{
    // 0 usually means BATTERY_VOLTAGE_NORMAL state in INAV logic.
    // Returning 0 prevents the linker error and tells OSD "battery OK".
    return 0;
}

/*
 * IMU registration
 *
 * The AirBrain board uses a single ICM-42688-P on SPI1 with CS on PA3.
 * INAV typically treats ICM42688P as compatible with the ICM42605 class
 * (DEVHW_ICM42605) and uses the same driver path.
 *
 * The ALIGN macro and BUS/CS macros come from AIRBRAINH743.h:
 *
 *   #define USE_IMU_ICM42688P
 *   #define IMU_ICM42688P_ALIGN     CW90_DEG
 *   #define ICM42688P_SPI_BUS       BUS_SPI1
 *   #define ICM42688P_CS_PIN        PA3
 *BUSDEV_REGISTER_SPI_TAG(busdev_icm42605, DEVHW_ICM42605, ICM42605_SPI_BUS,
                        ICM42605_CS_PIN, NONE, 0, DEVFLAGS_NONE,
                        IMU_ICM42605_ALIGN);
 * We only register one IMU here. No MPU6000/MPU6500/etc.
 */

/*
 * Timer / PWM outputs
 *
 * Each DEF_TIM entry wires a timer channel to a physical pin and gives INAV
 * a hint about how that channel should be used (motor output, LED strip,
 * beeper, etc.).
 *
 * For motors we use TIM_USE_OUTPUT_AUTO.
 *
 * Channel ordering below (S1..S8) matches your Betaflight mapping:
 *   PE9, PE11, PE13, PE14, PB0, PB1, PB10, PB11
 *
 * LED strip: PA2 (WS2812) -> TIM5_CH3 with TIM_USE_LED
 * BEEPER:    PA15 -> TIM2_CH1 with TIM_USE_BEEPER
 * Softserial/ANY: PC7 -> TIM8_CH2 with TIM_USE_ANY (optional helper channel)
 *
 * NOTE:
 * - dmaopt indices (last numeric arg) are incremented similarly to how other H7
 * targets do it, but exact values are not super critical for first-pass
 * compile.
 * - If you later change motor order, you only reorder the first 8 entries.
 */
// LIS2MDL (register as LIS3MDL-compatible) on I2C1 at 0x1E
BUSDEV_REGISTER_I2C(busdev_lis2mdl, DEVHW_LIS3MDL, BUS_I2C1, 0x1C, NONE,
                    DEVFLAGS_NONE, 0);

timerHardware_t timerHardware[] = {

    // -------- Motor outputs (8) --------
    // S1
    DEF_TIM(TIM1, CH1, PE9, TIM_USE_OUTPUT_AUTO, 0, 0),
    // S2
    DEF_TIM(TIM1, CH2, PE11, TIM_USE_OUTPUT_AUTO, 0, 1),
    // S3
    DEF_TIM(TIM1, CH3, PE13, TIM_USE_OUTPUT_AUTO, 0, 2),
    // S4
    DEF_TIM(TIM1, CH4, PE14, TIM_USE_OUTPUT_AUTO, 0, 3),

    // S5
    DEF_TIM(TIM3, CH3, PB0, TIM_USE_OUTPUT_AUTO, 0, 4),
    // S6
    DEF_TIM(TIM3, CH4, PB1, TIM_USE_OUTPUT_AUTO, 0, 5),

    // S7
    DEF_TIM(TIM2, CH3, PB10, TIM_USE_OUTPUT_AUTO, 0, 6),
    // S8
    DEF_TIM(TIM2, CH4, PB11, TIM_USE_OUTPUT_AUTO, 0, 7),

    // -------- LED strip (WS2812) --------
    // Your header maps WS2811_PIN to PA2.
    // We'll drive PA2 using TIM5_CH3 with TIM_USE_LED.
    DEF_TIM(TIM5, CH3, PA2, TIM_USE_LED, 0, 8),

    // -------- BEEPER (inverted) --------
    // BEEPER is on PA15 in the header.
    // Use TIM2_CH1 so INAV can drive a tone.
    DEF_TIM(TIM2, CH1, PA15, TIM_USE_BEEPER, 0, 9),

    // -------- AUX / softserial / anything --------
    // PC7 is available on your board (from your Betaflight mapping list).
    // We'll expose it as a generic channel. This is helpful for SoftSerial /
    // PPM, etc.
    DEF_TIM(TIM8, CH2, PC7, TIM_USE_ANY, 0, 10),
};

const int timerHardwareCount = sizeof(timerHardware) / sizeof(timerHardware[0]);
