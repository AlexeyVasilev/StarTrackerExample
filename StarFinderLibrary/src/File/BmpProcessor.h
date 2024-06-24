#pragma once

#include "../Data/ImageBitmap.h"

class BmpProcessor {
public:
	
	BmpProcessor(const char* const data, const size_t dataSize);

	ImageBitmap* ReadBmpData();
	void UpdateBmpData(ImageBitmap* bitmap);

private:
	inline unsigned char read_u8();
	inline unsigned short read_u16();
	inline unsigned int read_u32();
	inline int read_s32();
	inline void write_u8(unsigned char value);

private:
	char* _ptr{nullptr};
	const char* _end{nullptr};
};