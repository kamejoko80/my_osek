/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include <stdio.h>
#include "MKL46Z4.h"

#define size_t unsigned int

/**
 * @brief         UART0_PinConf
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0_PinConf(void)
{
	/* PTA1 : UART0_RX */
	PORTA->PCR[1] = 0x00000200UL;
	/* PTA2 : UART0_TX */
	PORTA->PCR[2] = 0x00000200UL;
}

/**
 * @brief         UART0_Init
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0_Init(void)
{
	char dummy;
	/* Enable clock gate UART0 */
    SIM->SCGC4 |=   1UL << 10;

	/* Choose MCGPLLCLK/2 (48MHz/2) */
    SIM->SOPT2 |=   1UL << 16;
	SIM->SOPT2 &= ~(1UL << 27);
	SIM->SOPT2 |=   1UL << 26;

    /* Baudrate = clock/(SBR[12:0] x (OSR + 1))   */
	/* OSR = 15, clock = 24MHz, baudrate = 115200 */
	/* -> SBR = 13 */
	/* LBKDIE = 0, RXEDGIE = 0, SBNS = 0 */
	UART0->BDH = 0x00;
	UART0->BDL = 0x0D;

	/* UART0 control */
	UART0->C1 = 0x00;
	UART0->C2 = 0x00;
	UART0->C3 = 0x00;
	UART0->C4 = 0x0F; /* OSR = 15 */
	UART0->C5 = 0x00;

	/* Enable UART0 transmit/receive */
	UART0->C2 |= 0x03 << 2;

	/* Dummy read to ensure UART0
	   receive buffer is empty already */
	dummy = UART0->D;
	dummy = dummy;
}

/**
 * @brief         UART0_PutChar
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART0_PutChar(char c)
{
	UART0->D   = c;
    /* Wait for transmition complete */
	while(!(UART0->S1 & (0x01 << 6))) {}
}

/**
 * @brief         UART0_GetChar
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
char UART0_GetChar(void)
{
	/* Wait for incomming character */
	while(!(UART0->S1 & (0x01 << 5))) {}
  return UART0->D;
}

int _read (int fd, const void *buf, size_t count)
{
  return 0;
}

int _write (int fd, const void *buf, size_t count)
{
  size_t CharCnt = 0x00;

  (void)fd;                            /* Parameter is not used, suppress unused argument warning */
   for (;count > 0x00; --count)
   {
     UART0_PutChar((unsigned char)*(uint8_t*)buf);
     (uint8_t*)buf++;
     CharCnt++;
   }
  return CharCnt; /* CORRECT */
}

int main(void)
{
  /* Update system clock */
  SystemCoreClockUpdate();
  /* Pinmux config */
  UART0_PinConf();
  /* Initialize UART0 */
  UART0_Init();

  printf("Hello frdm-lk25z\r\n");

  while(1)
  {

  }
}

/* Make compiler happy */
void exit (int status)
{

}
