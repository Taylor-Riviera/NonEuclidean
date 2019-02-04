#pragma once
#include <string>
#include <vector>

#include "RoomData.h"

struct Tile {
	Tile()
	: x(0) 
	, y(0)
	, pathId(-1)
	, doorId(-1)
	, roomId(-1)
	{}

	int x;
	int y;
	//Some id to distinguish path from room from door
	int pathId; //-1 if not path
	int doorId; // -1 if not door, note: all doors are also rooms
	int roomId; // -1 if not room
	friend std::ostream& operator<<(std::ostream &os, const Tile &m);
};

class MansionGenerator {
public:
	MansionGenerator();
	void generateNewMansion();
	void reconfigureAllPaths();
	void registerNewRoom(const RoomData& data);
	void writeMansionToConsole();
private:
	void _init(int width, int height);
	void _placeRoomsInMansion();
	Tile& _getTileAt(int x, int y);
	std::vector<RoomData> mRooms;
	std::vector<Tile> mLayoutData;
	
	int mHeight;
	int mWidth;
};
