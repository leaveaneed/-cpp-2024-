#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

class Bonus {
public:
    virtual ~Bonus() = default;
    virtual void apply() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
};

class ResizePaddleBonus : public Bonus {
    // Implementation...
};

class ChangeBallSpeedBonus : public Bonus {
    // Implementation...
};

class StickyBallBonus : public Bonus {
    // Implementation...
};

// Other bonuses...

#endif // BONUS_H
