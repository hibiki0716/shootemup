#pragma once
#include "Geometry.h"
#include "Trail.h"
class Trail;
struct Bullet
{
	Position2 pos;
	Vector2 vel;
	bool isFlag = false;
};
struct HomingShot : public Bullet
{
	HomingShot();
	Trail trail;

};

