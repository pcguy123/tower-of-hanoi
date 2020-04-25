#include "Scene.h"

Scene::Scene(unsigned int discs)
{
	Tower towerA(discs);
	Tower towerB(0);
	Tower towerC(0);
	win = towerA;
	towers.push_back(towerA);
	towers.push_back(towerB);
	towers.push_back(towerC);

	sf::Font fontArial = sf::Font();
	//fontArial.loadFromFile("res/arial.ttf");
}

Scene::~Scene()
{

}

void Scene::printScene()
{
	unsigned int rows = towers.at(TOWER_A).getNumDiscs();
	if (rows < towers.at(TOWER_B).getNumDiscs())
	{
		rows = towers.at(TOWER_B).getNumDiscs();
	}
	if (rows < towers.at(TOWER_C).getNumDiscs())
	{
		rows = towers.at(TOWER_C).getNumDiscs();
	}
	//std::cout << towers.at(TOWER_A).getNumDiscs();
	unsigned int rowsLeft = rows;
	unsigned int missingRowsA = 0;
	unsigned int missingRowsB = 0;
	unsigned int missingRowsC = 0;
	std::cout << "\n";
	for (int i = 0; i < rows; i++)
	{
		//std::cout << "rowsLeft" << rowsLeft << std::endl;
		//<< "row " << i;
		std::cout << "\t";
		if (rowsLeft <= towers.at(TOWER_A).getNumDiscs())
		{
			//std::cout << "a";
			std::cout << towers.at(TOWER_A).getDisc(i-missingRowsA);
		}
		else
		{
			std::cout << "|";
			missingRowsA++;
		}
		std::cout << "\t";

		if (rowsLeft <= towers.at(TOWER_B).getNumDiscs())
		{
			//std::cout << "b";
			std::cout << towers.at(TOWER_B).getDisc(i-missingRowsB);
		}
		else
		{
			std::cout << "|";
			missingRowsB++;
		}
		std::cout << "\t";

		if (rowsLeft <= towers.at(TOWER_C).getNumDiscs())
		{
			//std::cout << "c";
			std::cout << towers.at(TOWER_C).getDisc(i-missingRowsC);
		}
		else
		{
			std::cout << "|";
			missingRowsC++;
		}
		std::cout << "\t" << std::endl;
		rowsLeft--;
	}
	std::cout << "---------------------------------\n\n";
}

bool Scene::moveDisc(unsigned int from, unsigned int to)
{
	//std::cout << "Before first if\n";
	if ((from != to) && (from % 3 == from) && (to % 3 == to) && !(towers.at(from).getTower().empty()))
	{
		//std::cout << "Before second if\n";
		if ((towers.at(to).getTower().empty()) || (towers.at(from).getTopDisc() < towers.at(to).getTopDisc()))
		{
			//std::cout << "Before add disc\n";
			towers.at(to).addDisc(towers.at(from).getTopDisc());
			//std::cout << "Before remove disc\n";
			towers.at(from).removeDisc();
			//std::cout << "Before return true\n";
			return true;
		}
	}
	std::cout << "You can't do that!";
	return false;
}
// if(Math.pow((from * to), 0.5) % from == 0)
bool Scene::checkWin()
{
	//std::cout << "Before the first if" << std::endl;
	if (win.getNumDiscs() == towers.at(TOWER_C).getNumDiscs())
	{
		//std::cout << "Before the for loop" << std::endl;
		for (unsigned int i = 0; i < win.getNumDiscs(); i++)
		{
			//std::cout << "In for loop time " << i << " before if" << std::endl;
			if (win.getDisc(i) != towers.at(TOWER_C).getDisc(i))
			{
				//std::cout << "In for loop time in if, and will return false" << std::endl;
				return false;
			}
		}
		//std::cout << "After the for loop" << std::endl;
		return true;
	}
	return false;
}

void Scene::resetTowers()
{
	towers.at(TOWER_A) = Tower(numDiscs);
	towers.at(TOWER_B) = Tower(0);
	towers.at(TOWER_C) = Tower(0);
	win = towers.at(TOWER_A);
}

void Scene::resetTowers(unsigned int discs)
{
	towers.at(TOWER_A) = Tower(discs);
	towers.at(TOWER_B) = Tower(0);
	towers.at(TOWER_C) = Tower(0);
	win = towers.at(TOWER_A);
}

void Scene::drawRods(float screenWidth, float screenHeight, sf::Color rodColor, sf::RenderWindow& window)
{
	float rodWidth = screenHeight * 0.0375;
	sf::RectangleShape currentRod(sf::Vector2f(rodWidth, screenHeight * 0.65));
	currentRod.setFillColor(rodColor);
	for (int i = 0; i < 3; i++)
	{
		currentRod.setPosition(sf::Vector2f(screenWidth*0.25*((float)i+1)-rodWidth*0.5, screenHeight*0.1));
		window.draw(currentRod);
	}
}

void Scene::drawDiscs(float screenWidth, float screenHeight, std::vector<sf::Color> colors, sf::RenderWindow& window)
{
	fontArial.loadFromFile("res/arial.ttf");
	sf::Text number = sf::Text("", fontArial, 20); // has hard-coded font size
	number.setFillColor(colors.at(13));
	sf::RectangleShape currentDisc(sf::Vector2f(1.0f, 30.0f));
	for (int i = 0; i < 3; i++) // for each tower
	{
		for (int j = 0; j < towers.at(i).getNumDiscs(); j++) // for each disc in tower
		{
			currentDisc.setFillColor(colors.at(towers.at(i).getDisc(j)-1));
			currentDisc.setSize(sf::Vector2f((float)(30 + 10 * towers.at(i).getDisc(j)), 30.0f)); // has hard-coded size
			currentDisc.setPosition(sf::Vector2f(screenWidth*0.25*((float)i + 1) - currentDisc.getSize().x * 0.5, screenHeight * 0.75 - 30.0 * (float)(towers.at(i).getNumDiscs()-j)));
			window.draw(currentDisc);
			
			number.setString(std::to_string(towers.at(i).getDisc(j)-1));
			if (number.getString() == "1")
			{
				number.setPosition(sf::Vector2f(screenWidth*0.25*((float)i + 1) - number.getLocalBounds().width, screenHeight * 0.75 - 30.0 * (float)(towers.at(i).getNumDiscs() - j) + 5));
			}
			else
			{
				number.setPosition(sf::Vector2f(screenWidth*0.25*((float)i + 1) - number.getLocalBounds().width * 0.5, screenHeight * 0.75 - 30.0 * (float)(towers.at(i).getNumDiscs() - j) + 5));
			}
			window.draw(number);
		}
	}
}

void Scene::drawTable(float screenWidth, float screenHeight, sf::Color tableColor, sf::RenderWindow& window)
{
	sf::RectangleShape table = sf::RectangleShape(sf::Vector2f(screenWidth, screenHeight / 4));
	table.setFillColor(tableColor);
	table.setPosition(0.0f, screenHeight * 0.75);
	window.draw(table);
}

void Scene::drawToFromText(float screenWidth, float screenHeight, std::vector<sf::Color> colors, sf::RenderWindow& window, std::string from, std::string to)
{
	fontArial.loadFromFile("res/arial.ttf");
	// have hard-coded font sizes
	sf::Text fromText = sf::Text("From: " + from, fontArial, 24);
	sf::Text toText = sf::Text("To: " + to, fontArial, 24);

	fromText.setFillColor(colors.at(13));
	toText.setFillColor(colors.at(13));

	fromText.setPosition(sf::Vector2f(25.0, screenHeight*0.80666666));
	toText.setPosition(sf::Vector2f(25.0, screenHeight*0.90333333));

	window.draw(fromText);
	window.draw(toText);
}

sf::Font Scene::getFont()
{
	return fontArial;
}