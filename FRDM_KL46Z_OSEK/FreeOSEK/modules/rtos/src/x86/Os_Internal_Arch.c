/* Copyright 2008, 2009, 2014 Mariano Cerdeiro
 * Copyright 2014, Juan Cecconi
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

/** \brief FreeOSEK Os Internal Arch Implementation File
 **
 ** \file x86/Os_Internal_Arch.c
 ** \arch x86
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */


/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20090719 v0.1.3 MaCe rename file to Os_
 * 20090424 v0.1.2 MaCe use the right counter macros
 * 20090130 v0.1.1 MaCe change type uint8_least to uint8f
 * 20080713 v0.1.0 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint8 InterruptState;

uint32 OsekHWTimer0;

InterruptFlagsType InterruptFlag;

uint32* OSEK_InterruptFlags;

#ifdef CPUTYPE
#if ( CPUTYPE == ia64 )
uint64 OsStack;

uint64 OsekStack;
#elif ( CPUTYPE == ia32 )
uint32 OsStack;

uint32 OsekStack;
#else /* #if ( CPUTYPE == ia64 ) */
#error Unknown CPUTYPE for ARCH x86
#endif /* #if ( CPUTYPE == ia64 ) */
#else /* #ifdef CPUTYPE */
#error CPUTPYE is not defined
#endif /* #idef CPUTYPE */

/*==================[internal functions definition]==========================*/
/** \brief Check if at least one ISR has been set
 **
 ** \returns 1 if at least one isr has been triggered
 **          0 if no isr has been triggered
 **/
static uint8 OSEK_IsIsrWaiting(void)
{
   uint8 ret = 0;

   if (0 != OSEK_InterruptFlags[0])
   {
      ret = 1;
   }
   if (0 != OSEK_InterruptFlags[1])
   {
      ret = 1;
   }

   return ret;
}

/** \brief Returns the first Isr waiting to be executed
 **
 ** Returns the isr whith higher prio which has been triggered. Isr 0 has the
 ** highest priority and 63 the lowerst.
 **
 ** \returns a value between 0 and 63 representing the triggered isr
 **/
static uint8 OSEK_GetFirstIsr(void)
{
   uint32 mask;
   uint8 ret = 255;
   uint8 found = 0;
   uint8 offset;
   uint8 interrupt;

   /* TODO improve this code for speed, initial version was
    * implemented to avoid the dependency to circular buffer library */
   for(interrupt = 0; (0 == found) && (64 > interrupt); interrupt++)
   {
      if (32 > interrupt)
      {
         mask = 1 << interrupt;
         offset = 0;
      }
      else
      {
         mask = 1 << (interrupt-32);
         offset = 1;
      }

      if (OSEK_InterruptFlags[offset] & mask)
      {
         found = 1;
         ret = interrupt;

         /* reset interrupt flag */
         OSEK_InterruptFlags[offset] &= ~mask;
      }
   }

   return ret;
}

/*==================[external functions definition]==========================*/
void OSEK_ISR_HWTimer0(void)
{
#if (ALARMS_COUNT != 0)
   IncrementCounter(HardwareCounter, 1);
#endif /* #if (ALARMS_COUNT != 0) */
}

void OSEK_ISR_HWTimer1(void)
{
#if (defined HWCOUNTER1)
#if (ALARMS_COUNT != 0)
   IncrementCounter(HWCOUNTER1, 1);
#endif /* #if (ALARMS_COUNT != 0) */
#endif /* #if (defined HWCOUNTER1) */
}

void OsInterruptHandler(int signal)
{
   uint8 interrupt;

   if (SIGTERM == signal)
   {
      /* Terminate Child process */
      Os_Terminate_Flag = true;
      /* wait for the second thread to finish */
      pthread_join(Os_Thread_Timer, NULL);
      /* kill Main process */
      OsekKillSigHandler(0);
   }
   /* repeat until no more int flags are set */
   while( OSEK_IsIsrWaiting() )
   {
      /* read one interrupt */
      interrupt = OSEK_GetFirstIsr();

      /* only 0 .. 31 interrupts are allowed */
      if (INTERRUPTS_COUNT > interrupt)
      {
#if 0
         printf("Interrupt: %d\n",interrupt);
#endif
         if ( (InterruptState) &&
               ( (InterruptMask & (1 << interrupt ) )  == 0 ) )
         {
            InterruptTable[interrupt]();
         }
         else
         {
            InterruptFlag |= 1 << interrupt;
         }
      }
   }

}

void* HWTimerThread(void *pThread_Arg)
{
   struct timespec rqtp;
   uint8 interrupt;
   uint8 timer = (uint8) (intptr_t) pThread_Arg;

   if (timer <= 2)
   {
      /* intererupt every
       * 0 seconds and
       * 10 ms */
      rqtp.tv_sec=0;
      rqtp.tv_nsec=1000000;

      while(Os_Terminate_Flag == false)
      {
         /* sleep */
         nanosleep(&rqtp,NULL);

         /* the timer interrupt is the interrupt number 4 */
         interrupt = 4;

         /* add simulated interrupt to the interrupt queue */
         OSEK_InterruptFlags[0] |= 1 << interrupt;

         /* indicate interrupt using a signal */
         kill(getpid(), SIGALRM);
      }
   }
   return NULL;
}

void OsekKillSigHandler(int status)
{
   PreCallService();
   exit(0);
   PostCallService();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
