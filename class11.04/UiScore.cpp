#include "stdafx.h"
#include "UiScore.h"

UiScore::UiScore(const std::string& fontId, const std::string& name)
	: TextGo(fontId, name)
{
	sortingLayer = SortingLayers::UI;
}

void UiScore::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, originPreset);
}

void UiScore::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void UiScore::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.setPosition(pos);
}

void UiScore::SetRotation(float angle)
{
	rotation = angle;
	text.setRotation(angle);
}

void UiScore::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.setScale(scale);
}

void UiScore::SetCharacterSize(unsigned int x)
{
	text.setCharacterSize(x);
}

void UiScore::Reset()
{
	TextGo::Reset();
	SetScore(0);
}

void UiScore::SetScore(int hp)
{
	this->HP = hp;
	text.setString(textFormat + std::to_string(this->HP));
	SetOrigin(originPreset);
}
