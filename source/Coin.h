#pragma once
#include "FallingObject.h"

class Coin : public FallingObject {
public:
    Coin();

    ObjectType GetType() const override { return ObjectType::Coin; }
};