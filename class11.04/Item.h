#pragma once
#include "Player.h"
#include "SceneGame.h"

class Player;
class SceneGame;

class Item : public GameObject
{
public:
	enum class ItemTypes
	{
		Bullet,
		HeelBox,
	};

	static const int TotalItemTypes = 2; 

protected:
	ItemTypes itypes = ItemTypes::Bullet;
	sf::Sprite body;
	std::string textureId;

	sf::RectangleShape itemhitBox;

	sf::Vector2f pos;

	int bulletCount = 30;
	int heelBox = 50;

	Player* player;
	SceneGame* sceneGame;

	DebugBox debugBox;

public:
	Item(const std::string& name = "");
	~Item() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	sf::RectangleShape GetItemHitBox() { return itemhitBox; }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(ItemTypes itype);
};
