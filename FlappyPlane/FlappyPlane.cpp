// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>



using namespace sf;



int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "FlappyPlane!!!", Style::Fullscreen);
	bool paused = true;
	bool acceptInput = true;
	Texture background;
	background.loadFromFile("graphics/backgound.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(background);
	backgroundSprite.setPosition(0, 0);
	Texture player;
	player.loadFromFile("graphics/player.png");
	Sprite playerSprite;
	playerSprite.setTexture(player);
	playerSprite.setScale(Vector2f(0.5, 0.5));
	RectangleShape pipe;
	pipe.setSize(Vector2f(100, 800));
	pipe.setPosition(1920 / 2, 1080-800);
	pipe.setFillColor(Color::Green);
	bool pipeIsMoving = false;
	float pipeSpeed = 0.0f;
	Clock clock;
	sf::Text messageText;
	sf::Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Press Enter to start");
	scoreText.setString("Score =0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);
	int score = 0;
	Texture dead;
	dead.loadFromFile("graphics/dead.png");
	Sprite deadSprite;
	deadSprite.setTexture(dead);
	bool scoreAugment = true;
	SoundBuffer jumpBuffer;
	Sound jump;
	jumpBuffer.loadFromFile("sounds/jump.wav");
	jump.setBuffer(jumpBuffer);
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sounds/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);










	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Return)) {


			if (paused) {
				paused = false;
				score = 0;

				//hidden the rip
				deadSprite.setPosition(675, 2000);
				playerSprite.setPosition(0, 0);

			}
			else {
				paused = true;
			}

		}
		

		if (!paused) {
			if (playerSprite.getGlobalBounds().intersects(pipe.getGlobalBounds())) {
				paused = true;
				deadSprite.setPosition(0, 0);
				playerSprite.setPosition(675, 2000);
				messageText.setString("GameOver");
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				scoreText.setPosition(20, 20);
				death.play();
			}


				
					if (Keyboard::isKeyPressed(Keyboard::Space)) {
						jump.play();
						
						if (playerSprite.getPosition().y - 5 < 0) {
							playerSprite.setPosition(Vector2f(playerSprite.getPosition().x, 0));

						}
						else {
							playerSprite.setPosition(Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y - 5));
						}

					}
					
				
			
			
			if (pipe.getPosition().x <0 && scoreAugment ) {
				score += 10;
				scoreAugment = false;
			}
			if (playerSprite.getPosition().y < 980) {

				playerSprite.setPosition(Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 1));
			}
			Time dt = clock.restart();
			if (!pipeIsMoving) {
				srand((int)time(0) * 10);
				float height = (rand() % 800);
				pipe.setPosition(2000, height);
				//fast is?
				srand((int)time(0) * 10);
				pipeSpeed = (rand() % 200) + 200;
				pipeIsMoving = true;
				scoreAugment = true;

			}
			else {
				pipe.setPosition(pipe.getPosition().x - (pipeSpeed*dt.asSeconds()), pipe.getPosition().y);
				
					
				
				if (pipe.getPosition().x < -100) {
					

					pipeIsMoving = false;
					scoreAugment = false;
				}

			}



		}

		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());
		window.clear();
		window.draw(backgroundSprite);
		window.draw(pipe);
		window.draw(scoreText);
		if (paused) {
			window.draw(messageText);
		}
		window.draw(playerSprite);
		window.display();

	}
	return 0;
}

