#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

class Block {
public:
    virtual ~Block() = default;
    virtual void update() = 0;
    virtual void onHit() = 0;
    virtual bool isDestroyed() const = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
};

class UnbreakableBlock : public Block {
    // Implementation...
};

class BonusBlock : public Block {
    // Implementation...
};

class SpeedBlock : public Block {
    // Implementation...
};

class HealthBlock : public Block {
    // Implementation...
};

#endif // BLOCK_H
