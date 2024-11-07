#pragma once
#include <string>
#include <limits>
#include <corecrt_math.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

template <typename T>
class TextUI
{
protected:
	static_assert(std::is_arithmetic<T>::value, "T는 산술 가능한 타입이어야 합니다.");

public:
	TextUI(const std::string& fontPath = "");
	TextUI(const TextUI& text);
	virtual ~TextUI() = default;
	
	void SetFont(const std::string& fontPath);
	void SetCharacterSize(unsigned int size);
	void SetColor(const sf::Color& color);

	void SetBaseString(const std::string& baseStr);
	void SetString(const std::string& str);
	void SetNumber(T num);

	void SetOrigin(Origins origins);
	void SetOrigin(const sf::Vector2f& originPos);
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& pos);
	void SetRotation(float angle);
	void SetScale(float x, float y);
	void SetScale(const sf::Vector2f scale);

	std::wstring GetWString() const;
	std::string GetString() const;
	T GetNumber() const;
	sf::Vector2f GetPosition() const;
	float GetRotation() const;
	sf::Vector2f GetScale() const;

	void Draw(sf::RenderTarget& render);

	TextUI& operator=(T num);
	TextUI& operator=(const TextUI& text);

	TextUI operator+(T num);
	TextUI operator-(T num);
	TextUI operator*(T num);
	TextUI operator/(T num);

	friend TextUI operator+(T num, const TextUI& text);
	friend TextUI operator-(T num, const TextUI& text);
	friend TextUI operator*(T num, const TextUI& text);
	friend TextUI operator/(T num, const TextUI& text);

	TextUI operator+(const TextUI& text);
	TextUI operator-(const TextUI& text);
	TextUI operator*(const TextUI& text);
	TextUI operator/(const TextUI& text);

	TextUI& operator+=(T num);
	TextUI& operator-=(T num);
	TextUI& operator*=(T num);
	TextUI& operator/=(T num);

	TextUI& operator+=(const TextUI& text);
	TextUI& operator-=(const TextUI& text);
	TextUI& operator*=(const TextUI& text);
	TextUI& operator/=(const TextUI& text);

	bool operator==(T num);
	bool operator!=(T num);
	bool operator>(T num);
	bool operator<(T num);
	bool operator>=(T num);
	bool operator<=(T num);

	bool operator==(const TextUI& text);
	bool operator!=(const TextUI& text);
	bool operator>(const TextUI& text);
	bool operator<(const TextUI& text);
	bool operator>=(const TextUI& text);
	bool operator<=(const TextUI& text);

private:
	std::string m_Base;
	sf::Font m_Font;
	sf::Text m_Text;
	T m_Count;
};

template <typename T>
TextUI<T>::TextUI(const std::string& fontPath)
	: m_Base("")
	, m_Font()
	, m_Text()
	, m_Count(0)
{
	if (!fontPath.empty() && m_Font.loadFromFile(fontPath))
	{
		m_Text.setFont(m_Font);
		this->SetNumber(m_Count);
	}
	else
		m_Text.setStyle(sf::Text::Bold);
	m_Text.setCharacterSize(10);
	m_Text.setPosition(0.0f, 0.0f);
	m_Text.setScale(1.0f, 1.0f);
}

template <typename T>
inline TextUI<T>::TextUI(const TextUI<T>& text)
{
	m_Font = text.m_Font;
	m_Text = text.m_Text;
	m_Count = text.m_Count;
}

template <typename T>
inline void TextUI<T>::SetFont(const std::string& fontPath)
{
	if (m_Font.loadFromFile(fontPath))
	{
		m_Text.setFont(m_Font);
		this->SetNumber(m_Count);
	}
	else
		m_Text.setStyle(sf::Text::Bold);
}

template <typename T>
inline void TextUI<T>::SetCharacterSize(unsigned int size)
{
	m_Text.setCharacterSize(size);
}

template <typename T>
inline void TextUI<T>::SetColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

template<typename T>
inline void TextUI<T>::SetBaseString(const std::string& baseStr)
{
	m_Base = baseStr;
	m_Text.setString(m_Base + std::to_string(m_Count));
}

template <typename T>
inline void TextUI<T>::SetString(const std::string& str)
{
	m_Text.setString(str);
}

template <typename T>
inline void TextUI<T>::SetNumber(T num)
{
	m_Count = num; 
	m_Text.setString(m_Base + std::to_string(num));
}

template<typename T>
inline void TextUI<T>::SetOrigin(Origins origins)
{
	Utils::SetOrigin(m_Text, origins);
}

template<typename T>
inline void TextUI<T>::SetOrigin(const sf::Vector2f& originPos)
{
	m_Text.setOrigin(originPos);
}

template <typename T>
inline void TextUI<T>::SetPosition(float x, float y)
{
	m_Text.setPosition(x, y);
}

template <typename T>
inline void TextUI<T>::SetPosition(const sf::Vector2f& pos)
{
	m_Text.setPosition(pos);
}

template <typename T>
inline void TextUI<T>::SetRotation(float angle)
{
	m_Text.setRotation(angle);
}

template <typename T>
inline void TextUI<T>::SetScale(float x, float y)
{
	m_Text.setScale(x, y);
}

template <typename T>
inline void TextUI<T>::SetScale(const sf::Vector2f scale)
{
	m_Text.setScale(scale);
}

template<typename T>
inline std::wstring TextUI<T>::GetWString() const
{
	return m_Text.getString().toWideString();
}

template <typename T>
inline std::string TextUI<T>::GetString() const
{
	return m_Text.getString().toAnsiString();
}

template <typename T>
inline T TextUI<T>::GetNumber() const
{
	return m_Count;
}

template <typename T>
inline sf::Vector2f TextUI<T>::GetPosition() const
{
	return m_Text.getPosition();
}

template <typename T>
inline float TextUI<T>::GetRotation() const
{
	return m_Text.getRotation();
}

template <typename T>
inline sf::Vector2f TextUI<T>::GetScale() const
{
	return m_Text.getScale();
}

template <typename T>
inline void TextUI<T>::Draw(sf::RenderTarget& render)
{
	render.draw(m_Text);
}

template <typename T>
inline TextUI<T>& TextUI<T>::operator=(T num)
{
	this->SetNumber(num);
	return *this;
}

template <typename T>
inline TextUI<T>& TextUI<T>::operator=(const TextUI<T>& text)
{
	this->m_Font = text.m_Font;
	this->m_Text = text.m_Text;
	this->m_Count = text.m_Count;
	return *this;
}

template <typename T>
inline TextUI<T> TextUI<T>::operator+(T num)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count + num);
	return newText;
}

template <typename T>
inline TextUI<T> TextUI<T>::operator-(T num)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count - num);
	return newText;
}

template <typename T>
inline TextUI<T> TextUI<T>::operator*(T num)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count * num);
	return newText;
}

template <typename T>
inline TextUI<T> TextUI<T>::operator/(T num)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count / num);
	return newText;
}

template <typename T>
TextUI<T> operator+(T num, const TextUI<T>& text)
{
	TextUI newText = text;
	newText.SetNumber(num + text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> operator-(T num, const TextUI<T>& text)
{
	TextUI newText = text;
	newText.SetNumber(num - text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> operator*(T num, const TextUI<T>& text)
{
	TextUI newText = text;
	newText.SetNumber(num * text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> operator/(T num, const TextUI<T>& text)
{
	TextUI newText = text;
	newText.SetNumber(num / text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> operator%(T num, const TextUI<T>& text)
{
	TextUI newText = text;
	newText.SetNumber(num % text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> TextUI<T>::operator+(const TextUI<T>& text)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count + text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> TextUI<T>::operator-(const TextUI<T>& text)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count - text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> TextUI<T>::operator*(const TextUI<T>& text)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count * text.m_Count);
	return newText;
}

template <typename T>
TextUI<T> TextUI<T>::operator/(const TextUI<T>& text)
{
	TextUI newText = *this;
	newText.SetNumber(m_Count / text.m_Count);
	return newText;
}

template <typename T>
TextUI<T>& TextUI<T>::operator+=(T num)
{
	m_Count += num;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator-=(T num)
{
	m_Count -= num;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator*=(T num)
{
	m_Count *= num;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator/=(T num)
{
	m_Count /= num;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator+=(const TextUI<T>& text)
{
	m_Count += text.m_Count;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator-=(const TextUI<T>& text)
{
	m_Count -= text.m_Count;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator*=(const TextUI<T>& text)
{
	m_Count *= text.m_Count;
	this->SetNumber(m_Count);
	return *this;
}

template <typename T>
TextUI<T>& TextUI<T>::operator/=(const TextUI<T>& text)
{
	m_Count /= text.m_Count;
	this->SetNumber(m_Count);
	return *this;
}

template<typename T>
inline bool TextUI<T>::operator==(T num)
{
	return m_Count == num;
}

template<typename T>
inline bool TextUI<T>::operator!=(T num)
{
	return !(*this == num);
}

template<typename T>
inline bool TextUI<T>::operator>(T num)
{
	return m_Count > num;
}

template<typename T>
inline bool TextUI<T>::operator<(T num)
{
	return m_Count < num;
}

template<typename T>
inline bool TextUI<T>::operator>=(T num)
{
	return (*this > num) || (*this == num);
}

template<typename T>
inline bool TextUI<T>::operator<=(T num)
{
	return (*this < num) || (*this == num);
}

template<typename T>
inline bool TextUI<T>::operator==(const TextUI& text)
{
	return this->m_Count == text.m_Count;
}

template<typename T>
inline bool TextUI<T>::operator!=(const TextUI& text)
{
	return this->m_Count != text.m_Count;
}

template<typename T>
inline bool TextUI<T>::operator>(const TextUI& text)
{
	return this->m_Count > text.m_Count;
}

template<typename T>
inline bool TextUI<T>::operator<(const TextUI& text)
{
	return this->m_Count < text.m_Count;
}

template<typename T>
inline bool TextUI<T>::operator>=(const TextUI& text)
{
	return this->m_Count >= text.m_Count;
}

template<typename T>
inline bool TextUI<T>::operator<=(const TextUI& text)
{
	return this->m_Count <= text.m_Count;
}

template<>
inline bool TextUI<float>::operator==(float num)
{
	return std::fabsf(m_Count - num) <= std::numeric_limits<float>::epsilon();
}

inline bool TextUI<float>::operator!=(float num)
{
	return !(*this == num);
}

template<>
inline bool TextUI<float>::operator>(float num)
{
	return (m_Count > num) && (*this != num);
}

template<>
inline bool TextUI<float>::operator<(float num)
{
	return (m_Count < num) && (*this != num);
}

template<>
inline bool TextUI<float>::operator>=(float num)
{
	return (*this > num) || (*this == num);
}

template<>
inline bool TextUI<float>::operator<=(float num)
{
	return (*this < num) || (*this == num);
}

template<>
inline bool TextUI<double>::operator==(double num)
{
	return std::fabs(m_Count - num) <= std::numeric_limits<double>::epsilon();
}

template<>
inline bool TextUI<double>::operator!=(double num)
{
	return !(*this == num);
}

template<>
inline bool TextUI<double>::operator>(double num)
{
	return (m_Count > num) && (*this != num);
}

template<>
inline bool TextUI<double>::operator<(double num)
{
	return (m_Count < num) && (*this != num);
}

template<>
inline bool TextUI<double>::operator>=(double num)
{
	return (*this > num) || (*this == num);
}

template<>
inline bool TextUI<double>::operator<=(double num)
{
	return (*this < num) || (*this == num);
}
