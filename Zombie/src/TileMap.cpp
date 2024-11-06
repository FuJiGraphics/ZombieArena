#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& texId, const std::string& name)
	: GameObject(name)
	, m_Tiles()
	, m_Vao()
	, m_Texture()
	, m_Size(0, 0)
	, m_CurrPos(0, 0)
	, m_TexId(texId)
	, m_Data()
{
	this->sortingLayer = SortingLayers::Background;
	this->sortingOrder = -1;
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	m_Data.Translate.translate(pos);
}

void TileMap::SetRotation(float angle)
{
	GameObject::SetRotation(angle);
	m_Data.Rotation.rotate(angle);
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	m_Data.Scale.scale(scale);
}

void TileMap::SetOrigin(Origins preset)
{
	m_Data.Origin = sf::Transform::Identity;
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::Vector2f newOrigin = Utils::SetOrigin(*this, preset) * -1.0f;
		m_Data.Origin.translate(newOrigin);
	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	m_Data.Origin.translate(newOrigin * -1.0f);
}

void TileMap::Init()
{
	TEXTURE_MGR.Load(m_TexId);
	m_Vao.setPrimitiveType(sf::PrimitiveType::Quads);
	m_Texture = TEXTURE_MGR.Get(m_TexId);
}

void TileMap::Release()
{
	m_Vao.clear();
	m_Tiles.clear();
	m_Data.Clear();
}

void TileMap::Reset()
{
}

void TileMap::Update(float dt)
{
	/*static float elap = 0.0f;
	elap += dt;
	if (elap > 0.05f)
	{
		this->SetRotation(1);
		elap = 0.0f;
	}*/
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = &m_Texture;
	state.transform = m_Data.GetWorld();
	window.draw(m_Vao, state);
}

void TileMap::SetSize(unsigned int width, unsigned height)
{
	m_Size.x = width;
	m_Size.y = height;
}

void TileMap::Push(const sf::Vector2f& size, const sf::FloatRect& texCoord)
{
	if (m_CurrPos.x < m_Size.x)
	{
		PushColumn(size, texCoord);
		m_CurrPos.x++;
		width += size.x;
		height = (height < weightH + size.y) ? weightH + size.y : height;
		m_Length.x = (m_Length.x < width) ? width : m_Length.x;
		m_Length.y = (m_Length.y < height) ? height : m_Length.y;
	}
	else if (m_CurrPos.y + 1 < m_Size.y)
	{
		width = 0;
		m_CurrPos.x = 1;
		m_CurrPos.y++;
		PushRow(size, texCoord);
		width += size.x;
		weightH = height;
		// TODO : y축 길이 측정이 정확하지 않음
		m_Length.x = (m_Length.x < width) ? width : m_Length.x;
		m_Length.y = (m_Length.y < weightH + size.y) ? weightH + size.y : m_Length.y;
	}
	else
		// 범위 초과 예외 처리
		return;
}

void TileMap::PushColumn(const sf::Vector2f& size, const sf::FloatRect& texCoord)
{
	sf::Vector2f newPos = { 0.0f, 0.0f };
	if (!m_Tiles.empty())
	{
		int indexH = (m_CurrPos.y - 1) * m_Size.x + m_CurrPos.x;
		Tile& prevTileH = (m_CurrPos.y) ? m_Tiles[indexH] : m_Tiles.back();
		Tile& prevTileW = m_Tiles.back();
		float prevW = prevTileW.GetGlobalBounds().width;
		float prevH = (m_CurrPos.y) ? 
			prevTileH.GetGlobalBounds().height: 
			prevTileH.GetGlobalBounds().top;
		newPos.x = prevW;
		newPos.y = prevH;
	}
	m_Tiles.emplace_back();
	Tile& newTile = m_Tiles.back();
	newTile.SetPosition(newPos.x, newPos.y);
	newTile.SetSize(
		static_cast<unsigned int>(size.x),
		static_cast<unsigned int>(size.y)
	);
	auto& [x, y, width, height] = texCoord;
	newTile.SetTexCoord(x, y, width, height);
	m_Vao << newTile;
}


void TileMap::PushRow(const sf::Vector2f& size, const sf::FloatRect& texCoord)
{
	sf::Vector2f newPos = { 0.0f, 0.0f };
	if (!m_Tiles.empty())
	{
		Tile& prevTile = m_Tiles[(m_CurrPos.y - 1) * m_Size.x + m_CurrPos.x];
		const auto& prevPos = prevTile.GetGlobalBounds();
		newPos.x = 0.0f;
		newPos.y = prevPos.height;
	}
	m_Tiles.emplace_back();
	Tile& newTile = m_Tiles.back();
	newTile.SetPosition(newPos.x, newPos.y);
	newTile.SetSize(
		static_cast<unsigned int>(size.x),
		static_cast<unsigned int>(size.y)
	);
	auto& [x, y, width, height] = texCoord;
	newTile.SetTexCoord(x, y, width, height);
	m_Vao << newTile;
}
