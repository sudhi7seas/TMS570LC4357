/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"
#include "HL_system.h"

/* USER CODE BEGIN (1) */
#include "HL_i2c.h"

/* It defines the own address (own_add) as 0x20 and the slave address (slv_add) as 0x10*/

#define own_add 0x20
#define slv_add 0x10

/* The bsize constant is set to 16, which is the size of the TX_PACK and RX_PACK arrays */
#define bsize    16

/* The TX_PACK array is initialized with the string "HERCULESMICRO-TI" */
uint8  TX_PACK[bsize]={'H','E','R','C','U','L','E','S','M','I','C','R','O','-','T','I'};
uint8  RX_PACK[bsize]={0};
uint32 data;

/* The i2cEnableLoopback function is declared, which will be used to enable the I2C loop back mode */
void i2cEnableLoopback(i2cBASE_t *i2c);
/* USER CODE END */


/** @fn void main(void)
*   @brief Application main function
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */


void main(void)
{
/* USER CODE BEGIN (3) */
    uint32 i;

    /* The buf_size variable is set to bsize (16) */
    uint32 buf_size = bsize;

    /* Pointers t_buff and r_buff are created to point to the beginning of the TX_PACK and RX_PACK arrays, respectively */
    uint8  *t_buff = &TX_PACK[0];
    uint8  *r_buff = &RX_PACK[0];

    /* i2c initialization         */
    i2cInit();

    /* set i2c own address        */
    i2cSetOwnAdd(i2cREG1,own_add);

    /* enable internal loopback   */
    i2cEnableLoopback(i2cREG1);

    /* Initiate Start condition for Transmission  */
    i2cSetStart(i2cREG1);

    /* send data packets          */
    while(buf_size--)
    {
       i2cSendByte(i2cREG1,*t_buff++);
       /* receive data packets    */
       *r_buff++ = i2cReceiveByte(i2cREG1);
    }

    /* Delay to wait for all bytes to be received. */
    for(i=0;i<1000000;i++);

    /* Clear Stop Condition detect flag  */
    i2cClearSCD(i2cREG1);

    /* wait for ever  */
    while(1);

 /* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
