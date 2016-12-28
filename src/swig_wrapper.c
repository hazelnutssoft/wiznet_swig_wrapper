//
// Created by saber on 2016/12/14.
//

#include "rpi.h"
#include "wizchip_conf.h"
#include "commons.h"
//common methods
int32_t init_hardware(){
    bcm2835_initlize();
    reg_wizchip_cs_cbfunc(wizchip_cs_sel, wizchip_cs_desel);
    reg_wizchip_spi_cbfunc(wizchip_spi_readbyte, wizchip_spi_writebyte);
    reg_wizchip_spiburst_cbfunc(wizchip_spi_readburst, wizchip_spi_writeburst);
}

int32_t init_conf(const char *ip, const char *mask, const char *gateway){
    wiz_NetInfo mWIZNETINFO= {.mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},
        .ip = {192, 168, 1, 199},
        .sn = {255, 255, 255, 0},
        .gw = {192, 168, 1, 1},
        .dns = {8, 8, 8, 8},
        .dhcp = NETINFO_STATIC };;

    if(WIZNET_ERROR == str_to_netarray(mWIZNETINFO.ip,4,ip))
    {
        return WIZNET_ERROR;
    }
    if(WIZNET_ERROR == str_to_netarray(mWIZNETINFO.sn,4,mask))
    {
        return WIZNET_ERROR;
    }
    if(WIZNET_ERROR == str_to_netarray(mWIZNETINFO.gw,4,gateway))
    {
        return WIZNET_ERROR;
    }
    ctlnetwork(CN_SET_NETINFO, (void *)&mWIZNETINFO);
#ifdef _WIZNET_DEBUG_
    cltnetwork(CN_GET_NETINFO, (void *)&mWIZNETINFO);
    printf("mac: 0x%02X-0x%02X-0x%02X-0x%02X-0x%02X-0x%02X\n",
           mWIZNETINFO.mac[0], mWIZNETINFO.mac[1], mWIZNETINFO.mac[2], mWIZNETINFO.mac[3], mWIZNETINFO.mac[4], mWIZNETINFO.mac[5]);
    printf("ip: %d.%d.%d.%d\n", mWIZNETINFO.ip[0],mWIZNETINFO.ip[1],mWIZNETINFO.ip[2],mWIZNETINFO.ip[3]);
    printf("sn: %d.%d.%d.%d\n", mWIZNETINFO.sn[0],mWIZNETINFO.sn[1],mWIZNETINFO.sn[2],mWIZNETINFO.sn[3]);
    printf("gw: %d.%d.%d.%d\n", mWIZNETINFO.gw[0],mWIZNETINFO.gw[1],mWIZNETINFO.gw[2],mWIZNETINFO.gw[3]);
#endif
}

uint16_t get_recved_size(uint8_t sn){
    uint16_t size = 0;
    if(SOCK_ESTABLISHED == getSn_SR(sn)){
        if(getSn_IR(sn) & Sn_IR_CON) {
            if((size = getSn_RX_RSR(sn)) < 0){
                size = 0;
            }
        }
    }
    if(SOCK_UDP == getSn_SR(sn)){
        if((size = getSn_RX_RSR(sn)) < 0){
            size = 0;
        }
    }
    return size;
}

void socket_recv(uint8_t sn, char *buf, size_t *buf_size){
    if(SOCK_ESTABLISHED == getSn_SR(sn)){
        if(getSn_IR(sn) & Sn_IR_CON) {
            recv(sn, buf, *buf_size);
        }
    }
}

void socket_recvfrom(uint8_t sn, char *buf, size_t *buf_size) {
    uint8_t destip[4];
    uint16_t destport;
    if (SOCK_UDP == getSn_SR(sn)) {
        ret = recvfrom(sn, buf, size, destip, (uint16_t*)&dst_port);
    }
}

void socket_send(uint8_t sn, const char *buf, const size_t buf_size){
    if(SOCK_ESTABLISHED == getSn_SR(sn)){
        if(getSn_IR(sn) & Sn_IR_CON) {
            send(sn, buf, buf_size);
        }
    }

}

void socket_sendto(uint8_t sn, const char *dst_ip, const uint16_t dst_port,const char *buf,const size_t buf_size){
    if (SOCK_UDP == getSn_SR(sn)) {
        sendto(sn, buf, buf_size, dst_ip, dst_port);
    }
}

int32_t socket_disconnect(uint8_t sn){
    int32_t ret;
    if(SOCK_ESTABLISHED == getSn_SR(sn) || SOCK_CLOSE_WAIT == getSn_SR(sn)) {
        if((ret=disconnect(sn)) != SOCK_OK) return ret;
    }
    return 1;
}
//tcp server methods
int32_t tcp_listen(uint8_t sn){
    if(SOCK_INIT == getSn_SR(sn)) {
        if( (ret = listen(sn)) != SOCK_OK) return ret;
    }
    return 1;
}

int32_t setup_tcp(uint8_t sn, uint16_t port){
    if(SOCK_CLOSED == getSn_SR(sn)){
        if((ret = socket(sn, Sn_MR_TCP, port, 0x00)) != sn)
            return ret;
    }
    return 1;
}

//tcp client methods
int32_t tcp_client_connect(uint8_t sn, const char *dstip_str, const uint16_t dstPort){
    uint8_t destip[4];
    str_to_netarray(dstip,4,dstip_str);
    if(SOCK_INIT == getSn_SR(sn)) {
        if ((ret = connect(sn, destip, destport)) != SOCK_OK) return ret;
    }
    return 1;
}

//udp methods
int32_t setup_udp(uint8_t sn, const uint16_t port){
    if(SOCK_CLOSED == getSn_SR(sn)){
        if((ret = socket(sn, Sn_MR_UDP, port, 0x00)) != sn)
            return ret;
    }
    return 1;
}

