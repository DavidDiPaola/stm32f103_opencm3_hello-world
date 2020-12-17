# STM32F103 libopencm3 hello world

## Requirements

- ARM toolchain (Debian/Ubuntu: `sudo apt install gcc-arm-none-eabi`)
- ARM GDB (Debian/Ubuntu: `sudo apt install gdb-multiarch`)
- OpenOCD (Debian/Ubuntu: `sudo apt install openocd`)
- Python (for libopencm3)

## Usage

### Build and flash

1. Build: `make`
  - Build with alternate toolchain: `make TARGET_PREFIX=arm-something-else-`
2. Flash: `make flash`
  - Flash with alternate programmer: `make OPENOCD_INTERFACE=interface/stlink-v2.cfg flash`

### Debugging

1. Start OpenOCD debug server: `make run-debug-server`
2. Connect GDB in TUI mode: `make run-debug-client`
  - Use alternate GDB: `make TARGET_GDB=some-other-gdb run-debug-client`

## Licenses

libopencm3 is licensed under LGPL v3.

All other code is licensed under CC0.
