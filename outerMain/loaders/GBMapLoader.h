#pragma once

#include "../maps/GBMap.h"
#include "../util/Scanner.h"

// A utility to read a serialized GBMap and return it as an object.
class GBMapLoader {

public:

	// Supress default constructor.
	GBMapLoader() = delete;
	// Constructs a new GBMapLoader from the specified path. Throws an exception if the file at the
	// specified path cannot be opened.
	GBMapLoader(const std::string&);
	// Suppress copy constructor.
	GBMapLoader(const GBMapLoader&) = delete;
	// Destroys this GBMapLoader.
	~GBMapLoader();
	// Returns a GBMap read from the file specified at the creation of this GBMapLoader. Throws an
	// exception if the specified file is not properly formatted or if it contains invalid map data.
	GBMap* load();

private:

	Scanner* scanner;

	int getNumPlayers();
	HarvestTile* nextTile();
	ResourceToken* nextToken();
	std::pair<int, int> nextSquare();

	std::string errorMessage(const std::string&);

};
