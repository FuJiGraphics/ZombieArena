#include "stdafx.h"
#include "HpBar.h"

HpBar::HpBar()
	: hp(100.f)
	, maxHp(100.f)
	, color(sf::Color::Red)
{
	this->bar.setFillColor(color);
	this->bar.setOutlineColor(sf::Color::Black);
	this->bar.setOutlineThickness(1.f);
	this->SetOrigin(Origins::MC);
}

HpBar::~HpBar()
{
	// Empty
}

void HpBar::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	bar.setPosition(pos);
}

void HpBar::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	bar.setRotation(angle);
}

void HpBar::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	bar.setScale(scale);
}

void HpBar::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(bar, preset);
	}
}

void HpBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	bar.setOrigin(newOrigin);
}

void HpBar::Init()
{
	maxHp = 100.f;
	hp = 100.f;
}

void HpBar::Release()
{

}

void HpBar::Reset()
{
	hp = maxHp;
}

void HpBar::Update(float dt)
{

}

void HpBar::Draw(sf::RenderWindow& window)
{
	float dx = size.x / maxHp;
	float score = (hp / maxHp) * 100.f;
	if (score >= 60.f)
		bar.setFillColor(sf::Color::Green);
	else if (score >= 30.f)
		bar.setFillColor(sf::Color::Yellow);
	else
		bar.setFillColor(sf::Color::Red);
	bar.setSize({ dx * hp, size.y });
	window.draw(bar);
}

void HpBar::SetSize(float width, float height)
{
	size = { width, height };
	bar.setSize(size);
}

void HpBar::SetMaxHp(float hp)
{
	maxHp = hp;
	this->hp = maxHp;
}

void HpBar::SetHp(float hp)
{
	this->hp = hp; 
	ResetStrideHp();
}

void HpBar::AddHp(float hp)
{
	this->hp += hp; 
	ResetStrideHp();
}

void HpBar::SetColor(sf::Color color)
{
	this->color = color;
	this->bar.setFillColor(color);
}

bool HpBar::operator==(float d)
{
	return Utils::IsEqual(hp, d);
}

bool HpBar::operator<(float d)
{
	return ((*this != d) && (hp < d));
}

bool HpBar::operator>(float d)
{
	return ((*this != d) && (hp > d));
}

bool HpBar::operator<=(float d)
{
	return ((*this == d) || (*this < d));
}

bool HpBar::operator>=(float d)
{
	return ((*this == d) || (*this > d));
}

HpBar& HpBar::operator+=(float d)
{
	hp += d;

	ResetStrideHp();
	return (*this);
}

HpBar& HpBar::operator-=(float d)
{
	hp -= d;

	ResetStrideHp();
	return (*this);
}

HpBar& HpBar::operator=(float d)
{
	hp = d;

	ResetStrideHp();
	return (*this);
}

void HpBar::ResetStrideHp()
{
	if (this->hp > maxHp)
		this->hp = maxHp;
	if (this->hp <= 0.0f)
		this->hp = 0.0f;
}
