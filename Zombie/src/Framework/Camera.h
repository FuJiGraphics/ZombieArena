#pragma once
#include <SFML/Graphics.hpp>

class Camera : public sf::View
{
protected:
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

public:
	Camera();
	virtual ~Camera();

	void setCenter(const sf::Vector2f& center);
	// ī�޶� ����Ʈ�� �̵� ���� ������ �����Ѵ�.
	void setBlockArea(float x, float y, float width, float height);

private:
	sf::Vector2f m_PrevPos;
	sf::FloatRect m_BlockArea;
};
