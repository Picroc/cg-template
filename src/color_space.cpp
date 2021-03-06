#include "color_space.h"


ColorSpace::ColorSpace(unsigned short width, unsigned short height): BlackImage(width, height)
{

}

ColorSpace::~ColorSpace()
{
}

void ColorSpace::DrawScene()
{
	for (unsigned short x = 0; x < width; x++) {
		for (unsigned short y = 0; y < height; y++) {
			SetPixel(x, y, color(
				static_cast<unsigned short>(255*x/static_cast<float>(width)),
				static_cast<unsigned short>(255*y/static_cast<float>(height)),
				127
			));
		}
	}
}

void ColorSpace::SetPixel(unsigned short x, unsigned short y, color color)
{
	if (x > width || y > height) {
		return;
	}
	frame_buffer[y * width + x] = color;
}

