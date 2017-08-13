/*
 * spi.c
 *
 *  Created on: Aug 13, 2017
 *      Author: Joonatan
 */

#include <driverlib.h>
#include <spi_drv.h>

/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
        12000000,                                   // SMCLK = DCO = 12MHZ
        10000,                                    // SPICLK = 10khz
        EUSCI_B_SPI_MSB_FIRST,                     // MSB First
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
        EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};


Public void spi_init(void)
{
    /* Selecting P1.5 and P1.6 in SPI mode */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN5 | GPIO_PIN6 , GPIO_PRIMARY_MODULE_FUNCTION);

    // Set pin 4.3 as CS pin.
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);

    /* We should give a falling edge to CS pin, not entirely sure if this is necessary. */
    /* Possibly we might have to catch the transmit interrupt and then control CS??? Not yet sure how this works. */
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);

    /* Configuring SPI in 3wire master mode */
    SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);

    /* Enable SPI module */
    SPI_enableModule(EUSCI_B0_BASE);

    /* Enabling interrupts */
    /*SPI_enableInterrupt(EUSCI_B0_BASE, EUSCI_B_SPI_RECEIVE_INTERRUPT);*/
    /*Interrupt_enableInterrupt(INT_EUSCIB0);*/
    /*Interrupt_enableSleepOnIsrExit();*/
}

Public void spi_transmit(U8 * data, U16 data_len)
{
    U8 * data_ptr = data;

    while (data_len > 0)
    {
        spi_transmit_byte(*data_ptr);
        data_ptr++;
        data_len--;
    }
}


Public void spi_transmit_byte(U8 byte)
{
    uint32_t jj;

    /* Polling to see if the TX buffer is ready */
    while (!(SPI_getInterruptStatus(EUSCI_B0_BASE,EUSCI_B_SPI_TRANSMIT_INTERRUPT)));
    /* Transmitting data to slave */
    SPI_transmitData(EUSCI_B0_BASE, byte);

    /* Delay between transmissions for slave to process information */
    for(jj=50;jj<50;jj++);
}



