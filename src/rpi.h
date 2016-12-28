//
// Created by saber on 2016/12/14.
//

#ifndef WIZNET_RPI_H
#define WIZNET_RPI_H

void bcm2835_initlize();

void   wizchip_cs_sel();
void   wizchip_cs_desel();
uint8_t wizchip_spi_readbyte(void);
void 	wizchip_spi_writebyte(uint8_t wb);
void 	wizchip_spi_readburst(uint8_t* pBuf, uint16_t len);
void 	wizchip_spi_writeburst(uint8_t* pBuf, uint16_t len);

#endif //WIZNET_RPI_H
