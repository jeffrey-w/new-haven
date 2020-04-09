#include "../components/Resources.h"
#include "../players/Player.h"
#include "../util/Assert.h"
#include "../util/Debug.h"
#include "PlayerDriver.h"

static constexpr int SAMPLE_SIZE = 10;
static Player* player;

static void testDrawBuilding();
static void testDrawTile();
static void testBuildVillage();
static void testResourceTracker();
static void testPlaceTile();
static void setup();
static void tearDown();

void testPlayer() {
	std::cout << "Running Player tests:" << std::endl;
	testDrawBuilding();
	testDrawTile();
	testBuildVillage();
	testResourceTracker();
	testPlaceTile();
	std::cout << std::endl;
}

void testDrawBuilding() {
	Deck<Building*> deck;
	setup();
	ASSERT_THROWS(std::runtime_error, player->drawBuilding(&deck),
		"ERROR: drew from an empty deck.");
	deck.add(new Building());
	ASSERT_SUCCESS(player->drawBuilding(&deck), "Successfully drew from valid deck.");
	tearDown();
}

void testDrawTile() {
	Deck<HarvestTile*> deck;
	setup();
	ASSERT_THROWS(std::runtime_error, player->drawTile(&deck),
		"ERROR: drew from an empty deck.");
	deck.add(new HarvestTile());
	ASSERT_SUCCESS(player->drawTile(&deck), "Successfully drew from valid deck.");
	tearDown();
}

void testBuildVillage() {
	setup();
	ASSERT_SUCCESS(player->buildVillage(1, { 0, 0 }), "Successfully built village.");
	tearDown();
}

void testResourceTracker() {
	setup();
	ASSERT_THROWS(std::invalid_argument, player->resourceTracker(nullptr, 0, 0),
		"ERROR: recorded to the null GatherFacility.");
	GatherFacility resources;
	ASSERT_THROWS(std::runtime_error, player->resourceTracker(&resources, AbstractToken::NUM_TYPES, 1),
		"ERROR: recorded to a non-existant resource.");
	ASSERT_THROWS(std::runtime_error, player->resourceTracker(&resources, 0, 1),
		"ERROR: made an invalid adjustment to resources.");
	resources.incrementBy(0, 1);
	ASSERT_SUCCESS(player->resourceTracker(&resources, 0, 1),
		"Successfully decremented resources.");
	tearDown();
}

void testPlaceTile() {
	GBMap map;
	setup();
	ASSERT_THROWS(std::invalid_argument, player->placeTile(1, nullptr, { 0, 0 }),
		"ERROR: placed tile onto the null GBMap.");
	ASSERT_THROWS(std::invalid_argument, player->placeTile(3, &map, { 0, 0 }),
		"ERROR: invalid tile selection allowed.");
	ASSERT_SUCCESS(player->placeTile(1, &map, { 0, 0 }), "Successfully placed harvest tile.");
	tearDown();
}


void setup() {
	Deck<Building*> buildings;
	Deck<HarvestTile*> tiles;
	tiles.add(new HarvestTile());
	player = new Player();
	player->drawTile(&tiles);
	for (int i = 0; i < SAMPLE_SIZE; i++) {
		buildings.add(new Building());
		player->drawBuilding(&buildings);
	}
}

void tearDown() {
	delete player;
}
