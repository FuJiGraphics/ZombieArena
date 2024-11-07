#include "stdafx.h"
#include "Effect.h"

void Effect::SetSortingLayer(SortingLayers layer, int order)
{
	this->sortingLayer = layer;
	this->sortingOrder = order;
}

void Effect::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
	anim.SetPosition(pos);
}

void Effect::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	body.setRotation(angle);
}

void Effect::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(scale);
	anim.SetScale(scale);
}

void Effect::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Effect::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	body.setOrigin(newOrigin);
}

void Effect::Init()
{
}

void Effect::Release()
{
}

void Effect::Reset()
{
}

void Effect::Update(float dt)
{
	if (isAnimation)
	{
		anim.Update(dt);
		if (anim.IsFrameEnd())
		{
			GameObject::SetActive(false);
			if (myPool)
				myPool->Return(this);
		}
	}
	else
	{
		elap += dt;
		if (elap >= duration)
		{
			elap = 0.0f;
			GameObject::SetActive(false);
			if (myPool)
				myPool->Return(this);
		}
	}
}

void Effect::Draw(sf::RenderWindow& window)
{
	if (isAnimation)
		anim.Draw(window);
	else
		window.draw(body);
}

void Effect::SetAnimationMode(bool enabled)
{
	isAnimation = enabled;
}

void Effect::SetDuration(float duration)
{
	this->duration = duration;
}

void Effect::SetTexture(const std::string& path)
{
	body.setTexture(TEXTURE_MGR.Get(path));
}

void Effect::SetObjectPool(ObjectPool<Effect>& myPool)
{
	this->myPool = &myPool;
}

fz::Anim& Effect::GetAnimation()
{
	return anim;
}
