#ifndef _GRAPHICS_FIELD_
#define _GRAPHICS_FIELD_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Noise.cpp"
#include "Animals.cpp"
#include "DrawRules.cpp"
#include "MinerSructers.cpp"

#define _DEFOULT_SIZE_LETTERS_ 30
#define _DEFOULT_SIZE_HEADING_ 45

#define MenuColorsBackground RGB(221,200,95)
#define MenuColorsParts RGB(0,115,16)
#define MenuColorsDecor RGB(69,164,35)

#define _DEFOULT_RES_X_ 1800
#define _DEFOULT_RES_Y_ 900
#define _ZERO_X_OR_Y_POS_ 00
#define _MENU_SIZE_ 1000

#define _DEFOULT_BACKROUND_ "background.jpg"
#define _LOGO_ "logo.jpg"

#define X 60
#define Y 120
#define GridScale 20



typedef long double ld;
typedef long long int lli;


class graphicsLive {

public:
	graphicsLive(int resX, int resY, std::string Name) : window(sf::VideoMode(resX, resY), Name, sf::Style::Close), ScaleX((ld)resX / _DEFOULT_RES_X_), ScaleY((ld)resY / _DEFOULT_RES_Y_) {}
	graphicsLive(int resX, int resY) : window(sf::VideoMode(resX, resY), "LifeDisplay", sf::Style::Close), ScaleX((ld)resX / _DEFOULT_RES_X_), ScaleY((ld)resY / _DEFOULT_RES_Y_) {}
	graphicsLive() :window(sf::VideoMode(_DEFOULT_RES_X_, _DEFOULT_RES_Y_), "LifeDisplay", sf::Style::Close), ScaleX(1), ScaleY(1) {}

	sf::RenderWindow window;
	sf::RenderWindow* cons = new sf::RenderWindow(sf::VideoMode(1000, 1000), "The Consol", sf::Style::Close);
	ld ScaleX, ScaleY;

	void setField(ld** f) {
		CreateMenu();
		setbackground();
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				DrawAnimal(i, j, f);
			}
		}

		window.setFramerateLimit(60);
		window.display();

		while (window.isOpen())
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
		}
	}

	void CreateMenu()
	{
		sf::Font font;

		font.loadFromFile("arial.ttf");
		(*cons).clear(sf::Color::White);
		(*cons).setFramerateLimit(60);

		sf::Texture texture;
		texture.loadFromFile(_LOGO_);

		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(_ZERO_X_OR_Y_POS_, _ZERO_X_OR_Y_POS_);


		CreateRectangle(_ZERO_X_OR_Y_POS_, _ZERO_X_OR_Y_POS_, _MENU_SIZE_, _MENU_SIZE_, MenuColorsBackground.r, MenuColorsBackground.g, MenuColorsBackground.b); //ôîí
		CreateRectangle(_ZERO_X_OR_Y_POS_, _ZERO_X_OR_Y_POS_, 100, 100, MenuColorsBackground.r, MenuColorsBackground.g, MenuColorsBackground.b);

		(*cons).draw(sprite); // ëîãî

		CreateRectangle(100, 120, 850, 72, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // ôîí íàäïèñè èíôîðìàöèÿ î ïîëå
		CreateRectangle(100, 500, 850, 72, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // ôîí íàäïèñè ðåæèìû
		CreateRectangle(527, 600, 20, 500, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // ðàçäåëèòåëüíàÿ ïàëêà ðåæèìîâ
		CreateRectangle(_ZERO_X_OR_Y_POS_, 100, 100, 900, MenuColorsDecor.r, MenuColorsDecor.g, MenuColorsDecor.b); // áîëüøàÿ ïëàøêà ïîä ëîãî
		CreateRectangle(100, _ZERO_X_OR_Y_POS_, 900, 100, MenuColorsDecor.r, MenuColorsDecor.g, MenuColorsDecor.b); // áîëüøàÿ ïëàøêà ñïðàâà îò ëîãî
		CreateRectangle(332.5, 20, 435, 55, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // ôîí íàäïèñè ìåíþ
		CreateRectangle(100, 680, 340, 72, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // Êíîïêà Space (ïðîáåë)
		CreateRectangle(100, 780, 340, 110, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // the number of evolution steps performed 1
		CreateRectangle(590, 680, 120, 72, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // ðàç â ñåêóíäó
		CreateRectangle(606, 780, 340, 110, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // the number of evolution steps performed 2
		CreateRectangle(120, 227, 270, 240, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // ïëàøêà ñ èíôîðìàöèåé î ïîëå ëåâàÿ




		CreateRound(180, -30, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // âåðõíèé ëåâûé êðóã
		CreateRound(850, -30, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // âåðõíèé ïðàâûé êðóã
		CreateRound(-30, 122, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // êðóã Information about field
		CreateRound(-30, 505, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // êðóã Modes
		CreateRound(-30, 880, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // íèæíèé ëåâûé êðóã
		CreateRound(911, 120, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðóãëåíèå Information about field
		CreateRound(911, 500, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðóãëåíèå Modes
		CreateRound(408, 680, 36.5, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðóãëåíèå Êíîïêà Space (ïðîáåë)
		CreateRound(390, 780, 55.4, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðóãëåíèå ïðàâî the number of evolution steps performed 1
		CreateRound(255, 900, 38, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // 3
		CreateRound(680, 680, 36.6, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðãóãëåíèå ðàç â ñåêóíäó ïðàâî
		CreateRound(560, 680, 36.6, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðãóãëåíèå ðàç â ñåêóíäó âëåâî
		CreateRound(770, 680, 36.6, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // 3
		CreateRound(550, 780, 55.4, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðóãëåíèå ëåâî the number of evolution steps performed 2
		CreateRound(887, 780, 55.4, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // çàêðóãëåíèå ïðàâî the number of evolution steps performed 2
		CreateRound(734, 900, 38, MenuColorsParts.r, MenuColorsParts.g, MenuColorsParts.b); // 3

		CreateStaticText(495, 20, _DEFOULT_SIZE_HEADING_, font, "Menu"); //
		CreateStaticText(315, 123, _DEFOULT_SIZE_HEADING_, font, "Information about field"); //
		CreateStaticText(465, 500, _DEFOULT_SIZE_HEADING_, font, "Modes"); //
		CreateStaticText(155, 685, _DEFOULT_SIZE_HEADING_, font, "Button Space"); //
		CreateStaticText(103, 795, 35, font, "The number of evolution\n      steps performed"); //
		CreateStaticText(569.5, 698, 27, font, "Times per sec"); //
		CreateStaticText(585, 795, 35, font, "The number of evolution\n       steps performed"); //

		CreateDinamicText(130, 242, _DEFOULT_SIZE_HEADING_, font, "Wolf: ", 1234); // äóðà÷îê äîëæåí äàòü ññûëêó íà ïîëå 
		CreateDinamicText(130, 292, _DEFOULT_SIZE_HEADING_, font, "Bunny: ", 1234); // äóðà÷îê äîëæåí äàòü ññûëêó íà ïîëå 
		CreateDinamicText(130, 342, _DEFOULT_SIZE_HEADING_, font, "Grass: ", 1234); // äóðà÷îê äîëæåí äàòü ññûëêó íà ïîëå 
		CreateDinamicText(130, 392, _DEFOULT_SIZE_HEADING_, font, "Air: ", 1234); // äóðà÷îê äîëæåí äàòü ññûëêó íà ïîëå 

		


		CreateButton(0,0,0,0, 100, 50, font, "BIG", 25);


		(*cons).display();
	}


	void CreateButton(int x_text, int y_text, int x_button, int y_button, int len, int widht, sf::Font font, std::string str, int lettersize)
	{
		sf::Text buttonText;
		buttonText.setFont(font);
		buttonText.setCharacterSize(lettersize);
		buttonText.setString(str);
		buttonText.setFillColor(sf::Color::Black);
		buttonText.setPosition(x_text, y_text);

		sf::RectangleShape button(sf::Vector2f(len, widht));
		button.setFillColor(sf::Color::Green);
		button.setPosition(x_button, y_button);
		(*cons).draw(button);
		(*cons).draw(buttonText);
	}

	void CreateDinamicText(int x, int y, int lettersSize, sf::Font font, std::string str, int amountAnimals)
	{
		sf::Text menu("", font, 0);
		std::string laststr = str + std::to_string(amountAnimals);
		menu.setString(laststr);
		menu.setFont(font);
		menu.setCharacterSize(lettersSize);
		menu.setPosition(x, y);
		menu.setFillColor(sf::Color::White);

		(*cons).draw(menu);
	}

	void CreateStaticText(int x, int y, int lettersSize, sf::Font font, std::string str)
	{
		sf::Text menu("", font, 0);
		menu.setString(str);
		menu.setFont(font);
		menu.setCharacterSize(lettersSize);
		menu.setPosition(x, y);
		menu.setFillColor(sf::Color::White);


		(*cons).draw(menu);
	}

	void CreateRectangle(int x, int y, int len, int width, short r, short g, short b)
	{
		sf::RectangleShape rectangle(sf::Vector2f(len, width));
		rectangle.setPosition(x, y);
		rectangle.setFillColor(sf::Color(r, g, b));
		(*cons).draw(rectangle);
	}

	void CreateRound(int x, int y, int rad, short r, short g, short b)
	{
		sf::CircleShape circle(rad);
		circle.setPosition(x, y);
		circle.setFillColor(sf::Color(r, g, b));
		(*cons).draw(circle);
	}

	void setbackground()
	{
		sf::Texture texture;
		texture.loadFromFile(_DEFOULT_BACKROUND_);
		sf::Sprite sprite;
		sprite.setTexture(texture);
		window.draw(sprite);
	}

	void DrawAnimal(const int& x, const int& y, long double**& field) {

		if (field[x][y] == 1 || field[x][y] == -1) { return; }

		if (field[x][y] > 0.5) {
			setSquar(x, y, Grass);
		}
		else if (field[x][y] <= 0.5 && field[x][y] > -0.5) {
			setSquar(x, y, Wolf);
		}
		else {
			setSquar(x, y, Bunny);
		}
	}

	void setSquar(const int& x, const int& y, const AnimalsSpecies& Name) {

		sf::RectangleShape square;
		DrawInfoNode infoNode = DrawInfo.getV(Name);

		square.setSize(sf::Vector2f(infoNode.size * ScaleX, infoNode.size * ScaleY));
		square.setFillColor(sf::Color(infoNode.rgb.r, infoNode.rgb.g, infoNode.rgb.b));
		square.setPosition(y * GridScale * ScaleY, x * GridScale * ScaleX);
		square.setOutlineThickness(0.6);
		square.setOutlineColor(sf::Color::Black);
		window.draw(square);
	}
};

#endif