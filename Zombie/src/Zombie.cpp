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
		Utils::Normalize(dir);
		float angle = Utils::Angle(dir);
		body.setRotation(angle);
		prevPos = position;
		sf::Vector2f nextPos = position + (dir * speed * dt);
		float length = Utils::Distance(nextPos, player->GetPosition());
		if(length >= boundBox.getSize().x * 0.8f)
			this->SetPosition(position + (dir * speed * dt));
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

	const auto* scene = (const SceneWave1*)SCENE_MGR.GetCurrentScene();
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
		this->SetSpeed(30.f);
		this->SetAttackSpeed(1.0f);
		hp.SetMaxHp(100);
		hp.SetSize(50.f, 5.f);
		hp.SetOrigin(Origins::MC);
		this->ResetBoundBox();
		break;
	case ZombieType::chaser:
		TEXTURE_MGR.Load("Graphics/chaser.png");
		body.setTexture(TEXTURE_MGR.Get("Graphics/chaser.png"));
		this->SetAttack(30.f);
		this->SetSpeed(100.f);
		this->SetAttackSpeed(1.0f);
		hp.SetMaxHp(200);
		hp.SetSize(50.f, 5.f);
		hp.SetOrigin(Origins::MC);
		this->ResetBoundBox();
		break;
	case ZombieType::bloater:
		TEXTURE_MGR.Load("Graphics/bloater.png");
		body.setTexture(TEXTURE_MGR.Get("Graphics/bloater.png"));
		this->SetAttack(70.f);
		this->SetSpeed(65.f);
		this->SetAttackSpeed(1.2f);
		hp.SetMaxHp(1000);
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
		if (myPool)
			myPool->Return(this);
		scene.CurrZombieCount -= 1;
	}
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
