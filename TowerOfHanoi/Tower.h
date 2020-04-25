#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Tower
{
private:
	std::vector<unsigned int> discs;
	unsigned int numDiscs;
	sf::RectangleShape rod;

public:
	Tower();
	Tower(unsigned int initDiscs);
	void addDisc(unsigned int disc);
	void removeDisc();
	std::vector<unsigned int> getTower();
	unsigned int getTopDisc();
	unsigned int getNumDiscs();
	unsigned int getDisc(unsigned int location);
};