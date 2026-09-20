#pragma once
#pragma pack(push, 1)

#include <cstdint>

struct Bmp {
    // BITMAPFILEHEADER (14 байт)
    const uint16_t bfType = 0x4D42;
    uint32_t bfSize;
    const uint16_t bfReserved1 = 0;
    const uint16_t bfReserved2 = 0;
    const uint32_t bfOffBits = 0x3E;

    // BITMAPINFOHEADER (40 байт)
    const uint32_t biSize = 0x28;
    int32_t biWidth;
    int32_t biHeight;
    const uint16_t biPlanes = 0x1;
    const uint16_t biBitCount = 0x1;
    const uint32_t biCompression = 0x0;
    uint32_t biSizeImage;
    const uint32_t biXPelsPerMeter = 0xB13;
    const uint32_t biYPelsPerMeter = 0xB13;
    const uint32_t biClrUsed = 0x2;
    const uint32_t biClrImportant = 0x0;

    // ТАБЛИЦА ЦВЕТОВ (8 байт)
    const uint32_t zero = 0xFFFFFF00;
    const uint32_t one = 0x0;
};
