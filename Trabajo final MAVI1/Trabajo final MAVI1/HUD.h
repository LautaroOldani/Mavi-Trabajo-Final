#pragma once
#include <SFML/Graphics.hpp>

class HUD {
private:
    sf::Font font;
    sf::Text textoEnemigos;

public:
    HUD();

    void actualizar(
        int enemigosMatados,
        float tiempoRestante
    );

    void dibujar(sf::RenderWindow& window);
};
