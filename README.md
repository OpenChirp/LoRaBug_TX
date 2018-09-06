# Example Summary
This example cycles through sending a LoRa packet, indicating the send status
using the onboard LEDs, and then sleeping.

This example also configures the button to reset and trigger
the bootloader for immediate programming using a serial bootloader utility,
like [ccbootutil](https://github.com/openchirp/ccbootutil).

See [app.c](app.c) for more information.

# Cloning and Submodules

```
git clone https://github.com/OpenChirp/LoRaBug_TX.git
git submodule update --init --recursive
```

# Features Exercised

* LEDs
* Radio for TX Only
* Button callback (with bootloader launching)

# Application Design Details

## Bootloader
We have configured the button to make the MCU jump into the bootloader
when pressed. This allows for quick programming using a bootloader utility.
To make this happen, we utilize two key features.
1. The ability to have the MCU hard reset itself when the button is pressed
   (uses `SysCtrlSystemReset()`).
2. The ability to use the button as the backdoor to trigger the bootloader
   on boot (configured in [ccfg.c](ccfg.c)).

When the button is pressed, the button callback forces a hard reset.
Since you finger is still depressing the button when it starts to boot,
the bootloader backdoor is triggered, which launches the ROM bootloader.
The green LED always glows when the bootloader is launched.

## Minimal footprint
This example is based on the CC2650 Launchpad empty_min example project.

The empty_min is the same as the Empty example except many development
and debug features are disabled. For example:

* No Kernel Idle task
* No stack overflow checking
* No Logs or Asserts are enabled

> The ROM is being used in this example. This is controlled
> by the following lines in the *.cfg* file:

```
var ROM = xdc.useModule('ti.sysbios.rom.ROM');
    ROM.romName = ROM.CC2650;
```
> Since the kernel in the ROM is being used, there is no logging or assert
checking done by the kernel.

# References

* For GNU and IAR users, please read the following website for details
  about enabling [semi-hosting](http://processors.wiki.ti.com/index.php/TI-RTOS_Examples_SemiHosting)
  in order to view console output.

* Please refer to the __Memory Footprint Reduction__ section in the
TI-RTOS User Guide *spruhd4.pdf* for a complete and detailed list of the
differences between the empty minimal and empty projects.

# Developer Notes
Unfortunately, the LoRaMAC-node implementation of LoRaWAN uses C99's in for loop
variable declaration. For this reason, you MUST change the C compiler Language
mode to allow C99 syntax.
Currently, the C99 syntax usage is isolated to the
[LoRaMac.c](loramac/src/mac/LoRaMac.c) file.