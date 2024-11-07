#include "stdafx.h"
#include "HealingPotion.h"

void HealingPotion::OnCollide(Player& player)
{
	player.AddHP(20);
	Item::OnCollide(player);
}

