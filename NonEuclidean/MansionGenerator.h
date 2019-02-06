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

struct Point {
	Point(int x, int y) : 
	mX(x) ,
	mY(y) { }
	int mX;
	int mY;
};

class Path {
public:
	std::vector<Point> mPoints;
	std::vector<int> mConnectedDoors;//door ids
	int mPathId;
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
	void _createPath(int PathId, doorLocation doorIdStart, doorLocation doorIdGoal);
	float _aStarHuristic(int x1, int y1, int x2, int y2);
	void _writePathToLayout(Path path);
	void _addTileToPath(Path& path, Tile& tile);
	std::vector<Tile> _vaildTilesFromPoint(int x, int y);
	Tile& _getTileAt(int x, int y);
	int _getDirection(const Tile& start, const Tile& end);
	std::vector<RoomData> mRooms;
	std::vector<Tile> mLayoutData;
	
	int mHeight;
	int mWidth;
};
