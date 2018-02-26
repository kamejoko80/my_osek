-------------------------------------------------------------------------------------------
HOW TO DOWNLOAD M4 FIRMWARE AND RUN THE PROGRAM ON LINUX
-------------------------------------------------------------------------------------------

1> Write udoobuntu-udoo-neo-minimal_2.0rc2 into SD card.
   Note: If we've copied udoobuntu-udoo-neo-minimal_2.0rc2 into SD card already, we can restore u-boot bootcmd as bellow step:
   => setenv bootcmd 'mmc dev ${mmcdev}; if mmc rescan; then if run loadbootscript; then run bootscript; fi; udooinit; run m4boot; if run loadimage; then run mmcboot; else run netboot; fi; else run netboot; fi'

2> Power on the board and open Linux console.
3> Copy m4fwloader.c into Linux and build the program as bellow command:
   $ gcc -o m4fwloader m4fwloader.c

4> How to load M4 firmware and boot :
   - From Windows convert Cortex_M4.elf to Cortex_M4.bin.
   - Copy Cortex_M4.bin into UDOO-NEO Linux. (ex. copy to folder /boot/)
   - From Linux console run the following commands to load and start M4 program :

     A> To load M4 firmware
        $ sudo ./m4fwloader /boot/Cortex_M4.bin 0x007F8000 --verbose

     B> To start M4 core
        $ sudo ./m4fwloader start

     B> To stop M4 core
        $ sudo ./m4fwloader stop

-------------------------------------------------------------------------------------------
HOW TO LAUNCH M4 FIRMWARE ON LINUX STARTUP
-------------------------------------------------------------------------------------------

1> Copy m4fwloader into system folder
        $ sudo chmod 777 m4fwloader
        $ sudo cp m4fwloader /usr/sbin/
        
2> Create the startup script "startM4.sh" in /etc/init.d folder as below:

        $ cd /etc/init.d
        $ sudo nano startM4.sh
        
        The above command opens nano editor and creates a script file with name is "startM4.sh" 
        Write the content of the script as below: 

        #! /bin/sh
        /usr/sbin/m4fwloader /boot/Cortex_M4.bin 0x007F8000 --verbose
        /usr/sbin/m4fwloader start
        
        Then press CTR+O to save the script, CTR+X to close the nano editor.
        Then register this script into Linux system startup:
        
        $ sudo chmod 777 startM4.sh
        $ sudo update-rc.d startM4.sh defaults 60

        Linux will print out the register result:

        update-rc.d: warning: /etc/init.d/startM4.sh missing LSB information
        update-rc.d: see <http://wiki.debian.org/LSBInitScripts>
        Adding system startup for /etc/init.d/startM4.sh ...
        /etc/rc0.d/K60startM4.sh -> ../init.d/startM4.sh
        /etc/rc1.d/K60startM4.sh -> ../init.d/startM4.sh
        /etc/rc6.d/K60startM4.sh -> ../init.d/startM4.sh
        /etc/rc2.d/S60startM4.sh -> ../init.d/startM4.sh
        /etc/rc3.d/S60startM4.sh -> ../init.d/startM4.sh
        /etc/rc4.d/S60startM4.sh -> ../init.d/startM4.sh
        /etc/rc5.d/S60startM4.sh -> ../init.d/startM4.sh
        
        => Congratulation ! You've already installed auto start script on Linux booting up.
        Reset the UDOO-NEO to see how M4 runs on Linux startup.
