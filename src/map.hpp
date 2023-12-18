#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "tower.hpp"

class Tower; // Forward declaration

/**
 * @class Map
 * @brief Class representing the game map.
 * 
 * The Map class extends sf::Drawable and sf::Transformable to provide rendering and transformation functionality.
 * It loads a map texture and handles unbuildable areas, which prevents tower placement in specified regions.
 */

class Map : public sf::Drawable, public sf::Transformable {
public:
    sf::Texture texture; // Texture used for the map.
    sf::Sprite background; // Sprite representing the map background.
    std::vector<sf::FloatRect> unBuildable; // Vector of rectangles representing unbuildable areas on the map.

    /**
     * @brief Loads a map texture from the specified file.
     * @param fileName The name of the file containing the map texture.
     */

    void loadMap(const std::string& fileName);


private:
    /**
     * @brief Draws the map on the specified rendering target.
     * @param target The rendering target on which the map is drawn.
     * @param states The rendering states to apply (overrides sf::Drawable).
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // MAP_HPP