#include "../loaders/GBMapLoader.h"
#include "../loaders/VGMapLoader.h"
#include "../util/Assert.h"
#include "../util/Debug.h"
#include "MapLoaderDriver.h"

void testGBMapLoader() {
		std::cout << "Running GBMapLoader tests:" << std::endl;
	try {
		GBMapLoader valid("../../res/gmap.txt");
		GBMapLoader semantics("../../res/gmap_bad.txt");
		GBMapLoader syntax("../../res/gmap_bad_syntax.txt");
		GBMap* loaded = nullptr;
		ASSERT_SUCCESS((loaded = valid.load()), "Successfully loaded valid GBMap.");
		ASSERT_THROWS(std::exception, semantics.load(), "ERROR: loaded invalid GBMap.");
		ASSERT_THROWS(std::exception, syntax.load(), "ERROR: read invalid file.");
		std::cout << std::endl;
		delete loaded;
	} catch (const std::invalid_argument& e) {
		std::cerr << e.what() << "\n\n";
	}
}

void testVGMapLoader() {
		std::cout << "Running VGMapLoader tests:" << std::endl;
	try {
		VGMapLoader valid("../../res/vmap.txt");
		VGMapLoader semantics("../../res/vmap_bad.txt");
		VGMapLoader syntax("../../res/vmap_bad_syntax.txt");
		VGMap* loaded = nullptr;
		ASSERT_SUCCESS((loaded = valid.load()), "Successfully loaded valid VGMap.");
		ASSERT_THROWS(std::exception, semantics.load(), "ERROR: loaded invalid VGMap.");
		ASSERT_THROWS(std::exception, syntax.load(), "ERROR: read invalid file.");
		std::cout << std::endl;
		delete loaded;
	} catch (const std::invalid_argument & e) {
		std::cerr << e.what() << "\n\n";
	}
}
