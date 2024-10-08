#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "TILEMAP.cpp" // Incloem el fitxer de la capa de tiles

int main() {
    // Crear la finestra del joc
    sf::RenderWindow finestra(sf::VideoMode(512, 256), "Mapa de Tiles");

    // Preguntar a l'usuari quin fitxer de mapa carregar
    std::string fitxerMapa; // Variable per emmagatzemar el nom del fitxer
    std::cout << "Tria un fitxer de mapa (1 o 2):\n"; // Pregunta a l'usuari
    std::cout << "1. nivell1.txt\n"; // Opció 1
    std::cout << "2. nivell2.txt\n"; // Opció 2

    int eleccio; // Variable per emmagatzemar l'elecció de l'usuari
    std::cin >> eleccio; // Llegir l'elecció de l'usuari

    // Assignar el fitxer segons l'elecció
    if (eleccio == 1) {
        fitxerMapa = "nivell1.txt"; // Fitxer per a nivell 1
    }
    else if (eleccio == 2) {
        fitxerMapa = "nivell2.txt"; // Fitxer per a nivell 2
    }
    else {
        std::cerr << "Opció no vàlida.\n"; // Missatge d'error si l'opció no és vàlida
        return -1; // Finalitzar el programa amb error
    }

    // Obrir el fitxer del mapa
    std::ifstream mapaFitxer(fitxerMapa); // Crear un flux per llegir el fitxer
    if (!mapaFitxer.is_open()) { // Comprovar si el fitxer s'ha obert correctament
        std::cerr << "No s'ha pogut obrir el fitxer.\n"; // Missatge d'error
        return -1; // Finalitzar el programa amb error
    }

    // Llegir l'amplada i l'alçada del mapa
    unsigned int ampladaMapa, alcadaMapa; // Variables per emmagatzemar dimensions
    mapaFitxer >> ampladaMapa >> alcadaMapa; // Llegir dimensions del fitxer

    // Llegir el mapa i desar-lo en un vector
    std::vector<int> dadesMapa(ampladaMapa * alcadaMapa); // Vector per emmagatzemar les dades
    for (unsigned int i = 0; i < ampladaMapa * alcadaMapa; ++i) {
        mapaFitxer >> dadesMapa[i]; // Llegir cada tile del mapa
    }

    mapaFitxer.close(); // Tancar el fitxer

    // Crear la capa de tiles amb les dades llegides
    CapaTiles capa; // Crear un objecte de la classe CapaTiles
    if (!capa.carregar("KMM_PGVI_SPRITE MAPA.png", sf::Vector2u(32, 32), dadesMapa.data(), ampladaMapa, alcadaMapa))
        return -1; // Carregar les dades i verificar que tot és correcte

    // Bucle principal de la finestra
    while (finestra.isOpen()) { // Comprovar si la finestra està oberta
        sf::Event esdeveniment; // Crear un esdeveniment
        while (finestra.pollEvent(esdeveniment)) { // Processar els esdeveniments
            if (esdeveniment.type == sf::Event::Closed) // Si es tanca la finestra
                finestra.close(); // Tancar la finestra
        }

        // Dibuixar el mapa de tiles
        finestra.clear(); // Netejar la finestra
        finestra.draw(capa); // Dibuixar la capa de tiles
        finestra.display(); // Actualitzar la finestra
    }

    return 0; // Finalitzar el programa correctament
}
