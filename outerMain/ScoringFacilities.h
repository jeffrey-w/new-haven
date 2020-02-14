#pragma once
#include "VGMap.h"

class GatherFacility{



};


class BuildFacility{
private:
    VGMap* map;

public:
    BuildFacility();
    BuildFacility(VGMap*);
    int calculateVillageScore();



};