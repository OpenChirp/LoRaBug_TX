/**@file blinky_sleep.c
 *
 * @brief Blink both LEDs, sleep, and repeat.
 * @author Craig Hesling <craig@hesling.com>
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

/* TI-RTOS Header files */
// #include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header files */
#include "LORABUG.h"

/* LoRa Radio Header files */
#include "board.h" // The LoRaMac-node/src/boads/LoRaBug/board.h file
#include "radio.h"

#define TASKSTACKSIZE   512

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config ledPinTable[] = {
    Board_RLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW  | PIN_PUSHPULL,
    Board_GLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL,
    PIN_TERMINATE
};

/*
 *  ======== heartBeatFxn ========
 *  Toggle the Board_LED0. The Task_sleep is determined by arg0 which
 *  is configured for the heartBeat Task instance.
 */
Void heartBeatFxn(UArg arg0, UArg arg1)
{
    Radio.Sleep();

    while (1) {
        // Red
        PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_ON);
        PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_OFF);
        Task_sleep((UInt)arg0);
        // Green
        PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_OFF);
        PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_ON);
        Task_sleep((UInt)arg0);
        // Sleep Hard
        PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_OFF);
        PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_OFF);
        Task_sleep((UInt)arg0 * 3);
    }
}

/**
 * The main entrance point of the firmware, before the RTOS is enabled.
 * We setup the default task and IO, and then start the RTOS
 */
int main(void)
{
    Task_Params taskParams;

    /* Call board init functions */
    Board_initGeneral();
    // Board_initI2C();
    Board_initSPI();
    // Board_initUART();
    // Board_initWatchdog();

    BoardInitMcu(); // Initialize LoRa Stack - Must call initSPI before

    /* Construct heartBeat Task  thread */
    Task_Params_init(&taskParams);
    taskParams.arg0 = 1000000 / Clock_tickPeriod;
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)heartBeatFxn, &taskParams, NULL);

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
    if(!ledPinHandle) {
        System_abort("Error initializing board LED pins\n");
    }

    /* Start BIOS */
    BIOS_start();

    return (0);
}
