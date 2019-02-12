#pragma once

#include <string>
#include <vector>

struct doorLocation {
	doorLocation(int x, int y) :
		mX(x),
		mY(y){}

	int mX;
	int mY;
};

class RoomData {
public:
	RoomData(int width, int height, const std::string& name, int x, int y, std::vector<doorLocation> doors) :
		mWidth(width),
		mHeight(height),
		mName(name),
		mX(x),
		mY(y),
		mDoors(doors) {}

	int mWidth;
	int mHeight;
	std::string mName;
	int mX;
	int mY;
	std::vector<doorLocation> mDoors;
	doorLocation getDoorLocation(int i);
};