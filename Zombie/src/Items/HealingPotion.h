#pragma once
#include "Item.h"

class HealingPotion : public Item
{
public:
	HealingPotion() = default;
	virtual ~HealingPotion() = default;

	void OnCollide(Player& player) override;
};