#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Bullet.h"
#include "Item.h"
#include "UiScore.h"
#include "UiHud.h"
#include "BackGround.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	tile = AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	uiGameOver = AddGo(new UiScore("fonts/zombiecontrol.ttf", "Uiscoere"));
	uiHub = AddGo(new UiHud("UiHud"));
	backGround = AddGo(new BackGround("BackGround"));
	player->SetOrigin(Origins::TL);
	Scene::Init();

	itemSpawn = 0.f;
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	SoundMgr::Instance().PlayBgm(SOUNDBUFFER_MGR.Get("sound/cunning_city.mp3"));
	uiGameOver->SetPosition({ FRAMEWORK.GetWindowSizeF().x, FRAMEWORK.GetWindowSizeF().y + 500 });
	//uiGameOver->SetScale({ 4.f, 4.f });
	uiGameOver->SetCharacterSize(200);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
	worldView.setCenter(0.f, 0.f);
	uiView.setSize(FRAMEWORK.GetWindowSizeF());
	uiView.setCenter(FRAMEWORK.GetWindowSizeF() * 0.5f);
	Scene::Enter();
	uiGameOver->SetOrigin(Origins::MC);
	wave = 1;
	livezombie = 100;
	score = 0;
}

void SceneGame::Exit()
{
	for (auto zombie : zombies)
	{
		RemoveGo(zombie);
		zombiePool.Return(zombie);

	}
	zombies.clear();

	for (auto bullet : bullets)
	{
		RemoveGo(bullet);
		bulletPool.Return(bullet);

	}
	bullets.clear();

	for (auto item : items)
	{
		RemoveGo(item);
		itemPool.Return(item);

	}
	items.clear();

	SoundMgr::Instance().StopBgm();
	SoundMgr::Instance().StopAllSfx();

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);

	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		FRAMEWORK.SetTimeScale(1);
		SCENE_MGR.ChangeScene(SceneIds::Game);
		uiGameOver->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y + 500 });
		uiGameOver->SetChangeGameOverText();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		backGround->OnOffIsActive();
		FRAMEWORK.SetTimeScale(1);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SetOnOffHitBox();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(livezombie);
		//zombieSpawn = true;
	}

	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}

	itemSpawn += dt;
	if (itemSpawn > delaySpawn)
	{
		itemSpawn = 0.f;
		SpawnItems(3);
	}

	float posx = player->GetPosition().x;
	float posy = player->GetPosition().y;
	if (player->GetPosition().x < tile->GetGlobalBounds().left + 50.f +
		(player->GetLocalBounds().width * 0.25))
	{
		posx = tile->GetGlobalBounds().left + 50.f +
			(player->GetLocalBounds().width * 0.25);
		player->SetPosition({ posx, posy });
	}
	if (player->GetPosition().x > tile->GetGlobalBounds().left +
		tile->GetGlobalBounds().width - 50.f -
		(player->GetLocalBounds().width * 0.25))
	{
		posx = tile->GetGlobalBounds().left +
			tile->GetGlobalBounds().width - 50.f -
			(player->GetLocalBounds().width * 0.25);
		player->SetPosition({ posx, posy });
	}
	if (player->GetPosition().y < tile->GetGlobalBounds().top + 50.f +
		(player->GetLocalBounds().height * 0.25))
	{
		posy = tile->GetGlobalBounds().top + 50.f +
			(player->GetLocalBounds().height * 0.25);
		player->SetPosition({ posx, posy });
	}
	if (player->GetPosition().y > tile->GetGlobalBounds().top +
		tile->GetGlobalBounds().height - 50.f -
		(player->GetLocalBounds().height * 0.25))
	{
		posy = tile->GetGlobalBounds().top +
			tile->GetGlobalBounds().height - 50.f
			- (player->GetLocalBounds().height * 0.25);
		player->SetPosition({ posx, posy });
	}

	if (uiGameOver->GetGameOverText() == true)
	{
		uiGameOver->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f });
	}
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::SpawnZombies(int count)
{
	auto bound = tile->GetGlobalBounds();
	for (int i = 0; i < count; ++i)
	{
		Zombie* zombie = zombiePool.Take();
		zombies.push_back(zombie);

		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes - 1);
		zombie->SetType(zombieType);

		sf::Vector2f pos = Utils::RandomInUnitCircle() * 500.f;
		pos.x = Utils::RandomRange(bound.left + 50.f, bound.left + bound.width - 50.f);
		pos.y = Utils::RandomRange(bound.top + 50.f, bound.top + bound.height - 50.f);
		zombie->SetPosition(pos);

		AddGo(zombie);
	}
}

void SceneGame::SpawnItems(int count)
{
	auto bound = tile->GetGlobalBounds();
	for (int i = 0; i < count; ++i)
	{
		Item* item = itemPool.Take();
		items.push_back(item);

		Item::ItemTypes itemType = (Item::ItemTypes)Utils::RandomRange(0, Item::TotalItemTypes - 1);
		item->SetType(itemType);

		sf::Vector2f pos = Utils::RandomInUnitCircle() * 500.f;
		pos.x = Utils::RandomRange(bound.left + 50.f, bound.left + bound.width - 50.f);
		pos.y = Utils::RandomRange(bound.top + 50.f, bound.top + bound.height - 50.f);
		item->SetPosition(pos);

		AddGo(item);
	}
}

void SceneGame::OnUsedItem(Item* item)
{
	RemoveGo(item);
	itemPool.Return(item);
	items.remove(item);
}

void SceneGame::OnZomBieDie(Zombie* z)
{
	if (livezombie <= 0)
	{
		WaveUp();
	}
	RemoveGo(z);
	zombiePool.Return(z);
	zombies.remove(z);
	z->ChangeZombieDie();
}

void SceneGame::OnPlayerDie(Player* zombie)
{
	FRAMEWORK.SetTimeScale(0);
	uiGameOver->SetChangeGameOverText();
}

void SceneGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}

Bullet* SceneGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

void SceneGame::WaveUp()
{
	SoundMgr::Instance().PlaySfx(SOUNDBUFFER_MGR.Get("sound/powerup.wav"));

	++wave;
	if (wave > 3)
	{
		wave = 3;
	}
	livezombie = 100;
	int sum = livezombie * wave;
	SpawnZombies(sum);
	livezombie = sum;
}

void SceneGame::SetScores()
{
	++score;
	if (score > maxScore)
	{
		++maxScore;
	}
}
