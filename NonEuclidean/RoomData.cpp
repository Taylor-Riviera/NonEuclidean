#include "RoomData.h"

doorLocation RoomData::getDoorLocation(int i) {
	doorLocation output = { mDoors[i].mX + mX , mDoors[i].mY + mY };
	return output;
}