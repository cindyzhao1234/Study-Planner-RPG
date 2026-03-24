#pragma once
#include "raylib.h"
#include "User.h"
#include "Assets.h"

class CharacterRenderer {
public:
    void DrawCharacter(const User& user, const Assets& assets, std::vector<Accessories> allItems, Rectangle dest);
};