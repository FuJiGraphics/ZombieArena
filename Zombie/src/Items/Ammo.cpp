#include "stdafx.h"
#include "Ammo.h"

Ammo::Ammo(ItemType type)
	: Item(type)
{
}

void Ammo::OnCollide(Player& player)
{
	player.AddAmmo(100);
	Item::OnCollide(player);
}
