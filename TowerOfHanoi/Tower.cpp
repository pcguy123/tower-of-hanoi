#include "Tower.h"

Tower::Tower()
{

}

Tower::Tower(unsigned int initDiscs)
{
	numDiscs = initDiscs;
	if (initDiscs != 0)
	{
		for (unsigned int i = 0; i < initDiscs; i++)
		{
			discs.push_back(initDiscs - i);
		}
	}
}

void Tower::addDisc(unsigned int disc)
{
	discs.push_back(disc);
	numDiscs++;
}

void Tower::removeDisc()
{
	discs.pop_back();
	numDiscs--;
}

std::vector<unsigned int> Tower::getTower()
{
	return discs;
}

unsigned int Tower::getTopDisc()
{
	return discs.back();
}

unsigned int Tower::getNumDiscs()
{
	return numDiscs;
}

unsigned int Tower::getDisc(unsigned int location)
{
	return discs.at(numDiscs - location - 1); // location starts at 0 from the top
}