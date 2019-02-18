#pragma once
#include "Scene.h"

class MansionGenerator;
class GeneratedMansionLevel : public Scene {
public:
	virtual void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
	void generateRooms(PObjectVec& objs, MansionGenerator& mg);
};
