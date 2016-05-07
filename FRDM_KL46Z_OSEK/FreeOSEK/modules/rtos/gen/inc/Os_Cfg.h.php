/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2008, 2009, 2015 Mariano Cerdeiro
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

<?php
/** \brief FreeOSEK File to be Generated
 **
 ** \file Os_Cfg.h.php
 **
 **/
?>

#ifndef _OS_CFG_H_
#define _OS_CFG_H_
/** \brief FreeOSEK Os Generated Configuration Header File
 **
 ** This file contents the generated configuration of FreeOSEK Os
 **
 ** \file Os_Cfg.h
 **
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Global
 ** @{ */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150619 v0.1.4 MaCe fix issue #279
 * 20090719 v0.1.3 MaCe rename file to Os_
 * 20090424 v0.1.2 MaCe add counters defines
 * 20090128 v0.1.1 MaCe add MEMMAP off configuration
 * 20080810 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/
/** \brief Definition of the  DeclareTask Macro */
#define DeclareTask(name) void OSEK_TASK_ ## name (void)

#define OSEK_OS_INTERRUPT_MASK ((InterruptFlagsType)0xFFFFFFFFU)

<?php
/* Definitions of Tasks */
$tasks = getLocalList("/OSEK", "TASK");
$remote_tasks = getRemoteList("/OSEK", "TASK");

$count = 0;
foreach ($tasks as $task)
{
   print "/** \brief Task Definition */\n";
   print "#define $task $count\n";
   $count++;
}
print "\n";

if (count($remote_tasks) > 0)
{
   foreach ($remote_tasks as $task)
   {
      print "/** \brief Remote Task Definition */\n";
      print "#define $task $count\n";
      $count++;
   }
   print "\n";
}

/* Define the Applications Modes */
$appmodes = $config->getList("/OSEK","APPMODE");

foreach ($appmodes as $count=>$appmode)
{
   print "/** \brief Definition of the Application Mode $appmode */\n";
   print "#define " . $appmode . " " . $count . "\n";
}
print "\n";

/* Define the Events */
$events = $config->getList("/OSEK","EVENT");

foreach ($events as $count=>$event)
{
   print "/** \brief Definition of the Event $event */\n";
   print "#define " . $event . " 0x" . sprintf ("%xU", (1<<$count)) . "\n";
}
print "\n";

/* Define the Resources */
$resources = $config->getList("/OSEK","RESOURCE");

foreach ($resources as $count=>$resource)
{
   print "/** \brief Definition of the resource $resource */\n";
   print "#define " . $resource . " ((ResourceType)" . $count . ")\n";
}
print "\n";

/* Define the Alarms */
$alarms = getLocalList("/OSEK", "ALARM");

foreach ($alarms as $count=>$alarm)
{
   print "/** \brief Definition of the Alarm $alarm */\n";
   print "#define " . $alarm . " " . $count . "\n";
}
print "\n";

/* Define the Counters */
$counters = getLocalList("/OSEK", "COUNTER");

foreach ($counters as $count=>$counter)
{
   print "/** \brief Definition of the Counter $counter */\n";
   print "#define " . $counter . " " . $count . "\n";
}
print "\n";

$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
?>
/** \brief OS Error Get Service Id */
/* \req OSEK_ERR_0.1 The macro OSErrorGetServiceId() shall provide the service
 * identifier with a OSServiceIdType type where the error has been risen
 * \req OSEK_ERR_0.1.1 Possibly return values are: OSServiceId_xxxx, where
 * xxxx is the name of the system service
 */
#define OSErrorGetServiceId() (Osek_ErrorApi)

#define OSErrorGetParam1() (Osek_ErrorParam1)

#define OSErrorGetParam2() (Osek_ErrorParam2)

#define OSErrorGetParam3() (Osek_ErrorParam3)

#define OSErrorGetRet() (Osek_ErrorRet)

<?php
}

$memmap = $config->getValue("/OSEK/" . $os[0],"MEMMAP");
print "/** \brief OSEK_MEMMAP macro (OSEK_DISABLE not MemMap is used for FreeOSEK, OSEK_ENABLE\n ** MemMap is used for FreeOSEK) */\n";
if ($memmap == "TRUE")
{
   print "#define OSEK_MEMMAP OSEK_ENABLE\n";
}
elseif ($memmap == "FALSE")
{
   print "#define OSEK_MEMMAP OSEK_DISABLE\n";
}
else
{
   $this->log->warning("MEMMAP configuration not found in FreeOSEK configuration, disabling as default");
   print "#define OSEK_MEMMAP OSEK_DISABLE\n";
}

$osattr = $config->getValue("/OSEK/" . $os[0],"STATUS");
if ($osattr == "EXTENDED") : ?>
/** \brief Schedule this Task if higher priority Task are Active
 **
 ** \remarks if the system is configured with extended errors the
 **          function Schedule is implemented as a macro and calls the
 **          internal function Schedule_Int. If Standard errores are
 **          configured the function Schedule is implemented as a function.
 **
 ** This API shall Schedule the calling Task if a higher priority Task
 ** is active. This API shall only be used from non preemtive tasks.
 **
 ** \return E_OK if no error
 ** \return E_OS_CALLEVEL if call at interrupt level
 ** \return E_OS_RESOURCE if the calling task occupies resources
 **/
#define Schedule() Schedule_Int(TRUE)
<?php
   endif;
?>

/*==================[typedef]================================================*/
/** \brief Type definition of StatusType
 **
 ** This type is used to represent the status returned by all FreeOSEK APIs
 **/
/* \req OSEK_SYS_1.1 */
typedef unsigned char StatusType;


/*==================[external data declaration]==============================*/
<?php
$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
?>
/** \brief Error Api Variable
 **
 ** This variable contents the api which generate the last error
 **/
extern unsigned int Osek_ErrorApi;

/** \brief Error Param1 Variable
 **
 ** This variable contents the first parameter passed to the api which has
 ** generted the last error.
 **/
extern unsigned int Osek_ErrorParam1;

/** \brief Error Param2 Variable
 **
 ** This variable contents the second parameter passed to the api which has
 ** generted the last error.
 **/
extern unsigned int Osek_ErrorParam2;

/** \brief Error Param3 Variable
 **
 ** This variable contents the third parameter passed to the api which has
 ** generted the last error.
 **/
extern unsigned int Osek_ErrorParam3;

/** \brief Error Return Variable
 **
 ** This variable contents return value of the api which has generated
 ** the last error.
 **/
extern unsigned int Osek_ErrorRet;

<?php
}
?>

/*==================[external functions declaration]=========================*/
<?php
$pretaskhook=$config->getValue("/OSEK/" . $os[0],"PRETASKHOOK");
if ($pretaskhook == "TRUE")
{
   print "/** \brief Pre Task Hook */\n";
   print "extern void PreTaskHook(void);\n\n";
}
$posttaskhook=$config->getValue("/OSEK/" . $os[0],"POSTTASKHOOK");
if ($posttaskhook == "TRUE")
{
   print "/** \brief Post Task Hook */\n";
   print "extern void PostTaskHook(void);\n\n";
}
$shutdownhook=$config->getValue("/OSEK/" . $os[0],"SHUTDOWNHOOK");
if ($shutdownhook == "TRUE")
{
   print "/** \brief Shutdown Hook */\n";
   print "extern void ShutdownHook(void);\n\n";
}
$startuphook=$config->getValue("/OSEK/" . $os[0],"STARTUPHOOK");
if ($startuphook == "TRUE")
{
   print "/** \brief Startup Hook */\n";
   print "extern void StartupHook(void);\n\n";
}
$errorhook=$config->getValue("/OSEK/" . $os[0],"ERRORHOOK");
if ($errorhook == "TRUE")
{
   print "/** \brief Error Hook */\n";
   print "extern void ErrorHook(void);\n\n";
}

/* Declare Tasks */

foreach ($tasks as $count=>$task)
{
   print "/** \brief Task Declaration of Task $task */\n";
   print "DeclareTask($task);\n";
}
print "\n";

$intnames = getLocalList("/OSEK", "ISR");

foreach ($intnames as $count=>$int)
{
   print "/** \brief ISR Declaration */\n";
   print "extern void OSEK_ISR_$int(void); /* Interrupt Handler $int */\n";
}
print "\n";

$alarms = getLocalList("/OSEK", "ALARM");

foreach ($alarms as $count=>$alarm)
{
   $action = $config->getValue("/OSEK/" . $alarm, "ACTION");
   if ($action == "ALARMCALLBACK")
   {
      print "/** \brief Alarm Callback declaration */\n";
      print "extern void OSEK_CALLBACK_" . $config->getValue("/OSEK/" . $alarm . "/ALARMCALLBACK", "ALARMCALLBACKNAME") . "(void);\n";
   }
}
print "\n";

$osattr = $config->getValue("/OSEK/" . $os[0],"STATUS"); ?>
/** \brief Schedule this Task if higher priority Task are Active
 **
 ** This API shall Schedule the calling Task if a higher priority Task
 ** is active. This API shall only be used from non preemtive tasks.
 **
 ** \remarks This interface may be used by the end user over the
 **          macro Schedule or from the system itself. Therefore
 **          the parameter PerformChecks is provided. When
 **          the user calls the scheduler the checks shall be
 **          performed if the error checking is set as extended.
 **          If the system calls the Schedule no error checking
 **          shall be performed, the system shall be trusted.
 **
 ** \param[in] PerformChecks indicates if the function shall or not
 **                          perform the extended checks. This parameter
 **                          is only available if the error checks are set
 **                          to extended.
 ** \return E_OK if no error
 ** \return E_OS_CALLEVEL if call at interrupt level
 ** \return E_OS_RESOURCE if the calling task occupies resources
 **/
<?php if ($osattr == "EXTENDED") : ?>
extern StatusType Schedule_Int(boolean PerformChecks);
<?php elseif ($osattr == "STANDARD") : ?>
extern StatusType Schedule(void);
<?php endif; ?>

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_CFG_H_ */

