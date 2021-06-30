#pragma once

#include "IEventObserver.hpp"

class IEventSubject {
public:
    virtual void registerObserver(IEventObserver* observer) = 0;
    virtual void unRegisterObserver(IEventObserver* observer) = 0;
    virtual void notifyObserver(glm::vec2 location,int button, int action) = 0;
};