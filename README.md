# s32duino Core

This is a library for STM32F0 chips.

*WARNING*: This is still a WIP Project. It probably contains quite a few bugs and I'm not sure if going to continue developement

Chips available:

## Supported chips

- STM32F030F4

## Getting Started

1. Download the latest version from https://github.com/david-sawatzke/s32duino
2. Unzip it into [Arduino]/hardware folder
3. Install Arduino Zero from the board manager for the arm-none-eabi-gcc compiler

## Differences

- There are no pin numbers, each Pin is named according to the datasheet, e.g. PA4, PA5
- Pins have the PinNumber type
  (If using a library, you can see if it uses an int for pins and just cast it
  to int. You will get a few warnings, but it'll probably work)
- A double has 64 bits and an int has 32 bits
- Programming can only be done via [blackmagic debugging probe](https://github.com/blacksphere/blackmagic)

## Code Size

As this library doesn't use a HAL, the compiled binaries are comparable to the
AVR core:

- Blink: 1956 Bytes
- DigitalReadSerial: 2072 Bytes
- ToneMultiple: 2188 Bytes
- Autoscroll: 3044 Bytes
- ArduinoISP: 4120 Bytes

## Troubleshooting

If you have any issue to download/use a package, you could [file an issue on Github](https://github.com/david-sawatzke/s32duino/issues/new).

## Working Libraries
- Core
- LiquidCrystal
  - Not tested
- SPI
  - UsingInterrupt isn't there
  - Not tested
- Servo
  - Not tested

## TODO

- Add more chips from the stm32f0 family
- Add a board manager url
- Add more programmers
- Implement more libraries

## LICENSE
Most of the files have copyright notices, which apply. The rest is licensed
under GPLv2 or later
