#include "HL_sys_common.h"
#include "HL_system.h"

/* USER CODE BEGIN (1) */
#include "HL_esm.h"
#include "HL_i2c.h"
#include "HL_sys_core.h"

#define own_add 0x20
#define slv_add 0x10
#define bsize    16

uint8  TX_PACK[bsize]={'H','E','R','C','U','L','E','S','M','I','C','R','O','-','T','I'};
uint8  RX_PACK[bsize]={0};
uint32 data;

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

    uint32 i,buf_size = bsize;
    uint8  *t_buff = &TX_PACK[0];
    uint8  *r_buff = &RX_PACK[0];

    /* Enable CPU Interrupts - FIQ & IRQ */
    _enable_interrupt_();

    /* i2c initialization         */
    i2cInit();

    /* set i2c own address        */
    i2cSetOwnAdd(i2cREG1,own_add);

    /* enable internal loopback   */
    i2cEnableLoopback(i2cREG1);

    /* Initiate Receive data length & destination ptr */
    i2cReceive(i2cREG1, 16, r_buff);

    /* Initiate Start condition for Transmission  */
    i2cSetStart(i2cREG1);

    /* send data packets          */
    while(buf_size)
    {
       i2cSendByte(i2cREG1,*t_buff);
       t_buff++;
       buf_size--;
    }

    /* Delay to wait for all bytes to be received. */
    for(i=0;i<1000000;i++);

    /* Clear Stop Condition detect flag  */
    i2cClearSCD(i2cREG1);

    /* Disable RX ready Interrupt  */
    i2cDisableNotification(i2cREG1, I2C_RX_INT);

    /* wait for ever  */
    while(1);

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
