#include "stdafx.h"
#include "Item.h"

Item::Item(const std::string& name)
	: GameObject(name)
{
	this->scale = { 1.0f, 1.0f };
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
	originPreset = preset;
	if (originPreset != Origins::Custom)
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
	if (texId.empty())
		return;

	TEXTURE_MGR.Load(texId);
	body.setTexture(TEXTURE_MGR.Get(texId));
	this->SetOrigin(Origins::MC);
	boundBox.setPosition(0.0f, 0.0f);
	boundBox.setSize({ body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.5f });
	boundBox.setFillColor(sf::Color::Transparent);
	boundBox.setOutlineColor(sf::Color::Green);
	boundBox.setOutlineThickness(3.0f);
	Utils::SetOrigin(boundBox, Origins::MC);
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

	boundBox.setPosition(position);
}

void Item::Draw(sf::RenderWindow& window)
{
	if (!IsActive())
		return;

	window.draw(body);

	const auto* scene = (const SceneWave1*)SCENE_MGR.GetCurrentScene();
	if (scene->IsOnDebugBox())
		window.draw(boundBox);
}

void Item::SetTextureId(const std::string& texId)
{
	this->texId = texId;
}
