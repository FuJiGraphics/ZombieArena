#include "stdafx.h"
#include "Ammo.h"

void Ammo::OnCollide(Player& player)
{
	player.AddAmmo(100);
	Item::OnCollide(player);
}
