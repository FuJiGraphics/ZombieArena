#include "stdafx.h"
#include "Bullet.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bullet::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	body.setRotation(angle);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	body.setOrigin(newOrigin);
}

void Bullet::Init()
{
	TEXTURE_MGR.Load("graphics/bullet.png");
	body.setTexture(TEXTURE_MGR.Get("graphics/bullet.png"));
	boundBox.setPosition(0.0f, 0.0f);
	boundBox.setSize({ body.getLocalBounds().width, body.getLocalBounds().height });
	active = true;
	this->isDie = false;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
}

void Bullet::Update(float dt)
{
	if (!active || isDie)
		return;

	elap += dt;
	if (elap <= duration)
	{
		this->SetPosition(position + (dir * speed * dt));
		body.setRotation(Utils::Angle(dir));
	}
	else
	{
		elap = 0;
		GameObject::active = false;
		isDie = true;
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	if (!active || isDie)
		return;

	window.draw(body);
}

void Bullet::SetDuration(float duration)
{
	this->duration = duration;
}

void Bullet::SetDirection(const sf::Vector2f& dir)
{
	this->dir = dir;
	Utils::Normalize(this->dir);
}

void Bullet::SetSpeed(float speed)
{
	this->speed = speed;
}

void Bullet::SetAttack(float atk)
{
	this->atk = atk;
}

void Bullet::SetPool(ObjectPool<Bullet>* myPool)
{
	this->myPool = myPool;
}

void Bullet::SetBoundBox(float x, float y, float width, float height)
{
	boundBox.setPosition(x, y);
	boundBox.setSize({ width, height });
}

sf::FloatRect Bullet::GetBoundBox() const
{
	const sf::Vector2f& pos = boundBox.getPosition();
	const sf::Vector2f& size = boundBox.getSize();
	float newX = position.x + pos.x;
	float newY = position.y + pos.y;
	return { newX, newY, size.x, size.y };
}

void Bullet::OnCollide(Zombie* zombie)
{
	if (zombie)
	{
		zombie->OnDamage(atk);
		isDie = true;
		active = false;
	}
}
