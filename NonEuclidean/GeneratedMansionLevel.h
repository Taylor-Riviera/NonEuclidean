#pragma once
#include "Scene.h"

class MansionGenerator;
class GeneratedMansionLevel : public Scene {
public:
	virtual void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
private:
	void generateRooms(PObjectVec& objs, MansionGenerator& mg);
	void generatePaths(PObjectVec& objs, MansionGenerator& mg);
};
