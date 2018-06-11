#include <SFML/Graphics.hpp>
#include "map.h"
#include "View.h"
#include <sstream>
#include "mission.h"
#include <iostream>

using namespace std;
using namespace sf;

static int countLvl;
class Player {

public:
	float x, y;
	float w, h, dx, dy, speed;
	int dir, health, playerScore;
	String File;
	Image image; Texture texture; Sprite sprite;
	bool life;
	Player(String F, float X, float Y, float W, float H) {
		dx = 0; dy = 0; speed = 0; dir = 0; health = 1000; countLvl = 0; playerScore = 0; life = true;
		File = F; w = W; h = H;
		image.loadFromFile("Images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;  // Координаты появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));

	}
	void update(float time) {
		switch (dir)
		{
		case 0: dy = speed;  dx = speed;  break;  // Down
		case 1: dy = -speed;  dx = speed; break; // Up
		case 2: dy = 0; dx = speed;  break; // Nothing
		}
		x += dx*time;
		y += dy*time;
		sprite.setPosition(x, y);
		interactionWithMap();

		if (health <= 0) {
			life = false; speed = 0;
		}
	}

	void interactionWithMap()//ф-ция взаимодействия с картой
	{			
		try {
			for (int i = y / 32; i < (y + h - 20) / 32; i++) //проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			{
				for (int j = x / 32; j < (x + w - 15) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
				{
					switch (TileMap[i][j])
					{
					case '0': { // border
						if (dy > 0) {
							y = i * 32 - h;
						}
						if (dy < 0) {
							y = i * 32 + 32;
						}
						break;
					}

					case 'f': { // flowers
						playerScore++;
						TileMap[i][j] = ' '; break;
					}
					case 'h': { //healths
						health += 25;
						TileMap[i][j] = ' '; break;
					}
					case 's': { // stone
						health -= 25;
						TileMap[i][j] = ' ';
						break;
					}
					case 'e': { // portal
						countLvl++;
						x = 15, y = 180;
						view.reset(sf::FloatRect(-150, -50, 1200, 650));
						switch (countLvl)
						{
						case 1: {
							for (size_t i = 0; i < HEIGHT_MAP; i++)
							{
								TileMap[i] = TileMapLvl1[i];
							} break;
						}
						case 2: {
							for (size_t i = 0; i < HEIGHT_MAP; i++)
							{
								TileMap[i] = TileMapLvl2[i];
							}break;
						}
						case 3: {
							for (size_t i = 0; i < HEIGHT_MAP; i++)
							{
								TileMap[i] = TileMapLvl3[i];
							}break;
						}
						}
					}
					}
				}
			}
		}
			catch (...) 
			{

			}
		}


		float getplayercoordinateX() {
			return x;
		}
		float getplayercoordinateY() {
			return y;
		}
	};


	int main() {
		RenderWindow window(VideoMode(1920, 1080), "Super Runner", Style::Fullscreen);
		view.reset(sf::FloatRect(-150, -50, 1200, 650));
		Clock clock;
		float CurrentFrame = 0; // Текущий кадр( для скорости анимации)
		Player p("hero.png", 15, 180, 60, 100);

		Texture backgroundTexture; Sprite backgroundSprite;
		backgroundTexture.loadFromFile("images/background.png");
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setScale(4, 4);
		backgroundSprite.setPosition(-200, -200);

		Image map_image;
		map_image.loadFromFile("images/map.png");
		Texture map;
		map.loadFromImage(map_image);
		Sprite s_map;
		s_map.setTexture(map);

		Font font;
		font.loadFromFile("images/CyrilicOld.ttf");
		Text text("", font, 30);

		Clock gameTimeClock;
		int gameTime = 0;

		randomMapGenerate();

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
			clock.restart();
			time = time / 800;

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
					window.close();

			}


			// ПЕРЕДВИЖЕНИЕ		

			if (p.life) {
				if (Keyboard::isKeyPressed(Keyboard::M)) {
					p.health = 10000; countLvl++;
				}

				backgroundSprite.move(-0.01 * time, 0);
				view.move(0.2*time, 0);
				p.dir = 2; p.speed = 0.2;
				p.sprite.move(p.speed*time, 0); // Right
				CurrentFrame += 0.008*time;
				if (CurrentFrame > 6) CurrentFrame -= 6;
				p.sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 60, 100));

				if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
					p.dir = 1; p.speed = 0.2;
					CurrentFrame += 0.004*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
					if (CurrentFrame > 6) CurrentFrame -= 6; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
					p.sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 60, 100)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
					p.sprite.move(0, -0.5*time);//происходит само движение персонажа вверх
				}
				if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
					p.dir = 0;  p.speed = 0.2;
					CurrentFrame += 0.004*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
					if (CurrentFrame > 6) CurrentFrame -= 6; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
					p.sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 0, 60, 100)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
					p.sprite.move(0, 0.5*time);//происходит само движение персонажа вниз
				}
			}
			else {

				s_map.setColor(Color::Red);
				view.move(0, 0);
				backgroundSprite.setColor(Color::Red);
				text.setScale(2, 2);

				if (Keyboard::isKeyPressed(Keyboard::R)) {
					p.x = 15, p.y = 180;
					view.reset(sf::FloatRect(-150, -50, 1200, 650));
					gameTimeClock.restart();
					p.life = true; p.health = 100; p.speed = 0.2;
					p.playerScore = 0; gameTime = 0;
					backgroundSprite.getColor();
					view.move(0.2*time, 0); text.setScale(1, 1);
					s_map.setColor(Color::White);
					backgroundSprite.setColor(Color::White);

					for (size_t i = 0; i < HEIGHT_MAP; i++)
					{
						TileMap[i] = TileMapBackUp[i];
					}
				}
			}
			p.update(time);


			// ОTРИСОВКА
			window.setView(view);
			window.clear();
			window.draw(backgroundSprite);
			/////////////////////////////Рисуем карту///////////////////
			if (countLvl == 0) {
				for (int i = 0; i < HEIGHT_MAP; i++)
					for (int j = 0; j < WIDTH_MAP; j++)
					{
						s_map.move(-0.15*time, 0);
						if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
						if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
						if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
						if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
						if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
						if ((TileMap[i][j] == 'e')) s_map.setTextureRect(IntRect(160, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
						s_map.setPosition(j * 32, (i * 32));//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

						window.draw(s_map);//рисуем квадратики на экран
					}
			}
			if (countLvl == 1) {
				for (int i = 0; i < HEIGHT_MAP; i++)
					for (int j = 0; j < WIDTH_MAP; j++)
					{
						s_map.move(-0.15*time, 0);
						if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(192, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
						if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(224, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
						if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(256, 0, 32, 32));
						if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(288, 0, 32, 32));
						if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(320, 0, 32, 32));
						if ((TileMap[i][j] == 'e')) s_map.setTextureRect(IntRect(352, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
						s_map.setPosition(j * 32, (i * 32));//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

						window.draw(s_map);//рисуем квадратики на экран
					}
			}
			if (countLvl == 2) {
				for (int i = 0; i < HEIGHT_MAP; i++)
					for (int j = 0; j < WIDTH_MAP; j++)
					{
						s_map.move(-0.15*time, 0);
						if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(384, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
						if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(416, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
						if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(448, 0, 32, 32));
						if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(480, 0, 32, 32));
						if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(512, 0, 32, 32));
						if ((TileMap[i][j] == 'e')) s_map.setTextureRect(IntRect(544, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
						s_map.setPosition(j * 32, (i * 32));//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

						window.draw(s_map);//рисуем квадратики на экран
					}
			}
			if (countLvl == 3) {
				for (int i = 0; i < HEIGHT_MAP; i++)
					for (int j = 0; j < WIDTH_MAP; j++)
					{
						s_map.move(-0.15*time, 0);
						if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(576, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
						if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(608, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
						if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(640, 0, 32, 32));
						if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(672, 0, 32, 32));
						if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(704, 0, 32, 32));
						if ((TileMap[i][j] == 'e')) s_map.setTextureRect(IntRect(736, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
						s_map.setPosition(j * 32, (i * 32));//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

						window.draw(s_map);//рисуем квадратики на экран
					}
			}


			text.setPosition(view.getCenter().x - 575, view.getCenter().y - 280);
			text.setStyle(Text::Bold | Text::Underlined);
			ostringstream playerScoreString; ostringstream playerTimeString; ostringstream playerHealthString;
			playerScoreString << p.playerScore; playerTimeString << gameTime; playerHealthString << p.health;
			text.setString("Очки: " + playerScoreString.str() + +"    Жизни: " + playerHealthString.str() + "    Время: " + playerTimeString.str());

			window.draw(text);
			window.draw(p.sprite);
			window.display();
		}

		return 0;
	}