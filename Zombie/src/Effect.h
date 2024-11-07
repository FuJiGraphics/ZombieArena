#pragma once
#include "GameObject.h"

class Effect : public GameObject
{
protected:
	Effect(Effect&) = delete;
	Effect& operator=(const Effect&) = delete;

public:
	Effect() = default;
	virtual ~Effect() = default;

	void SetSortingLayer(SortingLayers layer, int order);
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

public:
	void SetAnimationMode(bool enabled);
	void SetDuration(float duration);
	void SetTexture(const std::string& path);
	void SetObjectPool(ObjectPool<Effect>& myPool);

	fz::Anim& GetAnimation();
private:
	sf::Sprite body;
	float duration = 0.0f;
	float elap = 0.0f;
	ObjectPool<Effect>* myPool = nullptr;
	bool isAnimation = false;
	fz::Anim anim;
};

