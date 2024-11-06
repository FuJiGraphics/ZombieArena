#pragma once
#include "Tile.h"

class TileMap : public GameObject
{
protected:
	TileMap(TileMap&) = delete;
	TileMap& operator=(const TileMap&) = delete;

public:
	TileMap(const std::string& texId, const std::string& name = "");
	~TileMap() = default;

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
	void SetSize(unsigned int width, unsigned height);
	inline sf::Vector2u GetSize() const { return m_Size; }
	inline sf::Vector2f GetLength() const { return m_Length; }

	void Push(const sf::Vector2f& size, const sf::FloatRect& texCoord);

private:
	void PushColumn(const sf::Vector2f& size, const sf::FloatRect& texCoord);
	void PushRow(const sf::Vector2f& size, const sf::FloatRect& texCoord);

private:
	std::vector<Tile>	m_Tiles;
	sf::VertexArray		m_Vao;
	std::string			m_TexId;
	sf::Texture			m_Texture;
	sf::Vector2u		m_Size;
	sf::Vector2u		m_CurrPos;
	sf::Vector2f		m_Length;
	TransformComponent	m_Data;
	unsigned int		width = 0;
	unsigned int		height = 0;
	unsigned int		weightH = 0;
};

