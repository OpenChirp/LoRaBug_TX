/**@file app.c
 *
 * @brief Send packet, indicate send status using LEDs, sleep, and repeat.
 * @author Craig Hesling
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>

/* TI-RTOS Header files */
// #include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Low level drivers */
#include <driverlib/sys_ctrl.h> // SysCtrlSystemReset()

/* Board Header files */
#include "LORABUG.h"

/* LoRa Radio Header files */
#include "board.h" // The LoRaMac-node/src/boads/LoRaBug/board.h file
#include "radio.h"

#define TASKSTACKSIZE   512

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

/* Event handle and constants */
#define EVENT_TXDONE Event_Id_00
#define EVENT_TXTIMEOUT Event_Id_01
static Event_Struct eventsStruct;
static Event_Handle events;

/* Pin driver handles */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;
static PIN_Handle btnPinHandle;
static PIN_State btnPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
static const PIN_Config ledPinTable[] = {
    Board_RLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL,
    Board_GLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL,
    PIN_TERMINATE
};
static const PIN_Config btnPinTable[] = {
    Board_BTN | PIN_INPUT_EN | PIN_NOPULL | PIN_IRQ_NEGEDGE,
    PIN_TERMINATE
};

/* Button callback handler */
void btnCallback(PIN_Handle handle, PIN_Id pinId) {
    // This will hard reset the board.
    // This should trigger the bootloader, since the button is still depressed.
    SysCtrlSystemReset();
}

/* Radio callback handlers */
static void TxDone() {
    Event_post(events, EVENT_TXDONE);
}
static void TxTimeout() {
    Event_post(events, EVENT_TXTIMEOUT);
}
static const RadioEvents_t RadioEventHandlers = {
   .TxDone    = TxDone,
   .TxTimeout = TxTimeout,
};


/* Radio Settings */
#define RF_FREQUENCY                                915e6     // Hz (915MHz band is 902e3 to 928e3)
#define TX_OUTPUT_POWER                             20        // dBm

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx (uint16_t)
#define LORA_SYMBOL_TIMEOUT                         5         // Symbols - Up to 1023 symbols (for RX)
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false
#define CRC_ON                                      true
#define TRANSMISSION_TIMEOUT                        3e3       // ms



Void mainTask(UArg arg0, UArg arg1)
{
    const uint8_t  msg[] = "Hello air space!";

    Radio.Init((RadioEvents_t *)&RadioEventHandlers);
    Radio.SetChannel(RF_FREQUENCY); // Must set channel before SetTxConfig
    Radio.SetTxConfig(MODEM_LORA,
                      TX_OUTPUT_POWER,
                      0, // Frequency Deviation (FSK only)
                      LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH,
                      LORA_FIX_LENGTH_PAYLOAD_ON,
                      CRC_ON,
                      false, // FreqHopOn
                      0,     // HopPeriod
                      LORA_IQ_INVERSION_ON,
                      TRANSMISSION_TIMEOUT);

    while (1) {
        Radio.Send((uint8_t *)msg, sizeof(msg)-1);
        UInt e = Event_pend(events, Event_Id_NONE, EVENT_TXDONE|EVENT_TXTIMEOUT, BIOS_WAIT_FOREVER);
        switch (e) {
        case EVENT_TXDONE:
            // Green
            PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_OFF);
            PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_ON);
            break;
        case EVENT_TXTIMEOUT:
            // Red
            PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_ON);
            PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_OFF);
            break;
        default:
            // Green + Red
            PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_ON);
            PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_ON);
            break;
        }
        Radio.Sleep();

        // Wait for lights to be seen
        Task_sleep((UInt)arg0);
        // Sleep Hard
        PIN_setOutputValue(ledPinHandle, Board_RLED, Board_LED_OFF);
        PIN_setOutputValue(ledPinHandle, Board_GLED, Board_LED_OFF);
        Task_sleep((UInt)arg0);
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
    Task_construct(&task0Struct, (Task_FuncPtr)mainTask, &taskParams, NULL);

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
    if(!ledPinHandle) {
        System_abort("Error initializing board LED pins\n");
    }
    /* Open Button pin */
    btnPinHandle = PIN_open(&btnPinState, btnPinTable);
    if(!btnPinHandle) {
        System_abort("Error initializing board Button pin\n");
    }
    PIN_registerIntCb(btnPinHandle, btnCallback);

    Event_construct(&eventsStruct, NULL);
    events = Event_handle(&eventsStruct);

    /* Start BIOS */
    BIOS_start();

    return (0);
}
