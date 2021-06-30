#pragma once

class IEventObserver {
public:
    virtual void onUpdate(glm::vec2 location, int button, int action) = 0;
};