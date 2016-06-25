# UDOO-NEO Core M4 BARE METAL PROJECT

Build instruction :

1> Download EmBlocks IDE as bellow link :
    
   http://www.emblocks.org/web/

2> Download and install Jlink software package as the following link:

   https://www.segger.com/jlink-software.html?step=1&file=JLink_510g
   
3> Download the following Linux image from UDOO web site
   
   - udoobuntu-udoo-neo-minimal_2.0rc2.zip
   - Run program Win32DiskImager.exe to copy Linux image into SD card.
      
4> Core M4 must be enabled by core A9, so we boot Linux before starting debugger with M4.   

5> Connect UART debug port with PC as bellow :

   J4_0 (UART5_RX) <--> RS232 TX

   J4_1 (UART5_TX) <--> RS232 RX

5> Open project with Emblocks IDE, press F7 to build source files and start debugger.

 