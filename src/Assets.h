#pragma once
#include <raylib.h>
#include "Items.h"
#include <vector>
#include <map>

struct Assets {
    Texture2D coinTexture;
    Texture2D characterTexture;

    std::unordered_map<std::string, Texture2D> loadedTextures;

    void Load(std::vector<Accessories>& ItemList);
    void Unload();
};