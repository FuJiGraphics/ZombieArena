#include "stdafx.h"
#include "Wall.h"

Wall::Wall(const std::string& name)
	: GameObject(name)
	, size(0.f, 0.f)
{
	
}

void Wall::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Wall::Init()
{
	// Init Wall
	
}

void Wall::Release()
{
}

void Wall::Reset()
{
}

void Wall::Update(float dt)
{
}

void Wall::Draw(sf::RenderWindow& window)
{
	const auto* scene = (const SceneWave1*)SCENE_MGR.GetCurrentScene();
	if (scene->IsOnDebugWall())
		window.draw(body);
}


bool Wall::Intersect(Player& obj)
{
	bool result = false;
	if (body.getGlobalBounds().intersects(obj.GetBoundBox()))
	{
		obj.OnCollide();
		result = true;
	}
	return result;
}

bool Wall::Intersect(Zombie& obj)
{
	bool result = false;
	if (body.getGlobalBounds().intersects(obj.GetBoundBox()))
	{
		obj.IsCollide(*this);
		result = true;
	}
	return result;
}

void Wall::SetSize(float width, float height)
{
	size = { width, height };
	body.setSize({ width, height });
}
