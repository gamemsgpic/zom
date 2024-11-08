#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(const std::string& name) : GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Zombie::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Zombie::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Zombie::OnDamage(GameObject* target, int d)
{
	hp -= d;
	if (hp <= 0)
	{
		SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/splat.wav"));
		zombiedie = true;
		TextureChange("graphics/blood.png");
		sceneGame->MinusZombieCount(1);
		sceneGame->SetScores();
	}
}

void Zombie::Init()
{
	
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	zombieHitBox.setOrigin(origin);
	zombieHitBox.setPosition(position);
	zombieHitBox.setOutlineColor(sf::Color::Green);
	zombieHitBox.setFillColor(sf::Color::Transparent);
	zombieHitBox.setOutlineThickness(2);
	SetType(types);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	//body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	zombieHitBox.setPosition(position);
	Utils::SetOrigin(zombieHitBox, Origins::MC);
	zombieHitBox.setOutlineColor(sf::Color::Green);
	zombieHitBox.setFillColor(sf::Color::Transparent);
	zombieHitBox.setOutlineThickness(2);

	playerHit = 0;
	zombieHitBox.setPosition(position);
	zombieHitBox.setRotation(rotation);
	Utils::SetOrigin(zombieHitBox, Origins::MC);

	
	effectTime = 0;
}

void Zombie::Update(float dt)
{
	if (zombiedie == true)
	{
		effectTime += dt;

		if (effectTime > offeffectTime)
		{
			sceneGame->OnZomBieDie(this);
		}
		return;
	}

	if (player != nullptr && Utils::Distance(position, player->GetPosition()) > 10.f)
	{
		direction = Utils::GetNormal(player->GetPosition() - position);
		SetRotation(Utils::Angle(direction));
		SetPosition({ position + direction * speed * dt });
	}

	zombieHitBox.setPosition(position);
	zombieHitBox.setRotation(rotation);

}

void Zombie::LateUpdate(float dt)
{
}

void Zombie::FixedUpdate(float dt)
{
	playerHit += dt;
	if (sceneGame == nullptr)
	{
		return;
	}
	sf::FloatRect zombieBounds = GetGlobalBounds();
	sf::FloatRect playerBounds = player->GetGlobalBounds();

	if (zombiedie == false)
	{
		if (zombieBounds.intersects(playerBounds) && Utils::CheckCollision(GetZombieHitBox(), player->GetPlayerHitBox()))
		{
			//debugBox.SetOutlineColor(sf::Color::Red);
			if (playerHit > playerinvi)
			{
				player->OnDamage(this, damage);
				playerHit = 0;
			}
			zombieHitBox.setOutlineColor(sf::Color::Red);
			player->ChangeColl();
		}
		else
		{
			zombieHitBox.setOutlineColor(sf::Color::Green);
			// player->ChangeColl();
		}

	}
			
			
	//debugBox.SetOutlineColor(sf::Color::Green);
	//const auto& list = sceneGame->GetZombieList();

	//for (auto& zombie : list)
	//{
	//	if (!zombie->IsActive())
	//	{
	//		continue;
	//	}

	//	
	//}
	//粱厚尝府 面倒贸府
	//for (auto& zombie : list)
	//{
	//	if (!zombie->IsActive())
	//	{
	//		continue;
	//	}
	//
	//	sf::FloatRect zombieBounds = GetGlobalBounds();
	//	auto newPos = position + direction * speed * dt;
	//
	//	if (zombieBounds.intersects(zombieBounds) && Utils::CheckCollision(GetZombieHitBox(), GetZombieHitBox()))
	//	{
	//		
	//	}
	//	SetPosition(newPos);
	//}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (sceneGame->GetOnOffHitBox() == true)
	{
		window.draw(zombieHitBox);
	}
}

void Zombie::SetType(Types type)
{
	float sizeX = zombieHitBox.getSize().x;
	float sizeY = zombieHitBox.getSize().y;
	this->types = type;
	switch (this->types)
	{
	case Types::Bloater:
		textureId = "graphics/bloater.png";
		maxHp = 200;
		hp = maxHp;
		damage + 20;
		speed = 100.f;
		zombieHitBox.setSize({ 59.f, 51.f });
		zombieHitBox.setPosition(0.f, 0.f);
		zombieHitBox.setOrigin(sizeX * 0.5f, sizeY * 0.5f - 2.f);
		break;
	case Types::Chaser:
		textureId = "graphics/chaser.png";
		maxHp = 100;
		hp = maxHp;
		damage + 10;
		speed = 300;
		zombieHitBox.setSize({ 26.f, 41.f });
		zombieHitBox.setPosition(position.x, position.y - 30.f);
		zombieHitBox.setOrigin(sizeX * 0.5f, sizeY * 0.5f + 8.f);
		break;
	case Types::Crawler:
		textureId = "graphics/crawler.png";
		maxHp = 50;
		hp = maxHp;
		speed = 200.f;
		zombieHitBox.setSize({ 49.f, 32.f });
		zombieHitBox.setPosition(position);
		zombieHitBox.setOrigin(sizeX * 0.5f + 6.f, sizeY * 0.5f + 5.f);
		break;
	}
	hp = maxHp;
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
}
