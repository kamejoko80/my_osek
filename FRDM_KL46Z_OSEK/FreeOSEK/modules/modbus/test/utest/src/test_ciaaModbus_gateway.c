/* Copyright 2015, Gustavo Muro
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

/** \brief This file implements the test of the modbus library
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Modbus CIAA Modbus
 ** @{ */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150825 v0.0.1 GMuro implement first tests
 */

/*==================[inclusions]=============================================*/
#include "unity.h"
#include "ciaaModbus_Cfg.h"
#include "ciaaModbus_gateway.h"
#include "mock_os.h"
#include "mock_ciaaModbus_transport.h"
#include "mock_ciaaModbus_slave.h"
#include "os.h"
#include "string.h"
#include "mock_ciaaPOSIX_string.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
static void * memset_stub(void * s, int c, size_t n, int cmock_num_calls)
{
   return memset(s, c, n);
}


static void ciaaModbus_transportRecvMsg_CALLBACK(int32_t handler,
      uint8_t* id, uint8_t* pdu, uint32_t* size, int cmock_num_calls)
{
   int32_t i;

   TEST_ASSERT_EQUAL(0, handler);

   *id = 2;

   for (i = 0 ; CIAAMODBUS_REQ_PDU_MINLENGTH > i ; i++)
   {
      pdu[i] = i & 0xff;
   }

   *size = CIAAMODBUS_REQ_PDU_MINLENGTH;
}

/*==================[external functions definition]==========================*/
/** \brief set Up function
 **
 ** This function is called before each test case is executed
 **
 **/
void setUp(void)
{
   /* ignore calls GetResource */
   GetResource_IgnoreAndReturn(E_OK);

   /* ignore calls ReleaseResource */
   ReleaseResource_IgnoreAndReturn(E_OK);

   /* set stub callback */
   ciaaPOSIX_memset_StubWithCallback(memset_stub);

   /* init gateway module */
   ciaaModbus_gatewayInit();
}

/** \brief tear Down function
 **
 ** This function is called after each test case is executed
 **
 **/
void tearDown(void)
{
}

void doNothing(void)
{
}

/** \brief Test ciaaModbus_gatewayAddTransport
 **
 **/
void test_ciaaModbus_gatewayAddTransport_01(void)
{
   int32_t hModbusGW;
   int32_t hModbusTransport = 0;
   int8_t ret;

   hModbusGW = ciaaModbus_gatewayOpen();

   ciaaModbus_transportGetType_ExpectAndReturn(hModbusTransport, CIAAMODBUS_TRANSPORT_TYPE_SLAVE);
   ciaaModbus_transportTask_Expect(hModbusTransport);
   ciaaModbus_transportRecvMsg_StubWithCallback(ciaaModbus_transportRecvMsg_CALLBACK);

   ret = ciaaModbus_gatewayAddTransport(hModbusGW, hModbusTransport);

   ciaaModbus_gatewayMainTask(hModbusGW);

   TEST_ASSERT_NOT_EQUAL(-1, hModbusGW);
   TEST_ASSERT_NOT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddTransport
 **
 **/
void test_ciaaModbus_gatewayAddTransport_02(void)
{
   int32_t hModbusGW;
   int32_t hModbusTransport = 0;
   int8_t ret;

   hModbusGW = ciaaModbus_gatewayOpen();

   ciaaModbus_transportGetType_ExpectAndReturn(hModbusTransport, CIAAMODBUS_TRANSPORT_TYPE_MASTER);
   ciaaModbus_transportRecvMsg_StubWithCallback(ciaaModbus_transportRecvMsg_CALLBACK);

   ret = ciaaModbus_gatewayAddTransport(hModbusGW, hModbusTransport);

   ciaaModbus_gatewayMainTask(hModbusGW);

   TEST_ASSERT_NOT_EQUAL(-1, hModbusGW);
   TEST_ASSERT_NOT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddTransport
 **
 **/
void test_ciaaModbus_gatewayAddTransport_03(void)
{
   int32_t hModbusGW;
   int32_t hModbusTransport = 0;
   int8_t ret;

   hModbusGW = ciaaModbus_gatewayOpen();

   ciaaModbus_transportGetType_ExpectAndReturn(hModbusTransport, CIAAMODBUS_TRANSPORT_TYPE_INVALID);

   ret = ciaaModbus_gatewayAddTransport(hModbusGW, hModbusTransport);

   TEST_ASSERT_NOT_EQUAL(-1, hModbusGW);
   TEST_ASSERT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddTransport
 **
 **/
void test_ciaaModbus_gatewayAddTransport_04(void)
{
   int32_t hModbusGW;
   int8_t ret;

   hModbusGW = ciaaModbus_gatewayOpen();

   ret = ciaaModbus_gatewayAddTransport(hModbusGW, -1);

   TEST_ASSERT_NOT_EQUAL(-1, hModbusGW);
   TEST_ASSERT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddTransport
 **
 **/
void test_ciaaModbus_gatewayAddTransport_05(void)
{
   int8_t ret;

   ret = ciaaModbus_gatewayAddTransport(-1, 0);

   TEST_ASSERT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddSlave
 **
 **/
void test_ciaaModbus_gatewayAddSlave_01(void)
{
   int32_t hModbusGW;
   int8_t ret;

   hModbusGW = ciaaModbus_gatewayOpen();

   ciaaModbus_slaveGetId_ExpectAndReturn(0x11223344, 2);

   ret = ciaaModbus_gatewayAddSlave(hModbusGW, 0x11223344);

   ciaaModbus_gatewayMainTask(hModbusGW);

   TEST_ASSERT_NOT_EQUAL(-1, hModbusGW);
   TEST_ASSERT_NOT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddSlave
 **
 **/
void test_ciaaModbus_gatewayAddSlave_02(void)
{
   int32_t hModbusGW;
   int8_t ret;

   hModbusGW = ciaaModbus_gatewayOpen();

   ret = ciaaModbus_gatewayAddSlave(hModbusGW, -1);

   ciaaModbus_gatewayMainTask(hModbusGW);

   TEST_ASSERT_NOT_EQUAL(-1, hModbusGW);
   TEST_ASSERT_EQUAL(-1, ret);
}

/** \brief Test ciaaModbus_gatewayAddSlave
 **
 **/
void test_ciaaModbus_gatewayAddSlave_03(void)
{
   int8_t ret;

   ret = ciaaModbus_gatewayAddSlave(-1, 0);

   TEST_ASSERT_EQUAL(-1, ret);
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

