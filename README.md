# Operation-DITTO teensy-controller

## About

This is the source code for the OP-DITTO teensy-controller, intended to be flashed onto a Teensy board using [Teensyduino](https://www.pjrc.com/teensy/td_download.html).

---

## Explanation

teensy-controller serves as a request handler and middle-man between the PSP UART hardware and the second analog nub. It receives a byte (0-2) from the user program using the [psp-uart-library](https://github.com/Operation-DITTO/psp-uart-library). The byte is analyzed and teensy-controller sends a different set of bytes back, respective to axis value.