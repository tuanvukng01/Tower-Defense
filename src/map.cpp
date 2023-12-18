#include "map.hpp"

// Loads a map from the specified file, applying the texture to the background.
// If the texture loading fails, the function returns early without setting the texture.
// Parameters:
//   - fileName: The name of the file containing the map texture.
void Map::loadMap(const std::string& fileName) {
    if (!texture.loadFromFile("textures/" + fileName)) {
         // Handle texture loading failure 
        return;
    }
    // Set the loaded texture to the background.
    background.setTexture(texture);
}

// Draws the map on the specified rendering target.
// Parameters:
//   - target: The rendering target on which the map is drawn.
//   - states: The rendering states to apply 
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the background on the specified rendering target.
    target.draw(background);
} 
