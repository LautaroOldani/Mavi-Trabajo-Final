#include "Bala.h"

Bala::Bala(sf::Vector2f posicion, sf::Vector2f dir) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(posicion);

    direccion = dir;
    velocidad = 400.0f;
}

void Bala::actualizar(float deltaTime) {
    shape.move(direccion * velocidad * deltaTime);
}

void Bala::dibujar(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Bala::getBounds() {
    return shape.getGlobalBounds();
}
