/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       LORABUG.h
 *
 *  @brief      LoRaBug Board Specific header file.
 *
 *  NB! This is the board file for LoRabug PCB version 3.1
 *
 *  ============================================================================
 */
#ifndef __LORABUG_H__
#define __LORABUG_H__

#ifdef __cplusplus
extern "C" {
#endif

/** ============================================================================
 *  Includes
 *  ==========================================================================*/
#include <ti/drivers/PIN.h>
#include <driverlib/ioc.h>

/** ============================================================================
 *  Externs
 *  ==========================================================================*/
extern const PIN_Config BoardGpioInitTable[];

/** ============================================================================
 *  Defines
 *  ==========================================================================*/

/* Same RF Configuration as 7x7 EM */
#define CC2650EM_7ID
#define CC2650_LAUNCHXL

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>        <pin mapping>
 */

/* Header Pins */
#define Board_HDR_HDIO0             IOID_5           /* High-Drive Capable Digital */
#define Board_HDR_HDIO1             IOID_6           /* High-Drive Capable Digital */
#define Board_HDR_HDIO2             IOID_7           /* High-Drive Capable Digital */
#define Board_HDR_ADIO0             IOID_23          /* Analog Capable */
#define Board_HDR_ADIO1             IOID_24          /* Analog Capable */
#define Board_HDR_ADIO2             IOID_25          /* Analog Capable */
#define Board_HDR_ADIO3             IOID_26          /* Analog Capable */
#define Board_HDR_ADIO4             IOID_27          /* Analog Capable */
#define Board_HDR_ADIO5             IOID_28          /* Analog Capable */
#define Board_HDR_ADIO6             IOID_29          /* Analog Capable */
#define Board_HDR_ADIO7             IOID_30          /* Analog Capable */

/* Discrete outputs */
#define Board_RLED                  IOID_8
#define Board_GLED                  IOID_9
#define Board_LED_ON                1
#define Board_LED_OFF               0

/* Discrete inputs */
#define Board_BTN                   IOID_22          /* Active low with external pull-up */

/* SX1276 LoRa Radio Pins */
#define Board_SX_MISO               IOID_14
#define Board_SX_MOSI               IOID_13
#define Board_SX_SCK                IOID_15
#define Board_SX_NSS                IOID_12
#define Board_SX_RF_CTRL1           IOID_0           /* Controls RF switches complement pair positive */
#define Board_SX_RF_CTRL2           IOID_10          /* Controls RF switches complement pair negative */
#define Board_SX_RESET              IOID_11          /* Active Low */
#define Board_SX_DIO0               IOID_21
#define Board_SX_DIO1               IOID_20
#define Board_SX_DIO2               IOID_19
#define Board_SX_DIO3               IOID_18
#define Board_SX_DIO4               IOID_17
#define Board_SX_DIO5               IOID_16

/* USB UART */
#define Board_UART_RX               IOID_2          /* FTDI TXD  */
#define Board_UART_TX               IOID_3          /* FTDI RXD  */
#define Board_UART_CTS              PIN_UNASSIGNED  /* CTS  */
#define Board_UART_RTS              PIN_UNASSIGNED  /* RTS  */

/* SPI Board */
#define Board_SPI0_MISO             Board_SX_MISO
#define Board_SPI0_MOSI             Board_SX_MOSI
#define Board_SPI0_CLK              Board_SX_SCK
#define Board_SPI0_CSN              PIN_UNASSIGNED    /* Toggle Manually */

#define Board_SPI1_MISO             PIN_UNASSIGNED
#define Board_SPI1_MOSI             PIN_UNASSIGNED
#define Board_SPI1_CLK              PIN_UNASSIGNED
#define Board_SPI1_CSN              PIN_UNASSIGNED

/* I2C */
#define Board_I2C0_SCL0             PIN_UNASSIGNED
#define Board_I2C0_SDA0             PIN_UNASSIGNED

/* SPI */
#define Board_SPI_FLASH_CS          PIN_UNASSIGNED
#define Board_FLASH_CS_ON           0
#define Board_FLASH_CS_OFF          1

#define Board_DIO23_ANALOG          IOID_23
#define Board_DIO24_ANALOG          IOID_24
#define Board_DIO25_ANALOG          IOID_25
#define Board_DIO26_ANALOG          IOID_26
#define Board_DIO27_ANALOG          IOID_27
#define Board_DIO28_ANALOG          IOID_28
#define Board_DIO29_ANALOG          IOID_29
#define Board_DIO30_ANALOG          IOID_30

/* PWM outputs */
#define Board_PWMPIN0                       Board_RLED
#define Board_PWMPIN1                       Board_GLED
#define Board_PWMPIN2                       PIN_UNASSIGNED
#define Board_PWMPIN3                       PIN_UNASSIGNED
#define Board_PWMPIN4                       PIN_UNASSIGNED
#define Board_PWMPIN5                       PIN_UNASSIGNED
#define Board_PWMPIN6                       PIN_UNASSIGNED
#define Board_PWMPIN7                       PIN_UNASSIGNED

/** ============================================================================
 *  Instance identifiers
 *  ==========================================================================*/
/* Generic I2C instance identifiers */
#define Board_I2C                   LORABUG_I2C0
/* Generic SPI instance identifiers */
#define Board_SPI0                  LORABUG_SPI0
#define Board_SPI1                  LORABUG_SPI1
/* Generic UART instance identifiers */
#define Board_UART                  LORABUG_UART0
/* Generic Crypto instance identifiers */
#define Board_CRYPTO                LORABUG_CRYPTO0
/* Generic GPTimer instance identifiers */
#define Board_GPTIMER0A             LORABUG_GPTIMER0A
#define Board_GPTIMER0B             LORABUG_GPTIMER0B
#define Board_GPTIMER1A             LORABUG_GPTIMER1A
#define Board_GPTIMER1B             LORABUG_GPTIMER1B
#define Board_GPTIMER2A             LORABUG_GPTIMER2A
#define Board_GPTIMER2B             LORABUG_GPTIMER2B
#define Board_GPTIMER3A             LORABUG_GPTIMER3A
#define Board_GPTIMER3B             LORABUG_GPTIMER3B
/* Generic PWM instance identifiers */
#define Board_PWM0                  LORABUG_PWM0
#define Board_PWM1                  LORABUG_PWM1
#define Board_PWM2                  LORABUG_PWM2
#define Board_PWM3                  LORABUG_PWM3
#define Board_PWM4                  LORABUG_PWM4
#define Board_PWM5                  LORABUG_PWM5
#define Board_PWM6                  LORABUG_PWM6
#define Board_PWM7                  LORABUG_PWM7

/** ============================================================================
 *  Number of peripherals and their names
 *  ==========================================================================*/

/*!
 *  @def    LORABUG_I2CName
 *  @brief  Enum of I2C names on the CC2650 dev board
 */
typedef enum LORABUG_I2CName {
    LORABUG_I2C0 = 0,

    LORABUG_I2CCOUNT
} LORABUG_I2CName;

/*!
 *  @def    LORABUG_CryptoName
 *  @brief  Enum of Crypto names on the CC2650 dev board
 */
typedef enum LORABUG_CryptoName {
    LORABUG_CRYPTO0 = 0,

    LORABUG_CRYPTOCOUNT
} LORABUG_CryptoName;


/*!
 *  @def    LORABUG_SPIName
 *  @brief  Enum of SPI names on the CC2650 dev board
 */
typedef enum LORABUG_SPIName {
    LORABUG_SPI0 = 0,
    LORABUG_SPI1,

    LORABUG_SPICOUNT
} LORABUG_SPIName;

/*!
 *  @def    LORABUG_UARTName
 *  @brief  Enum of UARTs on the CC2650 dev board
 */
typedef enum LORABUG_UARTName {
    LORABUG_UART0 = 0,

    LORABUG_UARTCOUNT
} LORABUG_UARTName;

/*!
 *  @def    LORABUG_UdmaName
 *  @brief  Enum of DMA buffers
 */
typedef enum LORABUG_UdmaName {
    LORABUG_UDMA0 = 0,

    LORABUG_UDMACOUNT
} LORABUG_UdmaName;

/*!
 *  @def    LORABUG_GPTimerName
 *  @brief  Enum of GPTimer parts
 */
typedef enum LORABUG_GPTimerName
{
    LORABUG_GPTIMER0A = 0,
    LORABUG_GPTIMER0B,
    LORABUG_GPTIMER1A,
    LORABUG_GPTIMER1B,
    LORABUG_GPTIMER2A,
    LORABUG_GPTIMER2B,
    LORABUG_GPTIMER3A,
    LORABUG_GPTIMER3B,
    LORABUG_GPTIMERPARTSCOUNT
} LORABUG_GPTimerName;

/*!
 *  @def    LORABUG_GPTimers
 *  @brief  Enum of GPTimers
 */
typedef enum LORABUG_GPTimers
{
    LORABUG_GPTIMER0 = 0,
    LORABUG_GPTIMER1,
    LORABUG_GPTIMER2,
    LORABUG_GPTIMER3,
    LORABUG_GPTIMERCOUNT
} LORABUG_GPTimers;

/*!
 *  @def    LORABUG_PWM
 *  @brief  Enum of PWM outputs on the board
 */
typedef enum LORABUG_PWM
{
    LORABUG_PWM0 = 0,
    LORABUG_PWM1,
    LORABUG_PWM2,
    LORABUG_PWM3,
    LORABUG_PWM4,
    LORABUG_PWM5,
    LORABUG_PWM6,
    LORABUG_PWM7,
    LORABUG_PWMCOUNT
} LORABUG_PWM;

/*!
 *  @def    LORABUG_ADCBufName
 *  @brief  Enum of ADCs
 */
typedef enum LORABUG_ADCBufName {
    LORABUG_ADCBuf0 = 0,
    LORABUG_ADCBufCOUNT
} LORABUG_ADCBufName;


/*!
 *  @def    LORABUG_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum LORABUG_ADCName {
    LORABUG_ADC0 = 0,
    LORABUG_ADC1,
    LORABUG_ADC2,
    LORABUG_ADC3,
    LORABUG_ADC4,
    LORABUG_ADC5,
    LORABUG_ADC6,
    LORABUG_ADC7,
    LORABUG_ADCDCOUPL,
    LORABUG_ADCVSS,
    LORABUG_ADCVDDS,
    LORABUG_ADCCOUNT
} LORABUG_ADCName;

/*!
 *  @def    LORABUG_WatchdogName
 *  @brief  Enum of Watchdogs on the CC2650_LAUNCHXL dev board
 */
typedef enum LORABUG_WatchdogName {
    LORABUG_WATCHDOG0 = 0,

    LORABUG_WATCHDOGCOUNT
} LORABUG_WatchdogName;

#ifdef __cplusplus
}
#endif

#endif /* __LORABUG_H__ */
