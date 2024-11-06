#pragma once

class Tile
{
public:
	Tile();
	virtual ~Tile();

	sf::FloatRect GetGlobalBounds() const;

	void SetSize(unsigned int width, unsigned int height);
	void SetSize(float width, float height);
	void SetPosition(float x, float y);
	void SetTexCoord(float x, float y, float width, float height);

	inline sf::Vector2f GetSize() const { return m_Size; }
	
	sf::Vertex& operator[] (int index) { return m_Vertices[index]; }
	friend sf::VertexArray& operator<<(sf::VertexArray& vao, Tile& tile);

private:
	std::vector<sf::Vertex> m_Vertices;
	sf::Vector2f m_Pos;
	sf::Vector2f m_Size;
};