#pragma once
#include "Item.h"

class Ammo : public Item
{
public:
	Ammo() = default;
	virtual ~Ammo() = default;

	void OnCollide(Player& player) override;
};