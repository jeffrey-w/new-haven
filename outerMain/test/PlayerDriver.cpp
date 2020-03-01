#include "../Player.h"
#include "../util/Assert.h"
#include "PlayerDriver.h"

static constexpr int SAMPLE_SIZE = 10;
static Player* player;

static void setup();
static void tearDown();

void testDrawBuilding() {
	BuildingDeck deck;
	setup();
	ASSERT_THROWS(std::runtime_error, player->drawBuilding(&deck),
		"ERROR: drew from an empty deck.");
	deck.add(new Building());
	ASSERT_SUCCESS(player->drawBuilding(&deck), "drew from valid deck.");
	tearDown();
}

void testDrawHarvestTile() {
	HarvestTileDeck deck;
	setup();
	ASSERT_THROWS(std::runtime_error, player->drawHarvestTile(&deck),
		"ERROR: drew from an empty deck.");
	deck.add(new HarvestTile());
	ASSERT_SUCCESS(player->drawHarvestTile(&deck), "drew from valid deck.");
	tearDown();
}

void testBuildVillage() {

}

void testResourceTracker() {
}

void testPlaceHarvestTile() {
}

void testCalculateResources() {
}

void setup() {
	BuildingDeck bDeck;
	player = new Player();
	for (int i = 0; i < SAMPLE_SIZE; i++) {
		bDeck.add(new Building());
		player->drawBuilding(&bDeck);
	}
}

void tearDown() {
	delete player;
}
