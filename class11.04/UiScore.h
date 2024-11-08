#pragma once
#include "TextGo.h"

class UiScore : public TextGo
{
protected:
	std::string textFormat = "Game Over";
	
	int HP = 0;

	bool gameOverText = false;
public:
	UiScore(const std::string& fontId, const std::string& name = "");
	~UiScore() = default;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetCharacterSize(unsigned int x);

	void SetChangeGameOverText() { gameOverText = !gameOverText; }
	bool GetGameOverText() { return gameOverText; }

	void Reset() ;
	void SetScore(int hp);
};

