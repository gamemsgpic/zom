#pragma once

class SceneGame;
class TileMap;
class Bullet;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/player.png";

	sf::RectangleShape playerHitBox;

	sf::Color playerColor;

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 1000.f;
	float shootTimer = 0;
	float shootSpeed = 0.1f;
	float reloadSpeed = 1.f;

	int maxPlayerHp = 1000;
	int playerHp = 1000;
	int damege = 1000;

	int ammo = 15;
	int maxammo = 15;
	int allAmmo = 150;

	SceneGame* sceneGame;
	TileMap* tileMap;
	Bullet* bullet;

	bool fireActive = false;
	bool reloadActive = false;
	bool coll = false;

public:
	Player(const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	sf::RectangleShape GetPlayerHitBox() { return playerHitBox; }

	void SetAmmo(int currentammo);
	int GetAmmo() { return ammo; }
	void SetAllAmmo(int currentAllAmmo);
	int GetAllAmmo() { return allAmmo; }
	int GetmaxPlayerHp() { return maxPlayerHp; }

	int SetSupBullet(int sup) { allAmmo += sup; }

	bool GetFire() { return fireActive; }
	bool GetReload() { return reloadActive; }

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Shoot();
	void OnDamage(GameObject* target, int zombiedamage);
	void OnHeeling(GameObject* target, int heelingbox);
	void OnSupplies(GameObject* target, int ammo);
	void ChangeColl() { coll = true; }
	int GetCurrentHp();

	void SetPlayerColorRed();
	void SetPlayerColor();
	void Reload();
};
