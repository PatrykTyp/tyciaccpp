#include "Zasady.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>


/*
* Konstruktor Zasady
*/
Zasady::Zasady() {
	texture.loadFromFile("image/zasady.png");

	view.setSize(sf::Vector2f(1200.0f, 800.0f));
	view.setCenter(sf::Vector2f(600.0f, 400.0f));

	tlo.setTexture(texture);

	font.loadFromFile("sansation.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);

	WypiszZasady();
}

Zasady::~Zasady() {}

/*
* Poruszanie si� po oknie Zasady za pomoc� scrolla
* W g�r� 
* i w d�
*/
void Zasady::ScrollWGore() {
	if (view.getCenter().y > 400.0f)
	view.move(sf::Vector2f(0, -25.0f));
}

void Zasady::ScrollWDol() {
	if(view.getCenter().y < 1200.0f)
	view.move(sf::Vector2f(0, 25.0f));
}

/*
* Resetowanie widoku okna na domy�ln�
*/
void Zasady::ScrollReset() {
	float tmp = -(view.getCenter().y - 400.0f);
	view.move(sf::Vector2f(0, tmp));
}

/*
* Rysowanie t�a i obiekt�w Zasady
*/
void Zasady::draw(sf::RenderWindow& window) {
	window.setView(view);
	window.draw(tlo);
	window.draw(text);
}

/*
* Metoda, kt�ra wczytuje na ekran zapisany w pliku tekst z zasadmi dotycz�cymi gry
*/
void Zasady::WypiszZasady() {
	std::string linijki;
	std::ifstream zasadyPlik;
	std::string zasadyText;
	zasadyPlik.open("zasady.txt");
	if (zasadyPlik){
		while (std::getline(zasadyPlik,linijki)){
			zasadyText += linijki + "\n";
		}
	}
	else {
		std::cout << "Nie udalo sie otworzyc pliczku";
	}
	text.setString(zasadyText);
	text.setCharacterSize(25);
	text.setPosition(15.0f, 15.0f);
}