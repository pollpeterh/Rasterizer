#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"

void process(image& img, std::ifstream& in);

int main(int argc, const char * argv[])
{
	const std::string FILE_NAME = "test1";

	image img = image(500, 500, WHITE);
	std::ifstream in(FILE_NAME + ".tri");
	process(img, in);
	std::ofstream out(FILE_NAME + "_img.ppm");
	out << img;
	out.close();
	std::cout << "File written" << std::endl;
	return 0;
}

void process(image& img, std::ifstream& in)
{
	point3 p0, p1, p2;
	rgb c0, c1, c2;
	while (in >> p0 >> c0 >> p1 >> c1 >> p2 >> c2) {
		img.triangle(p0, c0, p1, c1, p2, c2);
	}
}