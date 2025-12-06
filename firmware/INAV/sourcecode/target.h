/*
 * AirBrain H743 (Maverick) target for INAV
 *
 * Board: STM32H743VIH6
 * IMU:   ICM-42688-P on SPI1
 * MAG:   LIS2MDL on I2C1
 * BARO:  DPS368 on I2C1
 * FLASH: W25N01G (SPI-NAND) on SPI2  [NOT ENABLED YET IN THIS HEADER]
 * PSU:   3–10S LiPo, onboard 5V/2A and 10V/2.5A regulators
 * UARTs: 1,2,3,4,5,7,8 + VCP
 * PWM:   8 motor outputs, DShot capable
 *
 * This file is intentionally written in the style of existing INAV H743 targets
 * (e.g. MATEKH743) so it has the best chance to compile in INAV with minimal
 * edits.
 */

#pragma once

#define TARGET_BOARD_IDENTIFIER "AIRB"
#define USBD_PRODUCT_STRING "AIRBRAINH743"

#define USE_TARGET_CONFIG

/****************************************
 * LEDS / BEEPER
 ****************************************/
#define LED0 PB15
#define LED1 PD11
#define LED2 PD15

#define BEEPER PA15
#define BEEPER_INVERTED
#define BEEPER_PWM_FREQUENCY 2500

/****************************************
 * SPI BUSES / IMU / (future flash)
 ****************************************/

// ---- SPI1 : IMU ----// ---- SPI1 : IMU ----
#define USE_SPI
#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN PA5
#define SPI1_MISO_PIN PA6
#define SPI1_MOSI_PIN PA7

// ICM-42688-P, but INAV 8 expects the 42605 macro names (but seen these macros in DAKEFPVF722X8/target.h)
#define USE_IMU_ICM42688P
#define ICM42688P_SPI_BUS BUS_SPI1
#define ICM42688P_CS_PIN PA3
#define ICM42688P_EXTI_PIN PC6
#define IMU_ICM42688P_ALIGN CW90_DEG

/*

// Below works in INAV v8
#define USE_IMU_ICM42605
#define ICM42605_SPI_BUS BUS_SPI1
#define ICM42605_CS_PIN PA3
#define ICM42605_EXTI_PIN PC6
#define IMU_ICM42605_ALIGN CW90_DEG

*/

// ---- SPI2 : onboard NAND flash (blackbox) ----
// NOTE: INAV mainly supports NOR flash / SD cards today.
// The AirBrain uses a W25N01G SPI-NAND (128 MByte).
// We'll declare SPI2 bus pins so the bus exists,
// but we DO NOT enable flash logging yet to avoid build breakage.
//
// You can add USE_FLASHFS / USE_xxx later once INAV has/accepts a NAND driver.
//
#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN PD3
#define SPI2_MISO_PIN PB14
#define SPI2_MOSI_PIN PC3
// Flash CS is on PD4 (for future enablement):
// #define FLASH_CS_PIN         PD4
// #define FLASH_SPI_BUS        BUS_SPI2
// #define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT
// (commented out for first-pass build safety)

// ---- SPI3 : auxiliary header / expansion ----
// Expose SPI3 (optional external peripherals)
// Keeping this consistent with style in other targets
#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN PE12
#define SPI3_MISO_PIN PE5
#define SPI3_MOSI_PIN PE6

/****************************************
 * I2C BUSES / BARO / MAG
 ****************************************/

#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL PB6
#define I2C1_SDA PB7

// Barometer (Infineon DPS368)
#define USE_BARO
#define USE_BARO_DPS310  // DPS310 driver also covers DPS368
#define BARO_I2C_BUS BUS_I2C1

// Magnetometer (LIS2MDL)
#define USE_MAG
#define USE_MAG_LIS3MDL  // LIS2MDL is register-compatible enough
#define MAG_I2C_BUS BUS_I2C1

// (Optional future sensors on I2C1: rangefinder, pitot, etc. can be added
// later)

/****************************************
 * UARTs / SERIAL
 ****************************************/

#define USE_VCP

#define USE_UART1
#define UART1_TX_PIN PA9
#define UART1_RX_PIN PA10

#define USE_UART2
#define UART2_TX_PIN PD5
#define UART2_RX_PIN PD6

#define USE_UART3
#define UART3_TX_PIN PD8
#define UART3_RX_PIN PD9

#define USE_UART4
#define UART4_TX_PIN PB9
#define UART4_RX_PIN PB8

#define USE_UART5
#define UART5_TX_PIN PB13
#define UART5_RX_PIN PB12

// UART6 not routed on this board, so we do NOT define USE_UART6

#define USE_UART7
#define UART7_TX_PIN PE8  // present on header according to pinout
#define UART7_RX_PIN PE7

#define USE_UART8
#define UART8_TX_PIN PE1
#define UART8_RX_PIN PE0

// We are not enabling SOFTSERIAL by default (can add later if you want a
// software port)

#define SERIAL_PORT_COUNT 8

// Board default: CRSF/ELRS on a hardware UART is common,
// but unlike Matek we won't force SERIALRX defaults here.
// That can be done in target defaults / diff later.
// (So we skip DEFAULT_RX_TYPE / SERIALRX_PROVIDER / SERIALRX_UART for now)

/****************************************
 * LED STRIP / PINIO
 ****************************************/

#define USE_LED_STRIP
#define WS2811_PIN PA2  // addressable LED strip output

#define USE_PINIO
#define USE_PINIOBOX
// The board exposes an AUX transistor / USER pin on PB3, so map it:
#define PINIO1_PIN PB3
// If you have a second controllable transistor output, add PINIO2_PIN <pin>
// here

/****************************************
 * POWER / ADC
 ****************************************/
// NOTE:
// INAV expects ADC channel mapping (ADC_CHANNEL_n_PIN etc.).
// That mapping is specific to MCU pin -> ADC channel numbers.
// We don't guess here, because a wrong map breaks voltage/current sensing
// and can block arming in some modes.
//
// For first-pass bring-up / build sanity, we intentionally DO NOT
// enable USE_ADC yet. You can add this once you map:
//
//   - VBAT sense (PC4 on your board)
//   - CURRENT sense (PC5 on your board)
//
// Example for later (do NOT paste until you confirm channels):
//
// #define USE_ADC
// #define ADC_INSTANCE                ADC1
//
// #define ADC_CHANNEL_1_PIN           PC4   // VBAT
// #define ADC_CHANNEL_2_PIN           PC5   // CURRENT
//
// #define VBAT_ADC_CHANNEL            ADC_CHN_1
// #define CURRENT_METER_ADC_CHANNEL   ADC_CHN_2
//
// #define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
// #define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
// #define DEFAULT_VOLTAGE_METER_SCALE 150
// #define CURRENT_METER_SCALE         99

/****************************************
 * MOTOR OUTPUT / DSHOT
 ****************************************/

// AirBrain provides 8 motor outputs and supports DShot ESCs
#define MAX_PWM_OUTPUT_PORTS 8
#define USE_DSHOT
#define USE_SERIAL_4WAY_BLHELI_INTERFACE

// We do NOT define Betaflight-style MOTORx_PIN or TIMER_PIN_MAPPING here.
// INAV H7 targets don't use that macro in the .h.
// Timer routing can go in target.c later if needed.

/****************************************
 * GPIO MASKS
 ****************************************/
// Matek defines these to indicate what ports are available for resource
// remapping. For first pass we'll expose full ports A..E except for JTAG SWD
// pins if needed. You can tighten these later if INAV maintainers ask.

#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD 0xffff
#define TARGET_IO_PORTE 0xffff

/****************************************
 * DEFAULT FEATURES
 ****************************************/

// Matek enables a bunch of defaults (OSD, telemetry, etc.).
// This board does not have MAX7456 OSD onboard, so we do NOT enable OSD by
// default. We do enable VBAT/CURRENT etc. later once ADC is finalized. For
// first-pass compile safety, leave DEFAULT_FEATURES undefined and let INAV
// defaults apply.

// #define DEFAULT_FEATURES (FEATURE_TELEMETRY | FEATURE_CURRENT_METER |
// FEATURE_VBAT | FEATURE_BLACKBOX)

// Blackbox-on-flash is intentionally not auto-enabled yet because W25N01G
// isn't declared above as a supported SPI flash device in INAV mainline.
