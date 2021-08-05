#pragma once
#include <list>
#include "Geometry.h"

struct HomingShot;

class Trail
{
public:
	void Sethandle(int handle);


	Trail(HomingShot& owner);

	void Update();

	void Draw();

	void Clear();//

	
private:
	int handle_;
	HomingShot& owner_;  
	std::list<Position2> history_;//êŠ—š—ğ
};


