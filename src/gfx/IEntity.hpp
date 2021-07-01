#pragma once

/**
 * Abstract class that describes everything an entity needs to have.
 */
class IEntity {
public:
    virtual void draw() = 0;
};