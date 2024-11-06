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

Item* ItemGenerator::GenItem()
{
	// int ran = Utils::RandomRange(1, 3);
	int ran = 1;
	std::string tex = "";
	switch (ran)
	{
		case 1:
			tex = "graphics/health_pickup.png";
			break;
		case 2:break;
		case 3:break;
	}
	Item* item = itemPool.Take();
	item->SetTextureId(tex);
	item->Init(); 
	item->SetPosition(area.Spawn());
	return item;
}
