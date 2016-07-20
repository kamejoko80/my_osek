README !

This project is used for initial developement firmware for M4 core based on i.MX6SX UDOO NEO
development kit. Please flash Linux image into SD card, boot up Linux before starting debugger unless
we can't connect JTAG with M4.

This source code is based on FreeRTOS_BSP_1.0.0_iMX6SX from NXP, only platform specific code is kept,
FreeRTOS source code is removed out of the source tree.

Setting up environment, the following software packages are required :

Jlink software package version : JLink V5.12d or later.
UDOO Linux Image               : udoobuntu-udoo-neo-minimal_2.0rc2.zip
PHP CLI for Windows            : php-5.6.20-nts-Win32-VC11-x64.zip
EmBitz IDE                     : EmBitz 0.42

Uart Debug Connection:

J4_0 (UART5_RX) <--> RS232 TX
J4_1 (UART5_TX) <--> RS232 RX

Normaly OSEK oil generator is disabled to enable :

From Menu -> Project -> Build options -> Pre/post build steps -> change dropdown box to enable.
(This tep is need only onetime right after changing config.oil file)


