#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "Scene.h"
#include <vector>

void updateNumDiscs(Scene scene, sf::RenderWindow& window, unsigned int numDiscs, std::string delta)
{
	sf::Font font = sf::Font();
	font.loadFromFile("res/arial.ttf");
	sf::Text prompt = sf::Text("Disc number " + delta + "creased to " + std::to_string(numDiscs), font, 30);
	
	prompt.setFillColor(sf::Color::Black);
	window.draw(prompt);
}

int main()
{
	std::vector<sf::Color> colors;
	colors.push_back(sf::Color(255, 255, 255, 255)); // disc 0 - white
	colors.push_back(sf::Color(255, 0, 0, 255)); // disc 1 - red
	colors.push_back(sf::Color(255, 100, 0, 255)); // disc 2 - orange
	colors.push_back(sf::Color(255, 255, 0, 255)); // disc 3 - yellow
	colors.push_back(sf::Color(0, 255, 0, 255)); // disc 4 - lime green
	colors.push_back(sf::Color(0, 150, 0, 255)); // disc 5 - green
	colors.push_back(sf::Color(0, 255, 255, 255)); // disc 6 - cyan
	colors.push_back(sf::Color(0, 0, 255, 255)); // disc 7 - blue
	colors.push_back(sf::Color(40, 0, 150, 255)); // disc 8 - indigo
	colors.push_back(sf::Color(100, 0, 150, 255)); // disc 9 - purple
	colors.push_back(sf::Color(255, 132, 203, 255)); // disc 10 - pink
	colors.push_back(sf::Color(132, 76, 63, 255)); // disc 11 - brown
	colors.push_back(sf::Color(150, 150, 150, 255)); // disc 12 - gray
	colors.push_back(sf::Color(0, 0, 0, 255)); // disc 13 - black


	float screenWidth = 800;
	float screenHeight = 600;

	sf::Font font = sf::Font();
	font.loadFromFile("res/arial.ttf");

	sf::RenderWindow window(sf::VideoMode((unsigned int)screenWidth, (unsigned int)screenHeight), "Tower of Hanoi");
	window.setFramerateLimit(60);

	unsigned int numDiscs = 3;

	Scene scene(numDiscs);

	sf::Clock clock;
	bool increased = true;
	sf::Time promptWait = sf::seconds(3.0f);
	sf::Time promptTimeElapsed = sf::seconds(0);

	sf::Text prompt = sf::Text("", font, 30);
	prompt.setFillColor(sf::Color::Black);
	sf::Text winPrompt = prompt;

	sf::Text fps = sf::Text("", font, 30);
	fps.setPosition(sf::Vector2f(10.0, 10.0));
	fps.setFillColor(sf::Color::Yellow);

	bool from = true;
	bool to = false;
	int fromNum = -1;
	int toNum = -1;

	bool won = false;

	while (window.isOpen())
	{
		window.clear(sf::Color(74, 187, 205, 255));

		if (promptTimeElapsed > sf::seconds(0))
		{
			if (increased)
			{
				prompt.setString("Number of discs increased to " + std::to_string(numDiscs));
			}
			else
			{
				prompt.setString("Number of discs decreased to " + std::to_string(numDiscs));
			}
			prompt.setPosition(sf::Vector2f((screenWidth - prompt.getLocalBounds().width)*0.5, screenHeight / 60));
			window.draw(prompt);
			promptTimeElapsed = promptTimeElapsed - clock.getElapsedTime();
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Escape:
							window.close();
							break;
						case sf::Keyboard::Up:
							if (numDiscs < 13)
							{
								numDiscs++;
								//updateNumDiscs(scene, window, numDiscs, "in");
								scene.resetTowers(numDiscs);
								increased = true;
								promptTimeElapsed = promptWait;
								won = false;
							}
							break;
						case sf::Keyboard::Down:
							if (numDiscs > 1)
							{
								numDiscs--;
								//updateNumDiscs(scene, window, numDiscs, "de");
								scene.resetTowers(numDiscs);
								increased = false;
								promptTimeElapsed = promptWait;
								won = false;
							}
							break;
						case sf::Keyboard::R:
							scene.resetTowers(numDiscs);
							won = false;
							fromNum = -1;
							toNum = -1;
							break;
					}
					break;
				case sf::Event::TextEntered:
				{
					std::cout << event.text.unicode << std::endl;
					if (event.text.unicode > 47 && event.text.unicode < 51)
					{
						if (from)
						{
							fromNum = event.text.unicode - 48;
							from = false;
							to = true;
						}
						else
						{
							toNum = event.text.unicode - 48;
							from = true;
							to = false;
						}
					}
					//std::cout << fromNum << " " << toNum << std::endl;
					break;
				}
			}
		}

		scene.drawTable(screenWidth, screenHeight, sf::Color(125, 85, 0), window);

		if (fromNum != -1 && toNum != -1)
		{
			scene.drawToFromText(screenWidth, screenHeight, colors, window, std::to_string(fromNum), std::to_string(toNum));
			scene.moveDisc(fromNum, toNum);
			fromNum = -1;
			toNum = -1;
			from = true;
			to = true;
		}
		else if (fromNum != -1 && toNum == -1)
		{
			scene.drawToFromText(screenWidth, screenHeight, colors, window, std::to_string(fromNum), "");
		}
		else
		{
			scene.drawToFromText(screenWidth, screenHeight, colors, window, "", "");
		}

		if (scene.checkWin() == true)
		{
			winPrompt.setString("You won! Hit [R] to reset");
			winPrompt.setPosition(sf::Vector2f((screenWidth - winPrompt.getLocalBounds().width)*0.5, screenHeight / 60));
			prompt.setString("");
			won = true;
			promptTimeElapsed = sf::seconds(0.0);
		}

		scene.drawRods(screenWidth, screenHeight, sf::Color(150, 150, 0), window);
		scene.drawDiscs(screenWidth, screenHeight, colors, window);
		//scene.drawToFromText(screenWidth, screenHeight, colors, window, std::to_string(fromNum), std::to_string(toNum));

		// display the fps
		fps.setString(std::to_string(1.0/clock.getElapsedTime().asSeconds()));
		if (won)
		{
			window.draw(winPrompt);
		}
		window.draw(fps);

		clock.restart();
		window.display();
	}
	return 0;
}