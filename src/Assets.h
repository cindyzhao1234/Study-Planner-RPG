#pragma once
#include <raylib.h>
#include "Items.h"
#include <vector>
#include <map>

struct Assets {
    Texture2D coinTexture;
    Texture2D characterTexture;
    Texture2D backgroundTexture;
    Texture2D inventoryButtonTex;
    Texture2D shopButtonTex;
    Texture2D binTexture;
    Texture2D headerTex;
    Texture2D taskBox;
    Texture2D mainTaskBoxTex;
    Texture2D PopupBackground;
    Texture2D panelTex;
    Texture2D filterButton;
    Texture2D PressedFilterButton;

    std::unordered_map<std::string, Texture2D> loadedTextures;

    void Load(std::vector<Accessories>& ItemList);
    void Unload();
};