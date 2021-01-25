#include "Licytacja.h"

/*
* Konstruktor obiektu, klasy Licytacja
*/
Licytacja::Licytacja():
	licytujeZa(0),
	minLicytacja(100),
	ktoraKolej(0),
	czyStart(true),
	czyMogePass(false)
{
	if (!font.loadFromFile("sansation.ttf")) {
		std::cout << "Nie udalo sie pobrac czcionki";
	}
	for (int i = 0; i < 5; i++) {
		licytacjaUzyte[i] = -1;
	}
	/*
	* Nadawanie w�a�ciwo�ci wielko�ci licytacji
	*/
	for (int i = 0; i < 5; i++) {
		licytacja[i].setFont(font);
		licytacja[i].setFillColor(sf::Color::Yellow);
		licytacja[i].setCharacterSize(32);
		licytacja[i].setPosition(sf::Vector2f(150.0f, 250.0f + (50.0f * i)));
	}
	licytacja[0].setString("PASS");
	licytacja[1].setString("100");
	licytacja[2].setString("110");
	licytacja[3].setString("120");
	licytacja[4].setString("130");

	poleLicytacja.setSize(sf::Vector2f(150.0f, 50.0f));
	poleLicytacja.setFillColor(sf::Color::Blue);
	poleLicytacja.setOrigin(sf::Vector2f(poleLicytacja.getGlobalBounds().width / 2, poleLicytacja.getGlobalBounds().height / 2));
	poleLicytacja.setPosition(sf::Vector2f(licytacja[0].getPosition().x + 50.0f, licytacja[0].getPosition().y + 10.0f));

}

Licytacja::~Licytacja() {}

/*
* Metoda wy�wietlaj�ca licytacj�
*/
void Licytacja::draw(sf::RenderWindow& window) {
	window.draw(poleLicytacja);
	for (int i = 0; i < 5; i++) {
		window.draw(licytacja[i]);
	}
}
/*
* Wybranie nast�pnej warto�ci licytacji, podczas licytacji.
*
* Podobnie jak przy ruchu prawo-lewo, je�eli znacznik znajduje si� na skrajnie dolnym obiekcie,
* to znacznik zostanie przeniesiony na skrajnie g�rny.
*/
void Licytacja::wDol() {
	if (opcja < 4) {
		opcja++;
		poleLicytacja.setPosition(sf::Vector2f(licytacja[opcja].getPosition().x + 50.0f, licytacja[opcja].getPosition().y + 10.0f));
	}
	else {
		opcja = 0;
		poleLicytacja.setPosition(sf::Vector2f(licytacja[opcja].getPosition().x + 50.0f, licytacja[opcja].getPosition().y + 10.0f));
	}
};

/*
* Wybranie nast�pnej warto�ci licytacji, podczas licytacji.
*
* Podobnie jak przy ruchu prawo-lewo, je�eli znacznik znajduje si� na skrajnie gr�rnym obiekcie,
* to znacznik zostanie przeniesiony na skrajnie dolny.
*/
void Licytacja::wGore() {
	if (opcja > 0) {
		opcja--;
		poleLicytacja.setPosition(sf::Vector2f(licytacja[opcja].getPosition().x + 50.0f, licytacja[opcja].getPosition().y + 10.0f));
	}
	else {
		opcja = 4;
		poleLicytacja.setPosition(sf::Vector2f(licytacja[opcja].getPosition().x + 50.0f, licytacja[opcja].getPosition().y + 10.0f));
	}
};

/*
* Metoda, kt�ra licytuje wybran� wielko�� wyznaczon� przez gracza
*/
void Licytacja::licytuj() {
	ktoraKolej++;
	/*
	* Ustalenie warto�ci licytacji jako u�ytej, niemo�liwej do ponownego zalicytowania w tej samej rundzie, 
	* wyj�tkiem jest PASS, po kt�rego wybraniu nie bierzemy udzia�u w licytacji
	*/
	if (opcja == 0) {
		licytacjaUzyte[opcja] = -1;
	}
	else
		licytacjaUzyte[opcja] = opcja;
	std::cout <<"Opcja:  "<<opcja << std::endl;
	switch (opcja) {
		case 0:
			licytujeZa = -1;
			if (czyMogePass == false) {
				licytujeZa = 100;
				licytacja[1].setFillColor(sf::Color::Red);
			}
			else {
				for (int i = 1; i < 5; i++) {
					licytacjaUzyte[i] = i;
					licytacja[i].setFillColor(sf::Color::Red);
				}
				std::cout << "Pass" << std::endl;
			}
			break;
		case 1:
			if (minLicytacja <= 100) {
				for (int i = 1; i < 2; i++) {
					licytacjaUzyte[i] = i;
					licytacja[i].setFillColor(sf::Color::Red);
				}
				licytujeZa = 100;
			}
			break;
		case 2:
			if (minLicytacja < 110) {
				for (int i = 1; i < 3; i++) {
					licytacjaUzyte[i] = i;
					licytacja[i].setFillColor(sf::Color::Red);
				}
				licytujeZa = 110;
			}
			break;
		case 3:
			if (minLicytacja < 120) {
				for (int i = 1; i < 4; i++) {
					licytacjaUzyte[i] = i;
					licytacja[i].setFillColor(sf::Color::Red);
				}
				licytujeZa = 120;
			}
			break;
		case 4:
			if (minLicytacja < 130) {
				for (int i = 1; i < 5; i++) {
					licytacjaUzyte[i] = i;
					licytacja[i].setFillColor(sf::Color::Red);
				}
				licytujeZa = 130;
			}
			break;
		default:
			break;
		}
	/*
	* Zmiana warto�ci pierwszej licytacji, jezeli gracz sterowany przez osob� by� pierwszy
	*/
	czyStart = false;
	czyMogePass = true;
	minLicytacja = licytujeZa;
	std::cout << licytujeZa << std::endl;
}

/*
* Metoda licytuj�ca warto�ci gracza niesterowanego przez osob�
*/
int Licytacja::licytujBot(Karta kartyBota[]) {
	ktoraKolej++;
	int as{};
	/*
	* Wielko�� licytacji jest okre�lana za pomoc� ilo�ci as�w (karta daj�ca najwi�cej punkt�w) w talii gracza.
	*/
	for (int i = 0; i < 8; i++) {
		if (kartyBota[i].figura == "A")
			as++;
	}
	std::cout <<"Czy start boty: "<< std::boolalpha << czyStart << std::endl;
	/*
	* Sprawdzane jest czy minimalna warto�� licytacji jest mniejsza ni� ta, za kt�r� gracz mo�e zalicytowa�
	* Je�eli tak to licytuje, tym samym podnosz�c minimum jakie musi zosta� wylicytowane, eliminuj�c powtarzanie si� warto�ci w partii
	*/
	if (czyStart == true) {
		minLicytacja = 100;
		czyStart = false;
		return 100;
	}
	else if (as <= 1 && minLicytacja < 110) {
		licytacja[2].setFillColor(sf::Color::Red);
		licytacjaUzyte[2] = 2;
		minLicytacja = 110;
		licytacja[1].setFillColor(sf::Color::Red);
		licytacjaUzyte[1] = 1;
		return 110;
	}
	else if(as >= 2 && minLicytacja < 120) {
		licytacja[3].setFillColor(sf::Color::Red);
		minLicytacja = 120;
		licytacjaUzyte[3] = 3;
		licytacja[2].setFillColor(sf::Color::Red);
		licytacjaUzyte[2] = 2;
		licytacja[1].setFillColor(sf::Color::Red);
		licytacjaUzyte[1] = 1;
		return 120;
	}
	else {
		return -1;
	}
	/*
	* Zmiana warto�ci pierwszej licytacji, jezeli gracz sterowany przez osob� by� pierwszy
	*/
	czyStart = false;
	czyMogePass = true;
}

/*
* Metoda resetuj�ca ustawiania licytacji, umo�liwiaj�ca ponowne licytowanie w nast�pnej partii lub podczas resetu
*/
void Licytacja::reset() {
	for (int i = 0; i < 5; i++) {
		licytacjaUzyte[i] = -1;
		licytacja[i].setFillColor(sf::Color::Yellow);
		licytujeZa = 0;
		minLicytacja = 100;
		ktoraKolej = 0;
		czyStart = true;
	}
}
void Licytacja::resetKolei() {
		ktoraKolej = 0;
}

/*
* Metody tzw. gettery, pozwalaj�ce na wyci�ganie warto�ci prywatnych z clasy Licytacja,
* potrzebnych do dzia�ania gry
*/
int Licytacja::getOpcja() {
	return opcja;
}
int Licytacja::getLicytacjaUzyte() {
	return licytacjaUzyte[opcja];
}
int Licytacja::getLicytujeZa() {
	return licytujeZa;
}
int Licytacja::getMinLicytacja() {
	return minLicytacja;
}
bool Licytacja::getCzyStart() {
	return czyStart;
}