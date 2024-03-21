#pragma once
#include "FallingObject.h"

class Bomb : public FallingObject {
public:
    Bomb();

    Bomb(const float& playerPos);

    ObjectType GetType() const override { return ObjectType::Bomb; }
};