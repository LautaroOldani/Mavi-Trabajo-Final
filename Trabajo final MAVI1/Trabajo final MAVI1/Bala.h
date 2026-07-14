#pragma once
#include <SFML/Graphics.hpp>

class Bala {
private:
    sf::CircleShape shape;
    sf::Vector2f direccion;
    float velocidad;

public:
    Bala(sf::Vector2f posicion, sf::Vector2f direccion);

    void actualizar(float deltaTime);
    void dibujar(sf::RenderWindow& window);

    sf::FloatRect getBounds();
};

