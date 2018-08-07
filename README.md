# Example Summary
This example cycles through illuminating the red LED, the green LED,
and then sleeping at a rate determined by the `arg0` parameter for the
constructed heart beat Task.
It is intended to be a starting point for new development where
a minimal footprint is needed.

See [blinky_sleep.c](blinky_sleep.c) for more information.

# Special Cloning

```
git clone https://github.com/OpenChirp/LoRaBug_BlinkySleep.git
git submodule update --init --recursive
```

# Peripherals Exercised

* `Board_RLED`
* `Board_GLED`
* `Radio.Sleep()`

# Application Design Details

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