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
	// 카메라 뷰포트의 이동 가능 범위를 설정한다.
	void setBlockArea(float x, float y, float width, float height);

private:
	sf::Vector2f m_PrevPos;
	sf::FloatRect m_BlockArea;
};
