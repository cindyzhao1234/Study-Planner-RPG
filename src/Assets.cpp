#include "Assets.h"
#include "ItemLoader.h"
#include <iostream>

void Assets::Load(std::vector<Accessories>& ItemList) {
    coinTexture = LoadTexture("../assets/coin.png");
    characterTexture = LoadTexture("../assets/character.png");
    backgroundTexture = LoadTexture("../assets/Background.png");
    inventoryButtonTex = LoadTexture("../assets/inventoryButton.png");
    shopButtonTex = LoadTexture("../assets/ShopButton.png");
    binTexture = LoadTexture("../assets/Bin.png");
    headerTex = LoadTexture("../assets/headerTex.png");
    taskBox = LoadTexture("../assets/taskBox.png");
    mainTaskBoxTex = LoadTexture("../assets/mainTaskBox.png");
    PopupBackground = LoadTexture("../assets/PopupBackground.png");
    panelTex = LoadTexture("../assets/Panel.png");
    filterButton = LoadTexture("../assets/filterButton.png");
    PressedFilterButton = LoadTexture("../assets/PressedFilterButton.png");

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
    UnloadTexture(backgroundTexture);
    UnloadTexture(inventoryButtonTex);
    UnloadTexture(shopButtonTex);
    UnloadTexture(binTexture);
    UnloadTexture(headerTex);
    UnloadTexture(taskBox);
    UnloadTexture(mainTaskBoxTex);
    UnloadTexture(PopupBackground);
    UnloadTexture(panelTex);
    UnloadTexture(filterButton);
    UnloadTexture(PressedFilterButton);

    for(auto& entry : loadedTextures){
        UnloadTexture(entry.second);
    }

    loadedTextures.clear();
}