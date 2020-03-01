#include "../loaders/GBMapLoader.h"
#include "../loaders/VGMapLoader.h"
#include "../util/Assert.h"
#include "MapLoaderDriver.h"

void testGBMapLoader() {
	GBMapLoader valid("./res/gmap.txt");
	GBMapLoader semantics("./res/gmap_bad.txt");
	GBMapLoader syntax("./res/gmap_bad_format.txt");
	GBMap* loaded = nullptr;
	std::cout << "Running GBMapLoader tests:" << std::endl;
	ASSERT_SUCCESS((loaded = valid.load()), "loaded valid GBMap.");
	ASSERT_THROWS(std::invalid_argument, semantics.load(), "ERROR: loaded invalid GBMap.");
	ASSERT_THROWS(std::runtime_error, syntax.load(), "ERROR: read invalid file.");
	std::cout << std::endl;
	delete loaded;
}

void testVGMapLoader() {
	VGMapLoader valid("./res/vmap.txt");
	VGMapLoader semantics("./res/vmap_bad.txt");
	VGMapLoader syntax("./res/vmap_bad_syntax.txt");
	VGMap* loaded = nullptr;
	std::cout << "Running VGMapLoader tests:" << std::endl;
	ASSERT_SUCCESS((loaded = valid.load()), "loaded valid VGMap.");
	ASSERT_THROWS(std::invalid_argument, semantics.load(), "ERROR: loaded invalid VGMap.");
	ASSERT_THROWS(std::runtime_error, syntax.load(), "ERROR: read invalid file.");
	std::cout << std::endl;
	delete loaded;
}
