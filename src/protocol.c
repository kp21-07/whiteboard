#include "protocol.h"
#include <string.h>

void SerializePacket(const DrawPacket *packet, uint8_t *buffer) {
    // Manual serialization to ensure no padding issues and controlled endianness (assuming Little Endian system for simplicity)
    memcpy(buffer     , &packet->x1        , sizeof(int32_t ));
    memcpy(buffer + 4 , &packet->y1        , sizeof(int32_t ));
    memcpy(buffer + 8 , &packet->x2        , sizeof(int32_t ));
    memcpy(buffer + 12, &packet->y2        , sizeof(int32_t ));
    memcpy(buffer + 16, &packet->color     , sizeof(uint32_t));
    memcpy(buffer + 20, &packet->brush_size, sizeof(int32_t ));
}
