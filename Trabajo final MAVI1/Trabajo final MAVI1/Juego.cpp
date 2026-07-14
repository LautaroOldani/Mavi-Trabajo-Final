#include "Juego.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

Juego::Juego()
    : window(sf::VideoMode(1280, 720), "Juego")
{
    srand(time(NULL));

    // =========================
    // 🔵 FONDO
    // =========================
    texturaFondo.loadFromFile("Assets/Estanque.png");

    spriteFondo.setTexture(texturaFondo);

    spriteFondo.setScale(
        1280.f / spriteFondo.getTexture()->getSize().x,
        720.f / spriteFondo.getTexture()->getSize().y
    );

    // =========================
    // 🟥 JUGADOR
    // =========================
    jugador.setSize(sf::Vector2f(80, 20));

    jugador.setFillColor(sf::Color::Red);

    jugador.setPosition(600, 660);

    // =========================
    // 🦆 ENEMIGO
    // =========================
    texturaEnemigo.loadFromFile("Assets/Pato.png");

    // =========================
    // 🔤 FUENTE
    // =========================
    font.loadFromFile("Assets/arial.ttf");

    textoFinal.setFont(font);
    textoFinal.setCharacterSize(50);
    textoFinal.setFillColor(sf::Color::White);
    textoFinal.setPosition(300, 300);

    textoMenu.setFont(font);
    textoMenu.setCharacterSize(50);
    textoMenu.setFillColor(sf::Color::White);
    textoMenu.setPosition(250, 250);

    textoMenu.setString(
        "Duck Hunt\n\n"
        "Mata 15 patos antes\n"
        "de que se acabe el tiempo\n"
        "para ganar\n\n"
        "ENTER para jugar\n"
        "ESC para salir"
    );

    // =========================
    // 🔊 AUDIO
    // =========================

    musicaFondo.openFromFile("Assets/Audios/MusicaFondo.Wav");
    musicaFondo.setLoop(true);
    musicaFondo.setVolume(40.f);
    musicaFondo.play();

    bufferDisparo.loadFromFile("Assets/Audios/Disparo.Wav");
    sonidoDisparo.setBuffer(bufferDisparo);

    bufferMuerte.loadFromFile("Assets/Audios/MuertePato.Wav");
    sonidoMuerte.setBuffer(bufferMuerte);

    // =========================
    // 🐣 ENEMIGO INICIAL
    // =========================
    float x = 150 + rand() % (1050 - 150);
    float y = 180 + rand() % (350 - 180);

    enemigos.emplace_back(
        texturaEnemigo,
        sf::Vector2f(x, y)
    );
}

void Juego::reiniciarJuego()
{
    enemigos.clear();
    balas.clear();

    enemigosMatados = 0;
    enemigosMaximos = 1;

    tiempoRestante = 30.0f;

    juegoTerminado = false;
    victoria = false;

    tiempoSpawn = 0.0f;
    tiempoDisparo = 0.0f;

    float x = 150 + rand() % (1050 - 150);
    float y = 180 + rand() % (350 - 180);

    enemigos.emplace_back(
        texturaEnemigo,
        sf::Vector2f(x, y)
    );
}

void Juego::ejecutar()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter
                    && estadoActual == MENU)
                {
                    estadoActual = JUGANDO;
                }

                if (event.key.code == sf::Keyboard::R
                    && estadoActual == GAMEOVER)
                {
                    reiniciarJuego();
                    estadoActual = JUGANDO;
                }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // =========================
        // ⏱️ TIMER
        // =========================
        if (estadoActual == JUGANDO && !juegoTerminado)
        {
            tiempoRestante -= deltaTime;

            if (tiempoRestante <= 0)
            {
                juegoTerminado = true;
                victoria = false;
                estadoActual = GAMEOVER;
            }

            if (enemigosMatados >= 15)
            {
                juegoTerminado = true;
                victoria = true;
                estadoActual = GAMEOVER;
            }
        }

        tiempoDisparo += deltaTime;
        tiempoSpawn += deltaTime;

        // =========================
        // 🎮 GAMEPLAY
        // =========================
        if (estadoActual == JUGANDO && !juegoTerminado)
        {
            // 🔫 DISPARO
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
                && tiempoDisparo >= cooldown)
            {
                sf::Vector2f playerPos(
                    jugador.getPosition().x + 40,
                    jugador.getPosition().y
                );

                sf::Vector2f mousePos =
                    window.mapPixelToCoords(
                        sf::Mouse::getPosition(window)
                    );

                sf::Vector2f direccion = mousePos - playerPos;

                float length = sqrt(
                    direccion.x * direccion.x +
                    direccion.y * direccion.y
                );

                direccion /= length;

                balas.emplace_back(playerPos, direccion);

                sonidoDisparo.play();

                tiempoDisparo = 0.0f;
            }

            // 🐣 SPAWN
            if (enemigos.size() < enemigosMaximos
                && tiempoSpawn >= delaySpawn)
            {
                float x = 150 + rand() % (1050 - 150);
                float y = 180 + rand() % (350 - 180);

                enemigos.emplace_back(
                    texturaEnemigo,
                    sf::Vector2f(x, y)
                );

                tiempoSpawn = 0.0f;
            }

            // 🔄 ENEMIGOS
            for (int i = 0; i < enemigos.size(); i++)
                enemigos[i].actualizar(deltaTime);

            // 🔄 BALAS
            for (int i = 0; i < balas.size(); i++)
            {
                balas[i].actualizar(deltaTime);

                sf::FloatRect bounds = balas[i].getBounds();

                if (bounds.left > 1280 ||
                    bounds.left < 0 ||
                    bounds.top > 720 ||
                    bounds.top < 0)
                {
                    balas.erase(balas.begin() + i);
                    i--;
                }
            }

            // 💥 COLISIONES
            for (int i = 0; i < balas.size(); i++)
            {
                for (int j = 0; j < enemigos.size(); j++)
                {
                    if (balas[i].getBounds()
                        .intersects(enemigos[j].getBounds()))
                    {
                        enemigos.erase(enemigos.begin() + j);
                        balas.erase(balas.begin() + i);

                        enemigosMatados++;

                        sonidoMuerte.play();

                        if (enemigosMatados % 2 == 0
                            && enemigosMaximos < 5)
                        {
                            enemigosMaximos++;
                        }

                        i--;
                        break;
                    }
                }
            }
        }

        // =========================
        // HUD
        // =========================
        hud.actualizar(enemigosMatados, tiempoRestante);

        // =========================
        // DRAW
        // =========================
        window.clear();

        window.draw(spriteFondo);

        if (estadoActual == MENU)
        {
            window.draw(textoMenu);
        }

        if (estadoActual != MENU)
        {
            window.draw(jugador);

            for (int i = 0; i < enemigos.size(); i++)
                enemigos[i].dibujar(window);

            for (int i = 0; i < balas.size(); i++)
                balas[i].dibujar(window);

            hud.dibujar(window);
        }

        if (estadoActual == GAMEOVER)
        {
            if (victoria)
                textoFinal.setString("GANASTE\nPresione R para reiniciar");
            else
                textoFinal.setString("PERDISTE\nPresione R para reiniciar");

            window.draw(textoFinal);
        }

        window.display();
    }
}