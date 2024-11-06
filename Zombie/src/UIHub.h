#pragma once
#include "GameObject.h"

class UIHub : public GameObject
{
protected:


public:
	UIHub() = default;
	virtual ~UIHub() = default;



private:
	int zombieCount = 0;
	int wave = 0;
};