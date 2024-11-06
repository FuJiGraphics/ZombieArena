#pragma once

enum class SortingLayers
{
	Background,
	Foreground,
	UI,
	Default,
};

enum class SceneIds
{
	None = -1,
	Dev1,
	Dev2,
	SceneWave1,
	SceneWave2,
	SceneWave3,
	SceneWave4,
	SceneWave5,
	Count,
};

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
};

struct TransformComponent
{
	sf::Transform Origin;
	sf::Transform Translate;
	sf::Transform Scale;
	sf::Transform Rotation;

	void Clear()
	{
		Origin = sf::Transform::Identity;
		Translate = sf::Transform::Identity;
		Scale = sf::Transform::Identity;
		Rotation = sf::Transform::Identity;
	}

	sf::Transform GetWorld() const
	{
		sf::Transform world = Translate * Rotation * Scale * Origin;
		return world;
	}
};

