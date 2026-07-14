#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Enemigo.h"
#include "Bala.h"
#include "HUD.h"

enum EstadoJuego {
    MENU,
    JUGANDO,
    GAMEOVER
};

class Juego {

private:

    // =========================
    // ESTADO DE LA PARTIDA
    // =========================
    EstadoJuego estadoActual = MENU;
    sf::Text textoMenu;

    // =========================
    // VENTANA Y RECURSOS GRAFICOS
    // =========================
    sf::RenderWindow window;

    sf::Texture texturaEnemigo;
    sf::Texture texturaFondo;

    sf::Sprite spriteFondo;

    // =========================
    // ENTIDADES DEL JUEGO
    // =========================
    std::vector<Enemigo> enemigos;
    std::vector<Bala> balas;

    HUD hud;

    sf::RectangleShape jugador;

    // =========================
    // CONTROL DE DISPARO Y SPAWN
    // =========================
    float tiempoDisparo = 0.0f;
    float cooldown = 0.3f;

    float tiempoSpawn = 0.0f;
    float delaySpawn = 1.5f;

    // =========================
    // PROGRESO DE LA PARTIDA
    // =========================
    int enemigosMaximos = 1;
    int enemigosMatados = 0;

    float tiempoRestante = 30.0f;

    bool juegoTerminado = false;
    bool victoria = false;

    // =========================
    // INTERFAZ Y MENSAJES
    // =========================
    sf::Font font;
    sf::Text textoFinal;

    // =========================
    // AUDIO
    // =========================
    sf::Music musicaFondo;

    sf::SoundBuffer bufferDisparo;
    sf::Sound sonidoDisparo;

    sf::SoundBuffer bufferMuerte;
    sf::Sound sonidoMuerte;

public:

    Juego();

    void ejecutar();

    void reiniciarJuego();
};