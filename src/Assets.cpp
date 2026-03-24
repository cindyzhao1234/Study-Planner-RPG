#include "Assets.h"
#include "ItemLoader.h"
#include <iostream>

void Assets::Load(std::vector<Accessories>& ItemList) {
    coinTexture = LoadTexture("../assets/coin.png");
    characterTexture = LoadTexture("../assets/character.png");

    for(int i = 0; i < ItemList.size(); i++){
        std::string itemName = ItemList[i].name;

        std::string assetPath = "../assets/" + itemName + ".png";
        Texture2D itemTexture = LoadTexture(assetPath.c_str());
        loadedTextures.insert({itemName, itemTexture});

    }

}

void Assets::Unload() {
    UnloadTexture(coinTexture);
    UnloadTexture(characterTexture);

    for(auto& entry : loadedTextures){
        UnloadTexture(entry.second);
    }

    loadedTextures.clear();
}