#pragma once
#include "Item.h"

class HealingPotion : public Item
{
public:
	HealingPotion(ItemType type = ItemType::HealingPotion);
	virtual ~HealingPotion() = default;

	void OnCollide(Player& player) override;
};