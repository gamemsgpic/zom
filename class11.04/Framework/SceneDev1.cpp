#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	auto text = AddGo(new TextGo("fonts/DS-DIGI.ttf", "Scene Name"));
	
	Scene::Init();

	text->sortingLayer = SortingLayers::UI;
	text->Set(25, sf::Color::White);
	text->SetString("Dev 1");
}

void SceneDev1::Enter()
{
	//rect1.setSize({ 200.f, 100.f });
	//rect1.setFillColor(sf::Color::Blue);
	//Utils::SetOrigin(rect1, Origins::MC);
	//
	//rect2.setSize({ 200.f, 100.f });
	//rect2.setFillColor(sf::Color::Green);
	//Utils::SetOrigin(rect1, Origins::MC);
	//
	//
	//Scene::Enter();
	//worldView.setCenter(0.f, 0.f);
	//worldView.setSize(0.f, 0.f);


}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 
	Scene::Update(dt);

}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
