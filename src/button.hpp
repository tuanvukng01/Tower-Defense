#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>

/**
 * @enum Actions
 * @brief Possible actions a button can have.
*/
enum class Actions{
    Tower1,
    Tower2,
    Tower3,
    Tower4,
    Tower5,
    Pause,
    Upgrade,
    Sell,
    Close,  // In upgrade menu, closes upgrade menu.
    Level   // Click to start level
};

/**
 * @class Button
 * @brief Represents a clickable button
*/
class Button : public sf::Sprite {
public:
    /**
     * @brief Constructs a button.
     * 
     * @param action is the Actions enum determining the button type
     * @param texture is the texture for the button
     * @param position is the button position
     * @param text is the button lable text
     * @param font is the font used for the button 
    */
    Button(Actions action, sf::Texture& texture, sf::Vector2f position, std::string text, sf::Font& font) : action_(action) {
        setTexture(texture);
        setPosition(position);
        label_ = sf::Text(text, font, 15);
        label_.setPosition(position.x, position.y+20);
    }

    /**
     * @brief checks if the button has been clicked.
     * 
     * @return true if button was clicked, false otherwise.
    */
    bool isClicked(sf::Vector2f mousePos) const {
        return getGlobalBounds().contains(mousePos);
    }

    Actions getAction() const { return action_; }
    sf::Text getLabel() const { return label_; }

private:
    Actions action_;
    sf::Text label_;

};


#endif