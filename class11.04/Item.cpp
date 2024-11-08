#include "stdafx.h"
#include "Item.h"

Item::Item(const std::string& name) : GameObject(name)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Item::SetRotation(float angle)
{
	rotation = angle;
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void Item::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Item::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Item::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Item::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Item::Init()
{
	itemhitBox.setOrigin({0.f,0.f});
	itemhitBox.setPosition(position);
	itemhitBox.setOutlineColor(sf::Color::Green);
	itemhitBox.setFillColor(sf::Color::Transparent);
	itemhitBox.setOutlineThickness(2);
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	SetType(itypes);
}

void Item::Release()
{
}

void Item::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	itemhitBox.setPosition(position.x + 3.f, position.y);
	itemhitBox.setOutlineColor(sf::Color::Green);
	itemhitBox.setFillColor(sf::Color::Transparent);
	itemhitBox.setOutlineThickness(2);
	Utils::SetOrigin(itemhitBox, Origins::MC);
}

void Item::Update(float dt)
{
	itemhitBox.setPosition(position);
}

void Item::LateUpdate(float dt)
{
}

void Item::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
	{
		return;
	}
	sf::FloatRect items = GetGlobalBounds();
	sf::FloatRect playerbound = player->GetGlobalBounds();
	if (items.intersects(playerbound) && Utils::CheckCollision(GetItemHitBox(), player->GetPlayerHitBox()))
	{

		if (itypes == ItemTypes::Bullet)
		{
			player->OnSupplies(this, bulletCount);
			sceneGame->OnUsedItem(this);
			SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/pickup.wav"));
			return;

		}
		//debugBox.SetOutlineColor(sf::Color::Red);
		player->OnHeeling(this, heelBox);
		if (itypes == ItemTypes::HeelBox)
		{
			player->OnHeeling(this, heelBox);
			sceneGame->OnUsedItem(this);
			SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/pickup.wav"));
			return;
		}

	}
	////debugBox.SetOutlineColor(sf::Color::Green);
	//const auto& list = sceneGame->GetItemList();

	//for (auto& item : list)
	//{
	//	if (!item->IsActive())
	//	{
	//		continue;
	//	}
	//	sf::FloatRect items = GetGlobalBounds();
	//	sf::FloatRect playerbound = player->GetGlobalBounds();
	//	if (items.intersects(playerbound) && Utils::CheckCollision(GetItemHitBox(), player->GetPlayerHitBox()))
	//	{

	//		if (itypes == ItemTypes::Bullet)
	//		{
	//			player->OnSupplies(this, bulletCount);
	//			sceneGame->OnUsedItem(this);
	//			break;
	//		}
	//		//debugBox.SetOutlineColor(sf::Color::Red);
	//		player->OnHeeling(this, heelBox);
	//		if (itypes == ItemTypes::HeelBox)
	//		{
	//			player->OnHeeling(this, heelBox);
	//			sceneGame->OnUsedItem(this);
	//			break;
	//		}

	//	}
	//}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (sceneGame->GetOnOffHitBox() == true)
	{
		window.draw(itemhitBox);
	}
}

void Item::SetType(ItemTypes itype)
{
	float sizeX = itemhitBox.getSize().x;
	float sizeY = itemhitBox.getSize().y;
	this->itypes = itype;
	switch (this->itypes)
	{
	case ItemTypes::Bullet:
		textureId = "graphics/ammo_icon.png";
		itemhitBox.setSize({33.f, 37.f});
		itemhitBox.setOrigin(sizeX * 0.5f + 2.f, sizeY * 0.5f);
		//playerBulletCount += bulletCount;
		break;
	case ItemTypes::HeelBox:
		textureId = "graphics/health_pickup.png";
		itemhitBox.setSize({30.f, 24.f});
		itemhitBox.setOrigin(sizeX * 0.5f - 4.f, sizeY * 0.5f - 5.f);
		//playerHP += heelBox;
		break;
	}
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
}
