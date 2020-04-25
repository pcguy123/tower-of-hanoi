#pragma once
#include <vector>
#include <iostream>
#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <string>
#define TOWER_A 0
#define TOWER_B 1
#define TOWER_C 2


class Scene
{
private:
	unsigned int numDiscs;
	std::vector<Tower> towers;
	Tower win;
	sf::Font fontArial;
public:
	Scene(unsigned int discs);
	~Scene();
	void printScene();
	bool moveDisc(unsigned int from, unsigned int to);
	bool checkWin();
	void resetTowers();
	void resetTowers(unsigned int discs);
	//graphics
	void drawRods(float screenWidth, float screenHeight, sf::Color rodColor, sf::RenderWindow& window);
	void drawDiscs(float screenWidth, float screenHeight, std::vector<sf::Color> colors, sf::RenderWindow& window);
	void drawTable(float screenWidth, float screenHeight, sf::Color color, sf::RenderWindow& window);
	void drawToFromText(float screenWidth, float screenHeight, std::vector<sf::Color> colors, sf::RenderWindow& window, std::string from, std::string to);
	sf::Font getFont();
};