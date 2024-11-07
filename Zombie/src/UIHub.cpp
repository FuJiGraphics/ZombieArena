#include "stdafx.h"
#include "UIHub.h"

void UIHub::Init()
{
	this->sortingLayer = SortingLayers::UI;
	this->sortingOrder = 10;

	zombieCount.SetFont("fonts/zombiecontrol.ttf");
	zombieCount.SetOrigin(Origins::BR);
	zombieCount.SetPosition(0.0f, 0.0f);
	zombieCount.SetCharacterSize(30);
	zombieCount.SetBaseString("ZOMBIES: ");

	waveCount.SetOrigin(Origins::BR);
	waveCount.SetFont("fonts/zombiecontrol.ttf");
	waveCount.SetPosition(0.0f, 0.0f);
	waveCount.SetCharacterSize(30);
	waveCount.SetBaseString("WAVE: ");

	score.SetOrigin(Origins::BR);
	score.SetFont("fonts/zombiecontrol.ttf");
	score.SetPosition(0.0f, 0.0f);
	score.SetCharacterSize(30);
	score.SetBaseString("SCORE: ");
}

void UIHub::Release()
{
}

void UIHub::Reset()
{
}

void UIHub::Update(float dt)
{
	if (camera == nullptr)
		return;

	const auto& pos = camera->getCenter();
	const auto& size = camera->getSize();
	float halfW = size.x * 0.5f;
	float halfH = size.y * 0.5f;
	zombieCount.SetPosition(pos.x + halfW * 0.8f , pos.y - halfH * 0.9f);
	zombieCount.SetOrigin(Origins::TR);
	waveCount.SetPosition(pos.x + halfW * 0.3f, pos.y - halfH * 0.9f);
	waveCount.SetOrigin(Origins::TR);
	score.SetPosition(pos.x - halfW * 0.7f, pos.y - halfH * 0.9f);
	score.SetOrigin(Origins::TL);
}

void UIHub::Draw(sf::RenderWindow& window)
{
	zombieCount.Draw(window);
	waveCount.Draw(window);
	score.Draw(window);
}

void UIHub::SetScore(int score)
{
	if (this->score != score)
		this->score = score;
}

void UIHub::SetZombieCount(int count)
{
	if (zombieCount != count)
		zombieCount = count;
}

void UIHub::SetWave(int wave)
{
	if (waveCount != wave)
		waveCount = wave;
}

void UIHub::SetTargetCamera(Camera* target)
{
	camera = target;
	const auto& pos = camera->getCenter();
	const auto& size = camera->getSize();
	float halfW = size.x * 0.5f;
	float halfH = size.y * 0.5f;
	zombieCount.SetPosition(pos.x + halfW * 0.8f, pos.y - halfH * 0.9f);
	zombieCount.SetOrigin(Origins::TR);
	waveCount.SetPosition(pos.x + halfW * 0.3f, pos.y - halfH * 0.9f);
	waveCount.SetOrigin(Origins::TR);
	score.SetPosition(pos.x - halfW * 0.7f, pos.y - halfH * 0.9f);
	score.SetOrigin(Origins::TL);
}
