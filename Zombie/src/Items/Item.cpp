#include "stdafx.h"
#include "Item.h"

void Item::SetSortingLayer(SortingLayers layer, int order)
{
	this->sortingLayer = layer;
	this->sortingOrder = order;
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Item::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	body.setRotation(angle);
}

void Item::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(scale);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Item::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	body.setOrigin(newOrigin);
}

void Item::Init()
{
}

void Item::Release()
{
}

void Item::Reset()
{
}

void Item::Update(float dt)
{
	if (!IsActive())
		return;

	elap += dt;
	if (elap >= duration)
	{
		elap = 0.0f;
		GameObject::SetActive(false);
		if (myPool)
			myPool->Return(this);
	}

	boundBox.setPosition(position);
}

void Item::Draw(sf::RenderWindow& window)
{
	auto* scene = (SceneWave1*)SCENE_MGR.GetCurrentScene();
	if (!IsActive())
	{
		return;
	}

	window.draw(body);

	if (scene->IsOnDebugBox())
		window.draw(boundBox);
}

void Item::SetDuration(float duration)
{
	this->duration = duration;
}

void Item::SetTexture(const std::string& path)
{
	body.setTexture(TEXTURE_MGR.Get(path));
}

void Item::SetObjectPool(ObjectPool<Item>& myPool)
{
	this->myPool = &myPool;
}

void Item::SetBoundBox(float w, float h)
{
	boundBox.setPosition(position);
	if (w <= 0.0f && h <= 0.0f)
		boundBox.setSize({ body.getLocalBounds().width, body.getLocalBounds().height });
	else
		boundBox.setSize({ w, h });
	boundBox.setFillColor(sf::Color::Transparent);
	boundBox.setOutlineColor(sf::Color::Green);
	boundBox.setOutlineThickness(3.0f);
}

void Item::SetEnableCollide(bool enabled)
{
	auto* scene = (SceneWave1*)SCENE_MGR.GetCurrentScene();
	enabledCollide = enabled;
	if (enabledCollide)
		scene->EnableCollideItemList.push_back(this);
	else
		scene->EnableCollideItemList.remove(this);
}

bool Item::EnabledCollide() const
{
	return enabledCollide;
}

sf::FloatRect Item::GetBoundBox() const
{
	const sf::Vector2f& pos = boundBox.getPosition();
	const sf::Vector2f& size = boundBox.getSize();
	return { pos.x, pos.y, size.x, size.y };
}

void Item::OnCollide(Player& player)
{
	active = false;
	auto* scene = (SceneWave1*)SCENE_MGR.GetCurrentScene();
	scene->itemPool.Return(this);
	scene->EnableCollideItemList.remove(this);
}

void Item::OnCollide(Zombie& player)
{
	active = false;
	auto* scene = (SceneWave1*)SCENE_MGR.GetCurrentScene();
	scene->itemPool.Return(this);
	scene->EnableCollideItemList.remove(this);
}
