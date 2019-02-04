#include "MansionGenerator.h"

#include <iostream>
#include <iomanip>

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
	// output the result to std::out
	writeMansionToConsole();
}

void MansionGenerator::reconfigureAllPaths() {
	
}

void MansionGenerator::registerNewRoom(const RoomData& data) {
	mRooms.push_back(data);
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
				Tile& tile = _getTileAt(x + room.mX, MANSION_HEIGHT - (y + room.mY) - 1);
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
}

Tile& MansionGenerator::_getTileAt(int x, int y) {
	return mLayoutData[(y * mWidth) + (mWidth - x - 1)];
}