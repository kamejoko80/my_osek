/* ----------------------------------------------------------------------
 * Copyright (C) 2013 ARM Limited. All rights reserved.
 *
 * $Date:        26. August 2013
 * $Revision:    V1.01
 *
 * Project:      GPIO Driver for ST STM32F10x
 * -------------------------------------------------------------------- */

#include "GPIO_STM32F10x.h"

/* History:
 *  Version 1.01
 *    GPIO_PortClock and GPIO_PinConfigure functions rewritten
 *    GPIO_STM32F1xx header file cleaned up and simplified
 *    GPIO_AFConfigure function and accompanying definitions added
 *  Version 1.00
 *    Initial release
 */

/**
  \fn          void GPIO_PortClock (GPIO_TypeDef *GPIOx, bool en)
  \brief       Port Clock Control
  \param[in]   GPIOx  Pointer to GPIO peripheral
  \param[in]   enable Enable or disable clock
*/
void GPIO_PortClock (GPIO_TypeDef *GPIOx, bool enable) {

  if (enable) {
    if      (GPIOx == GPIOA) RCC->APB2ENR |=  (1UL << 2);
    else if (GPIOx == GPIOB) RCC->APB2ENR |=  (1UL << 3);
    else if (GPIOx == GPIOC) RCC->APB2ENR |=  (1UL << 4);
    else if (GPIOx == GPIOD) RCC->APB2ENR |=  (1UL << 5);
    else if (GPIOx == GPIOE) RCC->APB2ENR |=  (1UL << 6);
    else if (GPIOx == GPIOF) RCC->APB2ENR |=  (1UL << 7);
    else if (GPIOx == GPIOG) RCC->APB2ENR |=  (1UL << 8);
  } else {
    if      (GPIOx == GPIOA) RCC->APB2ENR &= ~(1UL << 2);
    else if (GPIOx == GPIOB) RCC->APB2ENR &= ~(1UL << 3);
    else if (GPIOx == GPIOC) RCC->APB2ENR &= ~(1UL << 4);
    else if (GPIOx == GPIOD) RCC->APB2ENR &= ~(1UL << 5);
    else if (GPIOx == GPIOE) RCC->APB2ENR &= ~(1UL << 6);
    else if (GPIOx == GPIOF) RCC->APB2ENR &= ~(1UL << 7);
    else if (GPIOx == GPIOG) RCC->APB2ENR &= ~(1UL << 8);
  }
}


/**
  \fn          bool GPIO_PinConfigure (GPIO_TypeDef      *GPIOx,
                                       uint32_t           num,
                                       GPIO_CONF          conf,
                                       GPIO_MODE          mode)
  \brief       Configure port pin
  \param[in]   GPIOx         Pointer to GPIO peripheral
  \param[in]   num           Port pin number
  \param[in]   mode          \ref GPIO_MODE
  \param[in]   conf          \ref GPIO_CONF
  \return      true  - success
               false - error
*/
bool GPIO_PinConfigure(GPIO_TypeDef *GPIOx, uint32_t num, GPIO_CONF conf,
                                                          GPIO_MODE mode) {
  __IO uint32_t *reg;
  if (num > 15) return false;

  if (mode == GPIO_MODE_INPUT) {
    if      (conf == GPIO_IN_PULL_DOWN) {
      /* Enable pull down on selected input */
      GPIOx->ODR &= ~(1 << num);
    }
    else if (conf == GPIO_IN_PULL_UP) {
      /* Enable pull up on selected input */
      conf &= ~1;
      GPIOx->ODR |=  (1 << num);
    }
  }

  if (num < 8) {
    reg = &GPIOx->CRL;
  }
  else {
    num -= 8;
    reg = &GPIOx->CRH;
  }
  *reg &= ~(0xF << (num << 2));
  *reg |= ((conf << 2) | mode) << (num << 2);
  return true;
}


/**
  \fn          void GPIO_AFConfigure (AFIO_REMAP af_type)
  \brief       Configure alternate functions
  \param[in]   af_type Alternate function remap type
*/
void GPIO_AFConfigure (AFIO_REMAP af_type) {
  __IO uint32_t *reg;
       uint32_t  msk, val;

  if (af_type != AFIO_UNAVAILABLE_REMAP) {
    if (!(RCC->APB2ENR & RCC_APB2ENR_AFIOEN)) {
      /* Enable AFIO peripheral clock */
      RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    }
    if (af_type & (1 << 12)) {
      /* AF remap and debug I/O config register 2 */
      reg = &AFIO->MAPR2;
    }
    else {
      /* AF remap and debug I/O config register */
      reg = &AFIO->MAPR;
    }
    msk = (af_type >> 5) & 0x07;
    val = (af_type >> 8) & 0x0F;
    *reg &= ~(msk << (af_type & 0x1F));
    *reg |=  (val << (af_type & 0x1F));
  }
}
