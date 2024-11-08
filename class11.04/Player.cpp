#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Scene.h"
#include "Bullet.h"
#include "TileMap.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

sf::FloatRect Player::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Player::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Player::SetAmmo(int currentammo)
{
	ammo = currentammo;
}

void Player::SetAllAmmo(int currentAllAmmo)
{
	allAmmo = currentAllAmmo;
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	playerColor = body.getColor();
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
	playerHitBox.setSize({ 35.f, 35.f });
	playerHitBox.setOrigin(origin);
	playerHitBox.setPosition(position);
	playerHitBox.setFillColor(sf::Color::Transparent);
	playerHitBox.setOutlineColor(sf::Color::Green);
	playerHitBox.setOutlineThickness(2);
}

void Player::Release()
{
}

void Player::Reset()
{


	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	SetOrigin(originPreset);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	direction = { 1.f, 0.f };

	shootTimer = 0.f;
	playerHitBox.setSize({ 35.f, 35.f });
	playerHitBox.setOrigin(origin);
	playerHitBox.setPosition(position);
	playerHitBox.setFillColor(sf::Color::Transparent);
	playerHitBox.setOutlineColor(sf::Color::Green);
	playerHitBox.setOutlineThickness(2);
	playerHp = 1000;

	ammo = 15;
	allAmmo = 150;
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		 Utils::Normailize(direction);
	}

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - position);

	SetRotation(Utils::Angle(look));
	SetPosition(position + direction * speed * dt);

	shootTimer += dt;
	if (ammo > 0)
	{
		if (shootTimer > shootSpeed && InputMgr::GetMouseButton(sf::Mouse::Left))
		{
			fireActive = true;
			shootTimer = 0.f;
			--ammo;
			SetAmmo(ammo);
			Shoot();
			if (shootTimer <= 0)
			{
				fireActive = false;
			}
		}
	}
	if (shootTimer > reloadSpeed && InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		reloadActive = true;
		Reload();
		if (shootTimer <= 0)
		{
			reloadActive = false;
		}
	}
	
	playerHitBox.setPosition(position);
	playerHitBox.setRotation(rotation);
	Utils::SetOrigin(playerHitBox, Origins::MC);

	
}

void Player::LateUpdate(float dt)
{
}

void Player::FixedUpdate(float dt)
{
	
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (sceneGame->GetOnOffHitBox() == true)
	{
		if (coll == false)
		{
			playerHitBox.setOutlineColor(sf::Color::Green);
		}
		else
		{
			playerHitBox.setOutlineColor(sf::Color::Red);
		}
		window.draw(playerHitBox);
		coll = false;
	}
}

void Player::Shoot()
{
	int bulletspeed = 2000;
	Bullet* bullet = sceneGame->TakeBullet();
	bullet->Fire(position, look, bulletspeed, damege);
}

void Player::OnDamage(GameObject* target, int zombiedamage)
{
	playerHp -= zombiedamage;
	if (playerHp <= 0)
	{
		playerHp = 0;
		sceneGame->OnPlayerDie(this);
	}
}

void Player::OnHeeling(GameObject* target, int heelingbox)
{
	playerHp += heelingbox;
	if (playerHp > 1000)
	{
		playerHp = 1000;
	}
}

void Player::OnSupplies(GameObject* target, int ammo)
{
	allAmmo += ammo;
}

int Player::GetCurrentHp()
{
	return playerHp;
}

void Player::SetPlayerColorRed()
{
	body.setColor({ 255, 0, 0, 125 });
}

void Player::SetPlayerColor()
{
	body.setColor(playerColor);
}

void Player::Reload()
{
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/reload.wav"));
	ammo += allAmmo > 15 ? 15 : allAmmo;
	allAmmo -= maxammo;
	if (allAmmo < 0)
	{
		allAmmo = 0;
	}
	if (ammo > maxammo)
	{
		int ammoleft = ammo - maxammo;
		ammo = maxammo;
		allAmmo += ammoleft;
	}
	SetAllAmmo(allAmmo);
}
