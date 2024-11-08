#pragma once
#include "Scene.h"

class Player;
class Zombie;
class TileMap;
class Bullet;
class Item;
class UiScore;
class UiHud;
class BackGround;

class SceneGame : public Scene
{
protected:
	Player* player;
	TileMap* tile;
	Zombie* zombie;
	Bullet* bullet;
	Item* item;
	UiScore* uiGameOver;
	UiHud* uiHub;
	BackGround* backGround;

	std::list<Zombie*> zombies;
	ObjectPool<Zombie> zombiePool;

	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	std::list<Item*> items;
	ObjectPool<Item> itemPool;

	float itemSpawn;
	float delaySpawn = 5.f;

	int wave = 1;
	int livezombie = 100;
	int score = 0;
	int maxScore = 0;

	bool zombieSpawn = false;

	bool onHitBox = false;


public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init();
	void Release();
	void Enter();
	void Exit();
	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void SpawnZombies(int count);
	void SpawnItems(int count);

	void SetOnOffHitBox() { onHitBox = !onHitBox; }
	bool GetOnOffHitBox() { return onHitBox; }
	

	void OnUsedItem(Item* item);
	void OnZomBieDie(Zombie* zombie);
	void OnPlayerDie(Player* zombie);
	void ReturnBullet(Bullet* bullet);
	Bullet* TakeBullet();

	const std::list<Zombie*>& GetZombieList() { return zombies; }
	const std::list<Item*>& GetItemList() { return items; }

	void WaveUp();
	int GetWave() { return wave; }
	int GetWZombieCount() { return livezombie; }
	void MinusZombieCount(int i) { livezombie -= i; }
	void SetScores();
	int GetScore() { return score; }
	int GetMaxScore() { return maxScore; }
};

