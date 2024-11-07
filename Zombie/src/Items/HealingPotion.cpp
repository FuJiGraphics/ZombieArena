#include "stdafx.h"
#include "HealingPotion.h"

HealingPotion::HealingPotion(ItemType type)
	: Item(type)
{
}

void HealingPotion::OnCollide(Player& player)
{
	player.AddHP(20);
	Item::OnCollide(player);
}

