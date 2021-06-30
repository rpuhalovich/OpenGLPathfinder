#pragma once

class IEventObserver {
public:
    virtual void OnUpdate(glm::vec2 location, int button, int action) = 0;
};