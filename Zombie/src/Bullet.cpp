#include "stdafx.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Wall.h"

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

void Bullet::SetKnockbackDuration(float duration)
{
	KnockbackDuration = duration;
}

void Bullet::SetWeaponType(WeaponType type)
{
	weaponType = type;
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
		if (weaponType == WeaponType::Minigun)
			zombie->SetKnockBack(true, KnockbackDuration);
		else if (weaponType == WeaponType::Shotgun)
			zombie->AddKnockBackDuration(KnockbackDuration);
		zombie->OnDamage(atk);
		isDie = true;
		active = false;

		auto* scene = (SceneTemplate*)SCENE_MGR.GetCurrentScene();
		auto& size = boundBox.getSize();
		Effect* effect = scene->AddGo(scene->effectPool.Take());
		effect->SetAnimationMode(true);
		auto& blood = effect->GetAnimation();
		blood.SetTexture(TEXTURE_MGR.Get("graphics/bloodEffect.png"));
		blood.SetAnimSequence({ 0, 0, 100, 100 }, 0, 0.02, 6);
		blood.AddAnimSequence({ 0, 100, 100, 100 }, 0, 0.02, 6);
		blood.AddAnimSequence({ 0, 200, 100, 100 }, 0, 0.02, 6);
		blood.SetPosition({ position.x - 48.f, position.y - 48.f });
	}
}

void Bullet::OnCollide()
{
	elap = 0;
	GameObject::active = false;
	isDie = true;

	auto* scene = (SceneTemplate*)SCENE_MGR.GetCurrentScene();
	auto& size = boundBox.getSize();
	Effect* effect = scene->AddGo(scene->effectPool.Take());
	effect->SetAnimationMode(true);
	auto& blood = effect->GetAnimation();
	blood.SetTexture(TEXTURE_MGR.Get("graphics/hit_Yellow.png"));
	blood.SetAnimSequence({ 0, 0, 64, 64 }, 0, 0.02, 4);
	blood.AddAnimSequence({ 0, 128, 64, 64 }, 0, 0.02, 4);
	blood.AddAnimSequence({ 0, 192, 64, 64 }, 0, 0.02, 4);
	blood.AddAnimSequence({ 0, 256, 64, 64 }, 0, 0.02, 4);
	blood.SetPosition({ position.x - 48.f, position.y - 48.f });
}
