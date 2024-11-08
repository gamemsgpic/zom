#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround(const std::string& name) : GameObject(name)
{
}

void BackGround::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetPosition(position);
}

void BackGround::SetRotation(float angle)
{
	rotation = angle;
	SetRotation(angle);
}

void BackGround::SetScale(const sf::Vector2f& s)
{
	scale = s;
	SetScale(scale);
}

sf::FloatRect BackGround::GetLocalBounds() const
{
	return sf::FloatRect();
}

sf::FloatRect BackGround::GetGlobalBounds() const
{
	return sf::FloatRect();
}

void BackGround::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(body, originPreset);
}

void BackGround::SetOrigin(const sf::Vector2f& newOrigin)
{
	origin = newOrigin;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BackGround::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

void BackGround::Release()
{
}

void BackGround::Update(float dt)
{
	mousePos = sf::Mouse::getPosition();
	for (int i = 0; i < 6; ++i)
	{
		if (text[i].getGlobalBounds().contains(SCENE_MGR.GetCurrentScene()->ScreenToUi(mousePos)))
		{
			text[i].setFillColor(sf::Color::Red);
		}
		else
		{
			text[i].setFillColor(sf::Color::White);
		}
	}
}

void BackGround::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(backGroundId));
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");


	for (int i = 0; i < 6; ++i)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(70.f);
		text[i].setFillColor(sf::Color::White);
		text[i].setPosition(150, (i + 1) * 120.f);
		IndexSet(i);
	}
}



void BackGround::IndexSet(int i)
{
	text[0].setString("1 - INCREASED RATE OF FIRE");
	text[1].setString("2 - INCREASED CLIP SIZECNEXT RELOAD");
	text[2].setString("3 - INCREASED MAX HEALTH");
	text[3].setString("4 - INCREASED RUN SPEED");
	text[4].setString("5 - MORE AND BETTER HEALTH PICKUPS");
	text[5].setString("6 - MORE AND BETTER AMMO PICKUPS");
	Utils::SetOrigin(text[i], Origins::TL);
}

void BackGround::SetBackGroundText()
{
	body.setPosition(0.f, 0.f);
	Utils::SetOrigin(body, Origins::TL);
}

void BackGround::Draw(sf::RenderWindow& window)
{
	if (isUpgradeActive == true)
	{ 
		window.draw(body);
		for (int i = 0; i < 6; ++i)
		{
			window.draw(text[i]);
		}
	}
}
