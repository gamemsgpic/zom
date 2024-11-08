#pragma once
#include "Zombie.h"

class Zombie;
class SceneGame;

class Bullet : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/bullet.png";

	sf::RectangleShape bulletHitBox;

	sf::Vector2f direction;
	float sound = 0.f;
	float hitSoundDelay = 1.f;
	float speed = 0.f;
	int damage;

	SceneGame* sceneGame;
	Zombie* zombie;

	DebugBox debugBox;

public:
	Bullet(const std::string& name = "");
	~Bullet() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	sf::RectangleShape GetBulletHitBox() { return bulletHitBox; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d);
};
