#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "state.h"

void SerializePacket(const DrawPacket *packet, uint8_t *buffer);

#endif
