#include "BmpProcessor.h"
#include "BmpStruct.h"

BmpProcessor::BmpProcessor(const char* const data, const size_t dataSize) {
    _ptr = const_cast<char*>(data);
    _end = _ptr + dataSize;
}

ImageBitmap* BmpProcessor::ReadBmpData() {
	if (_ptr == nullptr)
		return nullptr;

    BITMAPFILEHEADER header;

    header.bfType = read_u16();
    header.bfSize = read_u32();
    header.bfReserved1 = read_u16();
    header.bfReserved2 = read_u16();
    header.bfOffBits = read_u32();

    BITMAPINFOHEADER bmiHeader;
    bmiHeader.biSize = read_u32();
    bmiHeader.biWidth = read_s32();
    bmiHeader.biHeight = read_s32();
    bmiHeader.biPlanes = read_u16();
    bmiHeader.biBitCount = read_u16();
    bmiHeader.biCompression = read_u32();
    bmiHeader.biSizeImage = read_u32();
    bmiHeader.biXPelsPerMeter = read_s32();
    bmiHeader.biYPelsPerMeter = read_s32();
    bmiHeader.biClrUsed = read_u32();
    bmiHeader.biClrImportant = read_u32();

    ImageBitmap* bitmap = new ImageBitmap();
    bitmap->createArray(bmiHeader.biWidth, bmiHeader.biHeight);

    for (int i = 0; i < bmiHeader.biWidth; i++) {
        for (int j = 0; j < bmiHeader.biHeight; j++) {
            int blue = read_u8();
            int green = read_u8();
            int red = read_u8();
            bitmap->setValue(i, j, red, green, blue);
        }
    }

	return bitmap;
}

void BmpProcessor::UpdateBmpData(ImageBitmap* bitmap) {
    if (_ptr == nullptr)
        return;

    BITMAPFILEHEADER header;

    header.bfType = read_u16();
    header.bfSize = read_u32();
    header.bfReserved1 = read_u16();
    header.bfReserved2 = read_u16();
    header.bfOffBits = read_u32();

    BITMAPINFOHEADER bmiHeader;
    bmiHeader.biSize = read_u32();
    bmiHeader.biWidth = read_s32();
    bmiHeader.biHeight = read_s32();
    bmiHeader.biPlanes = read_u16();
    bmiHeader.biBitCount = read_u16();
    bmiHeader.biCompression = read_u32();
    bmiHeader.biSizeImage = read_u32();
    bmiHeader.biXPelsPerMeter = read_s32();
    bmiHeader.biYPelsPerMeter = read_s32();
    bmiHeader.biClrUsed = read_u32();
    bmiHeader.biClrImportant = read_u32();

    for (int x = 0; x < bmiHeader.biWidth; x++) {
        for (int y = 0; y < bmiHeader.biHeight; y++) {
            ImagePoint point = bitmap->getPoint(x, y);
            int blue = point.blueValue;
            int green = point.greenValue;
            int red = point.redValue;

            write_u8(blue);
            write_u8(green);
            write_u8(red);
        }
    }
}

unsigned char BmpProcessor::read_u8() {
    if (!_ptr || _ptr == _end)
        return 0;

    unsigned char val = *_ptr;
    _ptr++;
    return val;
}

void BmpProcessor::write_u8(unsigned char value) {
    if (!_ptr || _ptr == _end)
        return;

    *_ptr = value;
    _ptr++;
}

unsigned short BmpProcessor::read_u16()
{
    unsigned char b0, b1;

    b0 = read_u8();
    b1 = read_u8();

    return ((b1 << 8) | b0);
}

unsigned int BmpProcessor::read_u32()
{
    unsigned char b0, b1, b2, b3;

    b0 = read_u8();
    b1 = read_u8();
    b2 = read_u8();
    b3 = read_u8();

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int BmpProcessor::read_s32()
{
    unsigned char b0, b1, b2, b3;

    b0 = read_u8();
    b1 = read_u8();
    b2 = read_u8();
    b3 = read_u8();

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}
