# s32duino Core

This is a library for STM32F0 chips. It's based on the [official stm32 library](https://github.com/stm32duino/Arduino_Core_STM32)
*WARNING*: This is still a WIP Project. It probably contains quite a few bugs and I'm not sure if going to continue developement
Chips available:

- STM32F030F4

## Getting Started

1. Download the latest version from https://github.com/david-sawatzke/s32duino
2. Unzip it into [Arduino]/hardware folder
3. Install Arduino Zero from the board manager for the arm-none-eabi-gcc compiler

## Differences

- There are no pin numbers, each Pin is named according to the datasheet, e.g. PA4, PA5
- Pins are 32 bit big
- double is 64 bytes and int is 32 bytes
- Programming can only be done via [blackmagic debugging probe](https://github.com/blacksphere/blackmagic)

## Troubleshooting

If you have any issue to download/use a package, you could [file an issue on Github](https://github.com/david-sawatzke/s32duino/issues/new).

## Working Libraries
- Core
- SPI
  - UsingInterrupt is a no-op
  - Not tested

## TODO

- Add more chips from the stm32f0 family
- Add a board manager url
- Add more programmers
- Implement more libraries
