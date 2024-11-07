#pragma once
#include "Item.h"

class Ammo : public Item
{
public:
	Ammo(ItemType type = ItemType::Ammo);
	virtual ~Ammo() = default;

	void OnCollide(Player& player) override;
};