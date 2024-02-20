## What is Xinu?
Xinu stands for Xinu Is Not Unix -- although it shares concepts and even names with Unix, the internal design differs completely. Xinu is a small, elegant operating system that supports dynamic process creation, dynamic memory allocation, network communication, local and remote file systems, a shell, and device-independent I/O functions. The small size makes Xinu suitable for embedded environments.

## What is Xinu for STM32
Xinu for STM32 is a port of the ARM version of Xinu. The STM32 family of 32-bit microcontrollers is a popular SoC based on the Arm Cortex-M processor.
Besides porting the original version, Xinu for STM32 is extended with the following specific Cortex-M* features:

* Shadowed Stack Pointer:  Two stack pointers are available. The MSP is used
for the OS Kernel and interrupt handlers. The PSP is used by application
tasks.
* PendSV exception for scheduling: If Xinu decides that context switching is needed,
it sets the pending status of the PendSV, and delays the context-switching
request until all other IRQ handlers have completed their processing before 
carrying out the PendSV exception 


## Supported Peripherals (currently)
* [X] UART
* [X] GPIO
* [X] SPI

## Tested boards
1. STM32F103* - https://stm32-base.org/boards/STM32F103RCT6-STM32-Mini-V2.0
2. Qemu for STM32 - https://github.com/beckus/qemu_stm32

## How to build and run

### Requirements 
Xinu for STM32 uses simple Makefiles. The source code should be compiled with a cross compiler (i.e. GCC cross compiler for ARM Cortex-A/R/M processors). The following packages are required:

* gcc-arm-none-eabi 
* flex
* flex-dev
* bison
* gawk
* make
* libc-dev
* picocom
* stm32-flash)
(* qemu)

For a debian-like distribution: `apt-get install gcc-arm-none-eabi flex flex-dev bison gawk make libc-dev`

### Compiling locally
Make sure you have installed the above required packages.
```
cd compile
make
```

### Compiling with docker
This creates a very light container based on Alpine Linux:
```
docker build -t . xinu-container
docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp xinu-container sh -c 'cd compile && make'
```
If required you can use the container interactively: 
`docker run -it --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp xinu-container`

### Uploading firmware: built-in bootloader

Note: you will need a USB to UART device to set up communication between your PC and STM32 board. Any common chip will suffice. Pins are (RX1 - PA10, TX1 - PA9)

STM32Flash (https://sourceforge.net/projects/stm32flash) can be used for flashing the compiled code to the device's flash ROM. 

`stm32flash -w compile/xinu.bin -v /dev/ttyUSB0`

### Uploading firmware: JTAG, SWO (ST-Link)
Code layout is simple. You can just write directly at address 0x0. 

### Running
Xinu boots and shows a prompt. Output is over UART. Baudrate is at 115200. You can use a tool like *picocom* to communicate with your PC: `picocom -b 115200 /dev/ttyUSB0`

## Emulation
Use `make qemu` to run Xinu for STM32 in Qemu. Please note that this version of qemu should be manually build (see https://github.com/beckus/qemu_stm32)
Note: if you have installed *qemu-system-arm*, you will need to remove that package to avoid any conficts'

## Screenshots
![Screenshot](https://github.com/robinkrens/xinu-for-stm32/raw/master/screenshot.png "bootscreen")

More general information about Xinu can be found at https://xinu.cs.purdue.edu/

