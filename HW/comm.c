/*
 * comm.c
 *
 *  Created on: 28. mai 2017
 *      Author: Joonatan
 */

/* This file handles communication over the UART interface.
 * Unfortunately driverlib already has a source file named uart.c */

#include "comm.h"
#include "parser.h"
#include <uart.h>


Private U8 priv_receive_buffer[UART_BUF_LEN];
Private U8 priv_receive_cnt;
Private U8 priv_receive_flag = 0;


Public void comm_send_char(char c)
{
    UART_transmitData(EUSCI_A0_BASE, c);

    //So should we also wait until data has been sent out???
    //We should not send any chars out if UART is busy.
}

Public void comm_send_str(const char * str)
{
    const char * ps = str;
    while(*ps)
    {
        comm_send_char(*ps);
        ps++;
    }
}


Public void comm_send_number(long nr)
{
    U32 len = long2string(nr, sY);
    sY[len] = 0;
    comm_send_str(sY);
}

Public void comm_send_rn(void)
{
    comm_send_char('\r');
    comm_send_char('\n');
}

/* EUSCI A0 UART ISR */
/* Handles incoming data over the UART.*/
Public void EUSCIA0_IRQHandler(void)
{
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A0_BASE);
    U8 c;

    UART_clearInterruptFlag(EUSCI_A0_BASE, status);

    if (status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        //MAP_UART_transmitData(EUSCI_A0_BASE, MAP_UART_receiveData(EUSCI_A0_BASE));
        c = UART_receiveData(EUSCI_A0_BASE);

        if ((priv_receive_cnt < UART_BUF_LEN) && (priv_receive_flag == 0u))
        {
            priv_receive_buffer[priv_receive_cnt] = c;
            priv_receive_cnt++;

            if (c == '\n')
            {
                //We got new data that needs to be processed.
                priv_receive_flag = 1u;
            }
        }
        else
        {
            //Silently discard data to prevent buffer overflow.
        }
    }
}


Public U8 comm_receiveData(U8 * dest)
{
    //Return length of received data. If none received then return 0.
    U8 res = 0u;

    if (priv_receive_flag)
    {
        res = priv_receive_cnt;
        (void)memcpy(dest, priv_receive_buffer, priv_receive_cnt);
        priv_receive_cnt = 0u;
        priv_receive_flag = 0u;
    }

    return res;
}

