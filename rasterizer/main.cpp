#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"

struct tri {
	point3 points[3];
	rgb colors[3];

	tri() { }
};

void process(image& img, const std::vector<tri>& tf);

int main(int argc, const char * argv[])
{
	const std::string FILE_NAME = "test1";
	std::ifstream in(FILE_NAME + ".tri");
	std::vector<tri> triFile;
	point3 p;
	rgb c;
	tri triangle;
	int count = 0;
	while (in >> p >> c) {

		triangle.points[count] = p;
		triangle.colors[count] = c;

		if (count == 2) {
			triFile.push_back(triangle);
			triangle = tri();
			count = -1;
		}

		count++;
	}

	image img = image(500, 500, WHITE);
	process(img, triFile);
	std::ofstream out(FILE_NAME + "_img.ppm");
	out << img;
	out.close();
	std::cout << "File written" << std::endl;
	return 0;
}

void process(image& img, const std::vector<tri>& tf)
{
	for (int i = 0; i < tf.size(); i++) {
		point3 a = tf[i].points[0];
		point3 b = tf[i].points[1];
		point3 c = tf[i].points[2];
		rgb ac = tf[i].colors[0];
		rgb bc = tf[i].colors[1];
		rgb cc = tf[i].colors[2];

		img.triangle(a, ac, b, bc, c, cc);
	}
}