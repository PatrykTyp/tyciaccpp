#include "Zasady.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Zasady::Zasady() {
	texture.loadFromFile("image/zasady.png");
	view.setSize(sf::Vector2f(1200.0f, 800.0f));
	view.setCenter(sf::Vector2f(600.0f, 400.0f));
	tlo.setTexture(texture);
}

Zasady::~Zasady() {}

void Zasady::ScrollWGore() {
	if (view.getCenter().y > 400.0f)
	view.move(sf::Vector2f(0, -25.0f));
}

void Zasady::ScrollWDol() {
	if(view.getCenter().y < 1200.0f)
	view.move(sf::Vector2f(0, 25.0f));
}
void Zasady::ScrollReset() {
	float tmp = -(view.getCenter().y - 400.0f);
	view.move(sf::Vector2f(0, tmp));
}

void Zasady::draw(sf::RenderWindow& window) {
	window.setView(view);
	window.draw(tlo);
}