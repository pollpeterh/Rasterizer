#include "rgb.h"

struct material {
	rgb ka, kd, ks;
	int exponent;
	material(const rgb& a, const rgb& d, const rgb& s, int e) : ka(a), kd(d), ks(s), exponent(e) {}
};

struct glossyMaterial : material {
	glossyMaterial(const rgb& c) : material(c, c, LIGHT_GRAY, 64) {}
};

struct matteMaterial : material {
	matteMaterial(const rgb& c) : material(c, c, BLACK, 0) {}
};

