#pragma once
#include "Player.h"
#include "SceneGame.h"

class Player;
class SceneGame;

class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};

	static const int TotalTypes = 3;
protected:
	Types types = Types::Bloater;
	sf::Sprite body;
	std::string textureId;

	sf::Vector2f direction;

	sf::RectangleShape zombieHitBox;

	int maxHp = 0;
	float speed = 0.f;
	int damage = 10;
	float attackInterval = 0.f;

	int hp = 0;

	float playerHit = 0.f;
	float playerinvi = 1.f;

	float effectTime = 0.f;
	float offeffectTime = 1.5f;

	Player* player;
	SceneGame* sceneGame;

	DebugBox debugBox;

	bool zombiedie = false;

public:
	Zombie(const std::string& name = "");
	~Zombie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	float GetEffectTime() { return effectTime; }
	bool GetCurrentZombieDie() { return zombiedie; }
	void ChangeZombieDie() { zombiedie = !zombiedie; }

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	sf::RectangleShape GetZombieHitBox() { return zombieHitBox; }


	void OnDamage(GameObject* target, int damege);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
	void TextureChange(const std::string& z) { body.setTexture(TEXTURE_MGR.Get(z), true); }
};

