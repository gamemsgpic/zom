#pragma once
#include "GameObject.h"
class BackGround : public GameObject
{
protected:
	sf::Sprite body;
	sf::Text text[6];
	std::string backGroundId = "graphics/background.png";
	sf::Vector2i mousePos;

	bool isUpgradeActive = false;
public:
	BackGround(const std::string& name = "");
	virtual ~BackGround() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void OnOffIsActive() { isUpgradeActive = !isUpgradeActive; }

	void Init() override;
	void Release() override;
	void Update(float dt) override;
	void Reset() override;

	void IndexSet(int i);
	void SetBackGroundText();
	void Draw(sf::RenderWindow& window);
};

