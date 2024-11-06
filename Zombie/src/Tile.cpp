#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
	: m_Vertices(4, sf::Vector2f(0.0f, 0.0f))
{
	// Empty
}

Tile::~Tile()
{
	// Empty
}

sf::FloatRect Tile::GetGlobalBounds() const
{
	return { 
		m_Vertices[0].position.x, m_Vertices[0].position.y, 
		m_Vertices[1].position.x, m_Vertices[2].position.y 
	};
}

void Tile::SetSize(unsigned int width, unsigned int height)
{
	m_Size.x = static_cast<float>(width);
	m_Size.y = static_cast<float>(height);
	m_Vertices[1].position = { m_Pos.x + width, m_Pos.y };
	m_Vertices[2].position = { m_Pos.x + width, m_Pos.y + height };
	m_Vertices[3].position = { m_Pos.x, m_Pos.y + height };
}

void Tile::SetSize(float width, float height)
{
	m_Vertices[1].position = { m_Pos.x + width, m_Pos.y };
	m_Vertices[2].position = { m_Pos.x + width, m_Pos.y + height };
	m_Vertices[3].position = { m_Pos.x, m_Pos.y + height };
}

void Tile::SetPosition(float x, float y)
{
	m_Pos = { x, y };
	m_Vertices[0].position = { m_Pos.x, m_Pos.y };
	m_Vertices[1].position = { m_Pos.x + m_Size.x, m_Pos.y };
	m_Vertices[2].position = { m_Pos.x + m_Size.x, m_Pos.y + m_Size.y };
	m_Vertices[3].position = { m_Pos.x, m_Pos.y + m_Size.y };
}

void Tile::SetTexCoord(float x, float y, float width, float height)
{
	m_Vertices[0].texCoords = { x, y };
	m_Vertices[1].texCoords = { x + width, y };
	m_Vertices[2].texCoords = { x + width, y + height };
	m_Vertices[3].texCoords = { x, y + height };
}

sf::VertexArray& operator<<(sf::VertexArray& vao, Tile& tile)
{
	vao.append(tile.m_Vertices[0]);
	vao.append(tile.m_Vertices[1]);
	vao.append(tile.m_Vertices[2]);
	vao.append(tile.m_Vertices[3]);
	return vao;
}
