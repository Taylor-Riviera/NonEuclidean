#include "GeneratedMansionLevel.h"

#include "MansionGenerator.h"
#include "PlaceholderRoom.h"
#include "RoomData.h"

void GeneratedMansionLevel::Load(PObjectVec& objs, PPortalVec& portals, Player& player) {
	MansionGenerator mg;
	mg.registerNewRoom(RoomData(10, 7, "Foyer", 5, 0, { { 0,3 },{ 4,6 },{ 9,3 } }));
	mg.registerNewRoom(RoomData(6, 6, "Bathroom", 3, 11, { { 3,0 },{ 5,2 } }));
	mg.generateNewMansion();

	generateRooms(objs, mg);

	player.pos = Vector3(20, GH_PLAYER_HEIGHT + 1, 10);
};

void GeneratedMansionLevel::generateRooms(PObjectVec& objs, MansionGenerator& mg) {
	for each(auto room in mg.getRooms()) {
		
		std::shared_ptr<PlaceholderRoom>
			newRoom((new PlaceholderRoom(static_cast<float>(room.mWidth), static_cast<float>(room.mHeight))));
		newRoom->setPos(Vector3(
			static_cast<float>(room.mX + room.mWidth / 2), 
			0.f, 
			static_cast<float>(room.mY + room.mHeight / 2)));
		objs.push_back(newRoom);
	}
	
	std::shared_ptr<GeneratedMansionLevel> room(new GeneratedMansionLevel());

}