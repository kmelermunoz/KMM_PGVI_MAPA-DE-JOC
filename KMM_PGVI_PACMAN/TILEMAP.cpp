#include <SFML/Graphics.hpp>

class CapaTiles : public sf::Drawable, public sf::Transformable {
public:
    // Funció per crear el mapa de tiles
    bool carregar(const std::string& fitxerTileset, sf::Vector2u midaTile, const int* indicesTiles, unsigned int ampladaMapa, unsigned int alcadaMapa) {
        // Carregar la textura del tileset
        if (!tilesetTexture.loadFromFile(fitxerTileset))
            return false; // Retornar fals si no es pot carregar la textura

        // Configurar els vèrtex per al mapa
        vertices.setPrimitiveType(sf::Quads); // Configurar el tipus de primitivas com a quads
        vertices.resize(ampladaMapa * alcadaMapa * 4); // Redimensionar el vector de vèrtex

        // Recórrer cada tile al mapa
        for (unsigned int x = 0; x < ampladaMapa; ++x) {
            for (unsigned int y = 0; y < alcadaMapa; ++y) {
                // Obtenir l'índex del tile actual
                int tileIndex = indicesTiles[x + y * ampladaMapa];

                // Calcular la posició del tile al tileset
                int tu = tileIndex % (tilesetTexture.getSize().x / midaTile.x); // Coordenada x
                int tv = tileIndex / (tilesetTexture.getSize().x / midaTile.x); // Coordenada y

                // Obtenir un punter al quad actual
                sf::Vertex* quad = &vertices[(x + y * ampladaMapa) * 4]; // Punter al quad

                // Definir les posicions de les cantonades del quad
                quad[0].position = sf::Vector2f(x * midaTile.x, y * midaTile.y); // Esquerra dalt
                quad[1].position = sf::Vector2f((x + 1) * midaTile.x, y * midaTile.y); // Dreta dalt
                quad[2].position = sf::Vector2f((x + 1) * midaTile.x, (y + 1) * midaTile.y); // Dreta baix
                quad[3].position = sf::Vector2f(x * midaTile.x, (y + 1) * midaTile.y); // Esquerra baix

                // Definir les coordenades de la textura
                quad[0].texCoords = sf::Vector2f(tu * midaTile.x, tv * midaTile.y); // Esquerra dalt
                quad[1].texCoords = sf::Vector2f((tu + 1) * midaTile.x, tv * midaTile.y); // Dreta dalt
                quad[2].texCoords = sf::Vector2f((tu + 1) * midaTile.x, (tv + 1) * midaTile.y); // Dreta baix
                quad[3].texCoords = sf::Vector2f(tu * midaTile.x, (tv + 1) * midaTile.y); // Esquerra baix
            }
        }

        return true; // Retornar veritable si s'ha creat correctament
    }

private:
    // Sobreescriure la funció de dibuix per renderitzar el mapa de tiles
    virtual void draw(sf::RenderTarget& desti, sf::RenderStates estats) const {
        // Aplicar la transformació
        estats.transform *= getTransform(); // Aplicar la transformació de la capa

        // Aplicar la textura del tileset
        estats.texture = &tilesetTexture; // Assignar la textura al context de dibuix

        // Dibuixar el mapa
        desti.draw(vertices, estats); // Dibuixar els vèrtex
    }

    sf::VertexArray vertices;  // Array de vèrtex per als tiles
    sf::Texture tilesetTexture;  // Textura del tileset
};
