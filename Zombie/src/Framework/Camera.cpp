#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Camera.h"

Camera::Camera()
{
	// Empty
}

Camera::~Camera()
{
	// Empty
}

void Camera::setCenter(const sf::Vector2f& pos)
{
	m_PrevPos = this->getCenter();
	sf::Vector2f nextPos = pos;
	const auto& viewSize = this->getSize();
	if (ActivateBlockArea)
	{
		float hw = viewSize.x * 0.5f;
		float hh = viewSize.y * 0.5f;
		if (nextPos.x - hw < m_BlockArea.getPosition().x || nextPos.x + hw > m_BlockArea.width)
			nextPos.x = m_PrevPos.x;
		if (nextPos.y - hh < m_BlockArea.getPosition().y || nextPos.y + hh > m_BlockArea.height)
			nextPos.y = m_PrevPos.y;
	}
	sf::View::setCenter(nextPos);
}

void Camera::setBlockArea(float x, float y, float width, float height)
{
	m_BlockArea = { x, y, width, height };
	ActivateBlockArea = true;
}

