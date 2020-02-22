#include "GBMap.h"

int main() {
	GBMap map;
	HarvestTile tile1;
	map.setSquare(&tile1, { 0, 0 });
	map.display();
	return 0;
}
