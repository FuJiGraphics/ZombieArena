#include "stdafx.h"
#include "Zombie.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
	, type(ZombieType::crawler)
	, view(nullptr)
	, player(nullptr)
{
	this->sortingLayer = SortingLayers::Foreground;
	this->sortingOrder = -1;
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	body.setRotation(angle);
}

void Zombie::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(scale);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	body.setOrigin(newOrigin);
}

void Zombie::SetCamera(sf::View& view)
{
	this->view = &view;
}

void Zombie::Init()
{
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
}

void Zombie::Update(float dt)
{
	if (isDie)
		return;

	if (player != nullptr)
	{
		sf::Vector2f dir = (player->GetPosition() - position);
		if (isOverlapZombie)
		{ 
			sf::Vector2f backDir = Utils::GetRotateVector(90.f, overlapZombieDir);
			Utils::Normalize(backDir);
			float angle = Utils::Angle(backDir);
			body.setRotation(angle);
			currDir = backDir;
			prevPos = position;
		}
		else
		{
			Utils::Normalize(dir);
			float angle = Utils::Angle(dir);
			body.setRotation(angle);
			currDir = dir;
			prevPos = position;
		}

		KnockBackElap += dt;
		if (isKnockBack && KnockBackElap <= KnockBackDuration)
		{
			sf::Vector2f nextPos = position - (dir * (speed * 10.0f) * dt);
			float length = Utils::Distance(nextPos, player->GetPosition());
			if (length >= boundBox.getSize().x * 0.8f)
			{
				this->SetPosition(nextPos);
				currDir = dir;
			}
		}
		else if (isKnockBack && KnockBackElap > KnockBackDuration)
		{
			isKnockBack = false;
		}
		else if (isOverlapZombie)
		{
			sf::Vector2f nextPos = position + (currDir * (speed * 2.f) * dt);
			this->SetPosition(nextPos);
		}
		else
		{
			sf::Vector2f nextPos = position + (dir * speed * dt);
			float length = Utils::Distance(nextPos, player->GetPosition());
			if (length >= boundBox.getSize().x * 0.8f)
			{
				this->SetPosition(nextPos);
				currDir = dir;
			}
		}
	}
	attackElap += dt;
	if (isCollidePlayer)
	{
		if (attackElap >= atkSpeed)
		{
			attackElap = 0.0f;
			player->OnDamage(atk);
		}
	}
	else
		attackElap = atkSpeed;

	hp.SetPosition({ position.x, position.y + 20.f });
	boundBox.setPosition(position);

}

void Zombie::Draw(sf::RenderWindow& window)
{
	if (isDie)
		return;

	window.draw(body);
	hp.Draw(window);

	const auto* scene = (const SceneTemplate*)SCENE_MGR.GetCurrentScene();
	if (scene->IsOnDebugBox())
		window.draw(boundBox);
}

void Zombie::SetPlayer(Player* player)
{
	this->player = player;
}

void Zombie::SetHP(float hp)
{
	this->hp = hp;
}

void Zombie::SetAttack(float atk)
{
	this->atk = atk;
}

void Zombie::SetSpeed(float speed)
{
	this->speed = speed;
}

void Zombie::SetAttackSpeed(float atkSpeed)
{
	this->atkSpeed = atkSpeed;
}

void Zombie::SetPool(ObjectPool<Zombie>* myPool)
{
	this->myPool = myPool;
}

void Zombie::SetEffectPool(ObjectPool<Effect>* myPool)
{
	this->effectPool = myPool;
}

void Zombie::SetBoundBox(float x, float y, float width, float height)
{
	boundBox.setPosition(x, y);
	boundBox.setSize({ width, height });
}

void Zombie::SetZombieType(ZombieType type)
{
	switch (type)
	{
	case ZombieType::crawler:
		TEXTURE_MGR.Load("Graphics/crawler.png");
		body.setTexture(TEXTURE_MGR.Get("Graphics/crawler.png"));
		this->SetAttack(20.f);
		this->SetSpeed(50.f);
		this->SetAttackSpeed(1.0f);
		hp.SetMaxHp(100);
		hp.SetSize(50.f, 5.f);
		hp.SetOrigin(Origins::MC);
		this->ResetBoundBox();
		break;
	case ZombieType::chaser:
		TEXTURE_MGR.Load("Graphics/chaser.png");
		body.setTexture(TEXTURE_MGR.Get("Graphics/chaser.png"));
		this->SetAttack(15.f);
		this->SetSpeed(97.f);
		this->SetAttackSpeed(1.0f);
		hp.SetMaxHp(300);
		hp.SetSize(50.f, 5.f);
		hp.SetOrigin(Origins::MC);
		this->ResetBoundBox();
		break;
	case ZombieType::bloater:
		TEXTURE_MGR.Load("Graphics/bloater.png");
		body.setTexture(TEXTURE_MGR.Get("Graphics/bloater.png"));
		this->SetAttack(70.f);
		this->SetSpeed(89.f);
		this->SetAttackSpeed(1.5f);
		hp.SetMaxHp(5000);
		hp.SetSize(50.f, 5.f);
		hp.SetOrigin(Origins::MC);
		this->ResetBoundBox();
		break;
	}
	this->SetOrigin(Origins::MC);
}

sf::FloatRect Zombie::GetBoundBox() const
{
	const sf::Vector2f& pos = boundBox.getPosition();
	const sf::Vector2f& size = boundBox.getSize();
	return { pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, size.x, size.y };
}

bool Zombie::IsCollide(Bullet& bullet)
{
	bool result = false;
	const auto& globalBound = this->GetBoundBox();
	const auto& globalBoundBullet = bullet.GetBoundBox();
	if (globalBound.intersects(globalBoundBullet))
		result = true;
	return result;
}

bool Zombie::IsCollide(Wall& wall)
{
	this->SetPosition(prevPos);
	return true;
}

bool Zombie::IsCollide(Zombie& zombie)
{
	bool result = false;
	if (this->GetBoundBox().intersects(zombie.GetBoundBox()))
	{
		zombie.isOverlapZombie = true;
		zombie.overlapZombieDir = currDir;
		result = true;
	}
	return result;
}

bool Zombie::IsCollide(Player& player)
{
	bool result = false;
	if (this->GetBoundBox().intersects(player.GetBoundBox()))
	{
		result = true;
	}
	isCollidePlayer = result;
	return result;
}

void Zombie::OnDamage(int damage)
{
	hp -= damage;
	auto& scene = *(SceneTemplate*)SCENE_MGR.GetCurrentScene();

 	if (hp <= 0.0f)
	{
		hp = 0.0f;
		isDie = true;
		this->SetActive(false);
		scene.CurrZombieCount -= 1;
		scene.score += ((int)ZombieType::crawler * 100 + 100);
		myPool->Return(this);
		if (effectPool)
		{
			Effect* effect = scene.AddGo(effectPool->Take());
			effect->SetSortingLayer(SortingLayers::Background, 0);
			effect->SetTexture("graphics/blood.png");
			effect->SetDuration(15.0f);
			effect->SetObjectPool(*effectPool);
			effect->SetOrigin(Origins::MC);
			effect->SetPosition(position);
		}
	}
}

void Zombie::SetKnockBack(bool enabled, float duration)
{
	isKnockBack = enabled;
	KnockBackDuration = duration;
	KnockBackElap = 0.0f;
}

void Zombie::SetOverlapZombie(bool enabled)
{
	isOverlapZombie = enabled;
}

void Zombie::AddKnockBackDuration(float duration)
{
	isKnockBack = true;
	KnockBackDuration += duration;
	KnockBackElap = 0.0f;
}

void Zombie::ResetBoundBox()
{
	boundBox.setPosition(position);
	boundBox.setSize({ body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.5f });
	boundBox.setFillColor(sf::Color::Transparent);
	boundBox.setOutlineColor(sf::Color::Green);
	boundBox.setOutlineThickness(3.0f);
	Utils::SetOrigin(boundBox, Origins::MC);
}
