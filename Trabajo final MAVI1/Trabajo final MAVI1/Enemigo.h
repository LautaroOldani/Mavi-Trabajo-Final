#pragma once
#include <SFML/Graphics.hpp>

class Enemigo {

private:
    sf::Sprite sprite;

    float velocidad;
    float aceleracion;
    bool yendoDerecha;

public:

    
    Enemigo(sf::Texture& textura, sf::Vector2f posicion);

    void actualizar(float deltaTime);

    void dibujar(sf::RenderWindow& window);

    sf::FloatRect getBounds();
};