# FreeOSEK FRDM-KL46Z

Build instruction :

1> Download EmBlocks IDE as bellow link :
    
   http://www.emblocks.org/web/

2> Download and install Jlink software package as the following link:

   https://www.segger.com/opensda.html
   
3> Flash Jlink Firmware into OpenSDA debugger:

   - Press reset button
   - Connect OpenSDA with PC by USB cable.   
   - Drap and Drop JLink_OpenSDA_V2_1_2015-10-13.bin into the USB drive

4> Use PHP with windows 7 64 bits (need for OIL generator) :

   - Unzip php-5.6.20-nts-Win32-VC11-x64.zip
   - Create new folder C:\php and copy all decompressed files to this folder.
   - Add C:\php into PATH environment variable.
   - Install vc_redist.x64.exe if we can't run command php -v
   
5> Open project with Emblocks IDE, press F7 to build source files and start debugger.

 