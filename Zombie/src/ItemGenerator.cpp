#include "stdafx.h"
#include "ItemGenerator.h"

ItemGenerator::ItemGenerator()
{
	// Empty
}

ItemGenerator::~ItemGenerator()
{
	// Empty
}

void ItemGenerator::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	area.SetPosition(pos);
}

void ItemGenerator::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	area.SetScale(scale);
}

void ItemGenerator::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	area.SetOrigin(preset);
}

void ItemGenerator::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	area.SetOrigin(newOrigin);
}

void ItemGenerator::Init()
{

}

void ItemGenerator::Release()
{
}

void ItemGenerator::Reset()
{
}

void ItemGenerator::Update(float dt)
{
}

void ItemGenerator::Draw(sf::RenderWindow& window)
{
	const auto* scene = (const SceneWave1*)SCENE_MGR.GetCurrentScene();
	if (scene->IsOnDebugArea())
		area.Draw(window);
}

void ItemGenerator::SetSize(const sf::Vector2f size)
{
	area.SetSize(size);
}

void ItemGenerator::SetSize(float w, float h)
{
	area.SetSize({ w, h});
}

Item* ItemGenerator::GenItem(ItemType type)
{
	auto* scene = (SceneWave1*)SCENE_MGR.GetCurrentScene();
	switch (type)
	{
		case ItemType::HealingPotion: {
			auto* result = scene->itemPool.Take<HealingPotion>();
			result->SetTexture("graphics/health_pickup.png");
			result->SetBoundBox();
			result->SetEnableCollide(true);
			result->SetPosition(area.Spawn());
			result->SetDuration(60.f);
			return result;
		}
		case ItemType::Ammo: {
			auto* result = scene->itemPool.Take<Ammo>();
			result->SetTexture("graphics/ammo_pickup.png");
			result->SetBoundBox();
			result->SetEnableCollide(true);
			result->SetPosition(area.Spawn());
			result->SetDuration(60.f);
			return result;
		}
	}
}
