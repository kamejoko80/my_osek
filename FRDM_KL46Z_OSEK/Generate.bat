rm -rf config/inc
rm -rf config/src
php FreeOSEK/modules/rtos/generator/generator.php --cmdline -l -v -DARCH=cortexM0 -DCPUTYPE=MKL46ZXXX -DCPU=MKL46ZXXX -c oil/config.oil -t FreeOSEK/modules/rtos/gen/inc/Os_Internal_Cfg.h.php FreeOSEK/modules/rtos/gen/src/Os_Internal_Cfg.c.php FreeOSEK/modules/rtos/gen/inc/Os_Cfg.h.php  FreeOSEK/modules/rtos/gen/src/Os_Cfg.c.php FreeOSEK/modules/rtos/gen/src/cortexM0/Os_Internal_Arch_Cfg.c.php FreeOSEK/modules/rtos/gen/inc/cortexM0/Os_Internal_Arch_Cfg.h.php -o config
