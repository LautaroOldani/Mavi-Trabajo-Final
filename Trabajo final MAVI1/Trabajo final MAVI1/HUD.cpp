#include "HUD.h"

HUD::HUD() {

    font.loadFromFile("Assets/arial.ttf");

    textoEnemigos.setFont(font);

    textoEnemigos.setCharacterSize(30);

    textoEnemigos.setFillColor(sf::Color::White);

    textoEnemigos.setPosition(20, 10);
}

void HUD::actualizar(
    int enemigosMatados,
    float tiempoRestante
) {

    textoEnemigos.setString(

        "Patos: " +
        std::to_string(enemigosMatados)

        +

        "\nTiempo: " +
        std::to_string((int)tiempoRestante)
    );
}

void HUD::dibujar(sf::RenderWindow& window) {

    window.draw(textoEnemigos);
}