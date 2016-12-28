//
// Created by saber on 2016/12/27.
//

#ifndef WIZNET_SWIG_WRAPPER_H
#define WIZNET_SWIG_WRAPPER_H

#include <stdio.h>
//common methods
int32_t init_hardware();

int32_t init_conf(const char *ip, const char *mask, const char *gateway);

uint16_t get_recved_size(uint8_t sn);

void socket_recv(uint8_t sn, char *buf, size_t *buf_size);

void socket_recvfrom(uint8_t sn, char *buf, size_t *buf_size);

void socket_send(uint8_t sn, const char *buf, const size_t buf_size);

void socket_sendto(uint8_t sn, const char *dst_ip, const uint16_t dst_port,const char *buf,const size_t buf_size);

int32_t socket_disconnect(uint8_t sn);

int32_t tcp_listen(uint8_t sn);

int32_t tcp_client_connect(uint8_t sn, const char *dstip_str, const uint16_t dstPort);
//tcp client methods
uint8_t tcp_client_connect(uint8_t sn, const char *dstIp, const uint16_t dstPort);
//udp methods
int32_t setup_udp(uint8_t sn, const uint16_t port);

#endif //WIZNET_SWIG_WRAPPER_H
