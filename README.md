# Chip8 Interpreter

## Overview

This project is a C implementation of a Chip8 interpreter, which can run classic Chip8 ROMs such as games. Intended mostly as learning project to grasp the ideas behind virtual machines and to better understand hardware.

The project uses SDL2 for rendering and is mainly based on Cowgod's Chip-8 technical reference.

## Project Status

- Successfully rendering the IBM logo using IBM test ROM
- Implemented basic opcode handling using dispatch tables.
- Implemented a subset of the Chip8 instructiojns.

## TODO

1. **Implement Remaining Instructions**: The project currently only supports a subset of Chip8 instructions.
2. **Implement Input Handling**: Allow user input through keyboard, maybe controllers.
3. **Refactoring & Introduce Abstractions**: For better maintainability / flexibility.
4. **Tests**


## Building

1. Install SDL2
2. Clone the repo
3. Build using CMAKE
