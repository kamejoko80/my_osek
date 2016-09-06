# FreeOSEK STM32F4

FreeOSEK implementation for STM32F4 Discovery

Build instruction

1> Download EmBlocks IDE as bellow link :
    
   http://www.emblocks.org/web/

2> Use PHP with windows 7 (64 bit):

   - Unzip php-5.6.20-nts-Win32-VC11-x64.zip 
   - Create new folder C:\php and copy all decompressed files to this folder.
   - Add C:\php into PATH environment variable.
   - Install vc_redist.x64.exe if we can't run command php -v

3> Open project with Emblocks IDE, press F7 to build source files.

Uart Debug Connection:

PA2 (UART2_RX) <--> RS232 TX
PA3 (UART2_TX) <--> RS232 RX

Normaly OSEK oil generator is disabled to enable :

From Menu -> Project -> Build options -> Pre/post build steps -> change dropdown box to enable.
(This tep is need only onetime right after changing config.oil file)


