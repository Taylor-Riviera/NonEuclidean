#pragma once
#include "Object.h"
#include "Resources.h"

class PlaceholderRoom : public Object {
public:
	PlaceholderRoom(float x, float z) {
		mesh = AquireMesh("ground.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("checker_green.bmp");
		//euler.x = GH_PI / 2;
		scale = Vector3(x, 1, z);
	}
	void setPos(Vector3 newPos) {
		pos = Vector3(newPos.x * 2, newPos.y, newPos.z * 2);
	}
	virtual ~PlaceholderRoom() {}
};
