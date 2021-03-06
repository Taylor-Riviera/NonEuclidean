#include "MansionGenerator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

const int MANSION_WIDTH = 20;
const int MANSION_HEIGHT = 20;

std::ostream& operator<<(std::ostream &os, const Tile &m) {
	int output = 0;
	if (m.pathId != -1) {
		output += (m.pathId + 1);
	}
	if (m.roomId != -1) {
		output += (m.roomId + 1) * 10;
	}
	if (m.doorId != -1) {
		output += (m.doorId + 1) * 100;
	}
	return os << output;
}

MansionGenerator::MansionGenerator() {
	if (mLayoutData.size() == 0) {
		_init(MANSION_WIDTH, MANSION_HEIGHT);
	}
}

void MansionGenerator::generateNewMansion() {
	// Place the rooms in the mansion
	_placeRoomsInMansion();
	// generate paths beteewn the doors
	reconfigureAllPaths();
	// output the result to std::out
	writeMansionToConsole();
}

void MansionGenerator::_createPath(int pathId, doorLocation doorIdStart, doorLocation doorIdGoal) {
	//Path is a vector of points
	//Starting at a door
	Tile currentTile = _getTileAt(doorIdStart.mX, doorIdStart.mY);
	
	int goalXLoc = doorIdGoal.mX;
	int goalYLoc = doorIdGoal.mY;

	int lastDir = 0;
	Path path;
	path.mPathId = pathId;
	//path is a series of points
	while (currentTile.x != goalXLoc && currentTile.y != goalYLoc) {
		//Find a list of valid tiles to go to
		auto tilesList = _vaildTilesFromPoint(currentTile.x, currentTile.y);
		_ASSERT(tilesList.size() != 0);
		if (tilesList.size() == 1) {
			//That's the direction you're going in
			_addTileToPath(path, tilesList[0]);
			lastDir = _getDirection(currentTile, tilesList[0]);
			currentTile = tilesList[0];
			continue;
		}

		//calc dist to the goal from all of them. 
		std::vector<std::pair<float, int>> distanceVector;
		for (int i = 0; i < tilesList.size(); ++i) {
			distanceVector.push_back(std::make_pair(_aStarHuristic(tilesList[i].x, tilesList[i].y, goalXLoc, goalYLoc), i));
		}
		
		std::sort(distanceVector.begin(), distanceVector.end(), [](std::pair<float, int>& rhs, std::pair<float, int>& lhs) {
			return rhs.first < lhs.first;
		});

		_addTileToPath(path, tilesList[distanceVector[0].second]);
		lastDir = _getDirection(currentTile, tilesList[distanceVector[0].second]);
		currentTile = tilesList[distanceVector[0].second];
	}
	
	_writePathToLayout(path);
	mPaths.push_back(path);
}

int MansionGenerator::_getDirection(const Tile& start, const Tile& end) {
	int xdir = start.x - end.x;
	int ydir = start.y - end.y;
	return xdir == 0 ? 3 + ydir : 2 + xdir;
}

std::vector<Tile> MansionGenerator::_vaildTilesFromPoint(int x, int y) {
	std::vector<Tile> output;
	if (x > 0) {
		output.push_back(_getTileAt(x - 1, y));
	}
	if (x < MANSION_WIDTH - 1) {
		output.push_back(_getTileAt(x + 1, y));
	}
	if (y > 0) {
		output.push_back(_getTileAt(x, y - 1));
	}
	if (y < MANSION_HEIGHT - 1) {
		output.push_back(_getTileAt(x, y + 1));
	}
	output.erase(
		std::remove_if(
			output.begin(), 
			output.end(), 
			[](Tile& t) {
		return t.roomId != -1; 
	}), output.end());
	return output;
}

float MansionGenerator::_aStarHuristic(int x1, int y1, int x2, int y2) {
	return static_cast<float>((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void MansionGenerator::_writePathToLayout(Path path) {
	for (auto&& t : path.mPoints) {
		mLayoutData[_getTileIndex(t.mX, t.mY)].pathId = path.mPathId;
	}
}

void MansionGenerator::_addTileToPath(Path& path, Tile& tile) {
	if (path.mPoints.size() == 0) {
		path.mPoints.push_back(Point(tile.x, tile.y));
		return;
	}
	auto back = path.mPoints[path.mPoints.size() - 1];
	if (tile.doorId != -1) {
		path.mConnectedDoors.push_back(tile.doorId);
	}
	else {
		path.mPoints.push_back(Point(tile.x, tile.y));
	}
}

void MansionGenerator::reconfigureAllPaths() {
	_createPath(0, mRooms[0].getDoorLocation(0), mRooms[1].getDoorLocation(0));
}

void MansionGenerator::registerNewRoom(const RoomData& data) {
	mRooms.push_back(data);
}

const std::vector<RoomData>& MansionGenerator::getRooms() {
	return mRooms;
}

const std::vector<Path>& MansionGenerator::getPaths() {
	return mPaths;
}

void MansionGenerator::writeMansionToConsole() {
	for (int y = 0; y < MANSION_HEIGHT; ++y) {
		for (int x = 0; x < MANSION_WIDTH; ++x) {
			std::cout << std::setw(3) << _getTileAt(x, y);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void MansionGenerator::_placeRoomsInMansion() {
	//for each room in mRooms, set all the tiles that are within a room to the proper values
	int roomId = 0;
	int doorId = 0;
	for(auto&& room : mRooms) {
		for (int y = 0; y < room.mHeight; ++y) {
			for (int x = 0; x < room.mWidth; ++x) {
				Tile& tile = _getTileAt(x + room.mX, y + room.mY);
				tile.roomId = roomId;
				for (auto&& door : room.mDoors) {
					if (x == door.mX && y == door.mY) {
						tile.doorId = doorId++;
						break;
					}
				}
			}
		}
		++roomId;
		doorId = 0;
	}

}

void MansionGenerator::_init(int width, int height) {
	mWidth = width;
	mHeight = height;
	mLayoutData = std::vector<Tile>(width * height);
	for (unsigned i = 0; i < mLayoutData.size(); ++i) {
		Point point = _getPointFromIndex(i);
		mLayoutData[i].x = point.mX;
		mLayoutData[i].y = point.mY;
	}
}

int MansionGenerator::_getTileIndex(int x, int y) {
	return (y * mWidth) + x;
}

Point MansionGenerator::_getPointFromIndex(int index) {
	return Point( index % mWidth, index / mWidth);
}

Tile& MansionGenerator::_getTileAt(int x, int y) {
	return mLayoutData[_getTileIndex(x, y)];
}