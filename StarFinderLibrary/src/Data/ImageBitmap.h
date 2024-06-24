#pragma once

#include "ImagePoint.h"

struct ImageBitmap {
	size_t getWidth() {
		return _width;
	}

	size_t getHeigth() {
		return _heigth;
	}

	void createArray(size_t width, size_t heigth) {
		_width = width;
		_heigth = heigth;

		_data = new ImagePoint * [width];
		for (size_t i = 0; i < width; i++) {
			_data[i] = new ImagePoint[heigth];
		}
	}

	void setValue(size_t x, size_t y, int redValue, int greenValue, int blueValue) {
		if (!_data)
			return;
		if (x >= _width || y >= _heigth)
			return;
		_data[x][y].setValue(redValue, greenValue, blueValue);
	}

	void updateSetNumber(size_t x, size_t y, int setNumber) {
		if (!_data)
			return;
		if (x >= _width || y >= _heigth)
			return;
		_data[x][y].upateSetNumber(setNumber);
	}

	ImagePoint getPoint(size_t x, size_t y) {
		if (!_data)
			return ImagePoint();

		if (x >= _width || y >= _heigth)
			return ImagePoint();

		return _data[x][y];
	}

	~ImageBitmap() {
		if (_data) {
			for (size_t i = 0; i < _width; i++) {
				delete[] _data[i];
			}
			delete[] _data;
		}

	}

private:
	size_t _width{ 0 };
	size_t _heigth{ 0 };
	ImagePoint** _data{ nullptr };
};