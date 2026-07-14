#include "Enemigo.h"

Enemigo::Enemigo(sf::Texture& textura, sf::Vector2f posicion) {

    sprite.setTexture(textura);

    // posición recibida desde Juego.cpp
    sprite.setPosition(posicion);

    velocidad = 100.0f;

    aceleracion = 20.0f;

    yendoDerecha = true;
}

void Enemigo::actualizar(float deltaTime) {

    // MRUA
    velocidad += aceleracion * deltaTime;

    if (velocidad > 400.0f) {
        velocidad = 400.0f;
    }

    // movimiento
    if (yendoDerecha) {

        sprite.move(velocidad * deltaTime, 0);

        if (sprite.getPosition().x > 1080) {

            yendoDerecha = false;
        }
    }
    else {

        sprite.move(-velocidad * deltaTime, 0);

        if (sprite.getPosition().x < 100) {

            yendoDerecha = true;
        }
    }
}

void Enemigo::dibujar(sf::RenderWindow& window) {

    window.draw(sprite);
}

sf::FloatRect Enemigo::getBounds() {

    return sprite.getGlobalBounds();
}