#include "stdafx.h"
#include "Bullet.h"
#include "Zombie.h"
#include "SceneGame.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Bullet::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Bullet::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Bullet::Init()
{
	bulletHitBox.setSize({ 10.f, 4.f });
	bulletHitBox.setOrigin(origin);
	bulletHitBox.setPosition(position);
	bulletHitBox.setOutlineColor(sf::Color::Green);
	bulletHitBox.setFillColor(sf::Color::Transparent);
	bulletHitBox.setOutlineThickness(2);
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(textureId));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	SetOrigin(Origins::ML);

	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	bulletHitBox.setSize({ 10.f, 4.f });
	bulletHitBox.setOrigin(origin);
	bulletHitBox.setPosition(position);
	bulletHitBox.setOutlineColor(sf::Color::Green);
	bulletHitBox.setFillColor(sf::Color::Transparent);
	bulletHitBox.setOutlineThickness(2);

	direction = { 0.f, 0.f };
	sound = 0.f;



}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	//debugBox.SetBounds(GetGlobalBounds());
	bulletHitBox.setPosition(position);
	Utils::SetOrigin(bulletHitBox, Origins::MC);
	sound += dt;
	
}

void Bullet::LateUpdate(float dt)
{
}

void Bullet::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
	{
		return;
	}

	//debugBox.SetOutlineColor(sf::Color::Green);
	const auto& list = sceneGame->GetZombieList();

	for (auto& zombie : list)
	{
		if (!zombie->IsActive())
		{
			continue;
		}
		sf::FloatRect bulletBound = GetGlobalBounds();
		sf::FloatRect zombieBound = zombie->GetGlobalBounds();
		// 바디를 리턴하는 함수를 하나 제작한다.
		// 매개를 렉트로 하고 각 객체별 렉트를 만든다.
		// 
		if (zombie->GetCurrentZombieDie() == false)
		{
			if (bulletBound.intersects(zombieBound) && Utils::CheckCollision(GetBulletHitBox(), zombie->GetZombieHitBox()))
			{
				//debugBox.SetOutlineColor(sf::Color::Red);
				if (sound < hitSoundDelay)
				{
					SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/hit.wav"));
				}
				zombie->OnDamage(this, damage);
				sceneGame->ReturnBullet(this);
				bulletHitBox.setOutlineColor(sf::Color::Red);
				break;
			}
			else
			{
				bulletHitBox.setOutlineColor(sf::Color::Green);
			}
		}
	}
	bulletHitBox.setPosition(position);
	bulletHitBox.setRotation(rotation);
	Utils::SetOrigin(bulletHitBox, Origins::MC);

}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (sceneGame->GetOnOffHitBox() == true)
	{
		window.draw(bulletHitBox);
	}
	//debugBox.Draw(window);
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/shoot.wav"));
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;
	SetRotation(Utils::Angle(direction));
}


