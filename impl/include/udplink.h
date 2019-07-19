/**
 * Copyright (c) 2017 cs8425
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license.
 */

#ifndef __UDPLINK_H
#define __UDPLINK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void (*OnUdpData)(void *context, const char *data, uint32_t len);

typedef struct {
  void *context;
  int fd;
  struct sockaddr_in si;
  pthread_t thread;
  uint32_t timeout_ms;
  OnUdpData onData;
  char *buffer;
  uint32_t buffer_size;
  char *addr;
  uint16_t port;
  bool stop;
  bool isServer;
} udpLink_t;

int udp_init(udpLink_t *link, const char *addr, uint16_t port, bool isServer);
int udp_deinit(udpLink_t *link);
int udp_recv(udpLink_t *link, void *data, size_t size, uint32_t timeout_ms);
int udp_send(udpLink_t *link, const void *data, size_t size);
void udp_init_recv_thread(udpLink_t *link, const char *addr, uint16_t port,
                       OnUdpData callback, uint32_t timeout_ms, char *buffer,
                       uint32_t buffer_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
