#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

Player::Player(const std::string& texId, const std::string& name)
	: GameObject(name)
	, texId(texId)
	, speed(500.f)
	, view(nullptr)
	, delay(1.0f)
{
	this->sortingLayer = SortingLayers::Foreground;
	this->sortingOrder = 0;
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	body.setRotation(angle);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	body.setOrigin(newOrigin);
}

void Player::SetCamera(Camera& view)
{
	this->view = &view;
}

void Player::Init()
{
	TEXTURE_MGR.Load(texId);
	body.setTexture(TEXTURE_MGR.Get(texId));
	this->SetOrigin(Origins::MC);
	boundBox.setPosition(0.0f, 0.0f);
	boundBox.setSize({ body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.5f });
	boundBox.setFillColor(sf::Color::Transparent);
	boundBox.setOutlineColor(sf::Color::Green);
	boundBox.setOutlineThickness(3.0f);
	hp.SetMaxHp(100);
	hp.SetSize(50.f, 5.f);
	hp.SetOrigin(Origins::MC);
	Utils::SetOrigin(boundBox, Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
	sf::Vector2f move = { 0.0f, 0.0f };
	if (InputMgr::GetKey(sf::Keyboard::A))
		move.x -= 1.0f;
	if (InputMgr::GetKey(sf::Keyboard::D))
		move.x += 1.0f;
	if (InputMgr::GetKey(sf::Keyboard::W))
		move.y -= 1.0f;
	if (InputMgr::GetKey(sf::Keyboard::S))
		move.y += 1.0f;
	Utils::Normalize(move);
	position += move * speed * dt;
	prevPos = body.getPosition();
	body.setPosition(position);

	sf::Vector2f mousePosf = FRAMEWORK.GetWindow().mapPixelToCoords(InputMgr::GetMousePosition());

	const sf::Vector2f& newDir = Utils::GetNormal(mousePosf - position);
	float mouseAngle = Utils::Angle(newDir);
	body.setRotation(mouseAngle);

	delayElap += dt;
	bool isClick = false;
	if (weaponType == WeaponType::Minigun)
		isClick = InputMgr::GetMouseButton(sf::Mouse::Left);
	else if (weaponType == WeaponType::Shotgun)
		isClick = InputMgr::GetMouseButtonDown(sf::Mouse::Left);

	if (scene && isClick)
	{
		if (ammo > 0 && delayElap >= delay)
		{
			delayElap = 0.0f;
			if (weaponType == WeaponType::Minigun)
			{
				ammo -= 1;
				const sf::Vector2f& dir = Utils::RandomDirection(0.0f, 15.0f, newDir);
				Bullet* bullet = scene->AddGo(scene->bulletPool.Take());
				bullet->Init();
				bullet->SetWeaponType(WeaponType::Minigun);
				bullet->SetAttack(atkPower);
				bullet->SetPosition(position);
				bullet->SetKnockbackDuration(0.01f);
				bullet->SetDuration(3.0f);
				bullet->SetSpeed(600.f);
				bullet->SetDirection(dir);
				bullet->SetPool(&scene->bulletPool);
			}
			else if (weaponType == WeaponType::Shotgun)
			{
				for (int i = 1; i <= 30; ++i)
				{
					ammo--;
					const sf::Vector2f& dir = Utils::RandomDirection(0.0f, 45.0f, newDir);
					Bullet* bullet = scene->AddGo(scene->bulletPool.Take());
					bullet->Init();
					bullet->SetWeaponType(WeaponType::Shotgun);
					bullet->SetAttack(atkPower);
					bullet->SetPosition(position);
					bullet->SetKnockbackDuration(0.01f);
					bullet->SetDuration(0.3f);
					bullet->SetSpeed(900.f);
					bullet->SetDirection(dir);
					bullet->SetPool(&scene->bulletPool);
					dt += 1.0f;
					if (ammo <= 0)
					{
						ammo = 0;
						break;
					}
				}
			}
		}
	}

	
	if (view)
	{
		view->setCenter(position);
	}
	boundBox.setPosition(position);
	hp.SetPosition({ position.x, position.y + 20.f });
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	if (scene->IsOnDebugBox())
		window.draw(boundBox);

	hp.Draw(window);
}

void Player::SetWeapon(WeaponType type)
{
	weaponType = type;
}

void Player::SetScene(SceneTemplate* scene)
{
	this->scene = scene;
}

void Player::SetHP(float hp)
{
	this->hp = hp;
}

void Player::SetDelay(float delayTime)
{
	this->delay = delayTime;
	delayElap = delayTime;
}

void Player::SetSpeed(float speed)
{
	this->speed = speed;
}

sf::FloatRect Player::GetBoundBox() const
{
	const sf::Vector2f& pos = boundBox.getPosition();
	const sf::Vector2f& size = boundBox.getSize();
	return { pos.x - size.x * 0.5f, pos.y - size.y * 0.5f, size.x, size.y };
}

void Player::SetBoundBox(float x, float y, float width, float height)
{
	boundBox.setPosition(x, y);
	boundBox.setSize({ width, height });
}

void Player::SetDebugColor(sf::Color color)
{
	boundBox.setOutlineColor(color);
}

void Player::SetAttack(float atk)
{
	this->atkPower = atk;
}

void Player::SetAmmo(unsigned int ammo)
{
	this->ammo = ammo;
}

void Player::AddHP(float hp)
{
	this->hp += hp;
}

void Player::AddAmmo(unsigned int ammo)
{
	this->ammo += ammo;
}

void Player::OnCollide()
{
	this->SetPosition(prevPos);
}

void Player::OnDamage(int damage)
{
	hp -= damage;
	auto& scene = *(SceneTemplate*)SCENE_MGR.GetCurrentScene();

	if (hp <= 0.0f)
	{
		hp = 0.0f;
		isDie = true;
		this->SetActive(false);
	}
}

unsigned int Player::GetAmmo() const
{
	return ammo;
}
