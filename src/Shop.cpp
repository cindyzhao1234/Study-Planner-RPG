#include "Shop.h"
#include "User.h"
#include <format>
#include <iostream>

void Shop::DrawButton(Assets assets) {
    shopButton = {900.0f, 200.0f, 75.0f, 75.0f};
    DrawTextureEx(assets.shopButtonTex, {shopButton.x, shopButton.y}, 0.0f, 1.25f, WHITE);
}

void Shop::UpdateButton() {
    if (CheckCollisionPointRec(GetMousePosition(), shopButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isOpen = !isOpen;
        return;
    }

    if (!CheckCollisionPointRec(GetMousePosition(), shopButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        !CheckCollisionPointRec(GetMousePosition(), popupBox)) {
        isOpen = false;
    }
}

void Shop::DrawPopup(std::vector<Accessories>& allItems, Assets assets) {
    if (!isOpen) {
        return;
    }

    popupBox = {150.0f, 100.0f, 724.0f, 520.0f};
    DrawTexture(assets.PopupBackground, (int)popupBox.x, (int)popupBox.y, WHITE);

    DrawText("SHOP", (int)popupBox.x + 20, (int)popupBox.y + 15, 24, BLACK);

    float buttonW = 80.0f;
    float buttonH = 40.0f;
    float buttonSpacing = 10.0f;
    float startX = popupBox.x + 20;
    float startY = popupBox.y + 50;

    allFilter    = {startX + 0 * (buttonW + buttonSpacing), startY, buttonW, buttonH};
    hatFilter    = {startX + 1 * (buttonW + buttonSpacing), startY, buttonW, buttonH};
    hairFilter   = {startX + 2 * (buttonW + buttonSpacing), startY, buttonW, buttonH};
    topFilter    = {startX + 3 * (buttonW + buttonSpacing), startY, buttonW, buttonH};
    bottomFilter = {startX + 4 * (buttonW + buttonSpacing), startY, buttonW, buttonH};

    Texture2D selectedAllCat = (selectedCategory == "all") ? assets.PressedFilterButton : assets.filterButton;
    Texture2D selectedHatCat = (selectedCategory == "hat") ? assets.PressedFilterButton : assets.filterButton;
    Texture2D selectedHairCat = (selectedCategory == "hair") ? assets.PressedFilterButton : assets.filterButton;
    Texture2D selectedTopCat = (selectedCategory == "top") ? assets.PressedFilterButton : assets.filterButton;
    Texture2D selectedBottomCat = (selectedCategory == "bottom") ? assets.PressedFilterButton : assets.filterButton;

    DrawTexturePro(
        selectedAllCat, 
        {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
        {(float)allFilter.x, (float)allFilter.y, (float)allFilter.width, (float)allFilter.height},
        {0, 0,},
        0.0,
        WHITE
    );

    DrawTexturePro(
        selectedHatCat, 
        {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
        {(float)hatFilter.x, (float)hatFilter.y, (float)hatFilter.width, (float)hatFilter.height},
        {0, 0,},
        0.0,
        WHITE
    );

    DrawTexturePro(
        selectedHairCat, 
        {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
        {(float)hairFilter.x, (float)hairFilter.y, (float)hairFilter.width, (float)hairFilter.height},
        {0, 0,},
        0.0,
        WHITE
    );

    DrawTexturePro(
        selectedTopCat, 
        {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
        {(float)topFilter.x, (float)topFilter.y, (float)topFilter.width, (float)topFilter.height},
        {0, 0,},
        0.0,
        WHITE
    );

    DrawTexturePro(
        selectedBottomCat, 
        {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
        {(float)bottomFilter.x, (float)bottomFilter.y, (float)bottomFilter.width, (float)bottomFilter.height},
        {0, 0,},
        0.0,
        WHITE
    );

    DrawText("ALL", (int)allFilter.x + 20, (int)allFilter.y + 12, 16, BLACK);
    DrawText("HAT", (int)hatFilter.x + 20, (int)hatFilter.y + 12, 16, BLACK);
    DrawText("HAIR", (int)hairFilter.x + 15, (int)hairFilter.y + 12, 16, BLACK);
    DrawText("TOP", (int)topFilter.x + 20, (int)topFilter.y + 12, 16, BLACK);
    DrawText("BOTTOM", (int)bottomFilter.x + 8, (int)bottomFilter.y + 12, 16, BLACK);

    Rectangle itemsPanel = {
        popupBox.x + 20,
        popupBox.y + 110,
        popupBox.width * 0.55f,
        popupBox.height - 130
    };

    previewPanel = {
        popupBox.x + popupBox.width * 0.62f,
        popupBox.y + 110,
        popupBox.width * 0.30f,
        popupBox.height - 130
    };

    buyButton = {
        previewPanel.x + (previewPanel.width / 4),
        previewPanel.y + 300,
        previewPanel.width / 2,
        50
    };


    DrawTexturePro(
        assets.panelTex,
        {0, 0, (float)assets.panelTex.width, (float)assets.panelTex.height},
        {itemsPanel.x, itemsPanel.y, itemsPanel.width, itemsPanel.height},
        {0,0},
        0.0,
        WHITE
    );

    DrawTexturePro(
        assets.panelTex,
        {0, 0, (float)assets.panelTex.width, (float)assets.panelTex.height},
        {previewPanel.x, previewPanel.y, previewPanel.width, previewPanel.height},
        {0,0},
        0.0,
        WHITE
    );

    float slotSize = 70.0f;
    float slotSpacing = 15.0f;
    int columns = 3;
    int visibleIndex = 0;

    for (int i = 0; i < (int)allItems.size(); i++) {
        if (selectedCategory != "all" && allItems[i].category != selectedCategory) {
            continue;
        }

        int row = visibleIndex / columns;
        int col = visibleIndex % columns;

        float slotX = itemsPanel.x + 20 + col * (slotSize + slotSpacing);
        float slotY = itemsPanel.y + 20 + row * (slotSize + slotSpacing);

        Rectangle itemSlot = {slotX, slotY, slotSize, slotSize};

        Color slotColor = LIGHTGRAY;
        if (allItems[i].owned) {
            slotColor = GRAY;
        } else if (i == selectedItemIndex) {
            slotColor = YELLOW;
        }

        Texture2D selectedItemCat = (allItems[i].owned || i == selectedItemIndex) ? assets.PressedFilterButton : assets.filterButton;

        DrawTexturePro(
            selectedItemCat, 
            {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
            {(float)itemSlot.x, (float)itemSlot.y, (float)itemSlot.width, (float)itemSlot.height},
            {0, 0,},
            0.0,
            WHITE
        );

        DrawText(allItems[i].name.c_str(),
                 (int)itemSlot.x + 4,
                 (int)itemSlot.y + 25,
                 10,
                 BLACK);

        visibleIndex++;
    }

    if (selectedItemIndex >= 0 && selectedItemIndex < (int)allItems.size()) {
        DrawText(allItems[selectedItemIndex].name.c_str(),
                 (int)previewPanel.x + 10,
                 (int)previewPanel.y + 20,
                 20,
                 BLACK);

        DrawText(allItems[selectedItemIndex].category.c_str(),
                 (int)previewPanel.x + 10,
                 (int)previewPanel.y + 50,
                 16,
                 BLACK);

        if (allItems[selectedItemIndex].owned) {
            DrawText("Owned", (int)previewPanel.x + 10, (int)previewPanel.y + 250, 18, DARKGRAY);
            
        } else {
            DrawText("Available", (int)previewPanel.x + 10, (int)previewPanel.y + 250, 18, BLACK);

            DrawTexturePro(
                assets.filterButton, 
                {0, 0, (float)assets.filterButton.width, (float)assets.filterButton.height},
                {(float)buyButton.x, (float)buyButton.y, (float)buyButton.width, (float)buyButton.height},
                {0, 0,},
                0.0,
                WHITE
            );
            DrawText(TextFormat("Buy: %d coins", allItems[selectedItemIndex].price), buyButton.x + 10, buyButton.y + 15, 16, BLACK);
        }

        Texture2D itemTex = LoadTexture(TextFormat("../assets/%s.png", allItems[selectedItemIndex].name.c_str()));
        DrawTextureEx(itemTex, {previewPanel.x - 20, previewPanel.y - 50}, 0.0f, 5.0f, WHITE);
    }

    if(popupMessageTimer > 0){
        DrawText(popupMessage.c_str(), popupBox.x + 200, popupBox.y + 100, 20, GREEN);
    }
}

void Shop::UpdatePopup(std::vector<Accessories>& allItems, User& user) {
    if (!isOpen) {
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), allFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "all";
        selectedItemIndex = -1;
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), hatFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "hat";
        selectedItemIndex = -1;
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), hairFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "hair";
        selectedItemIndex = -1;
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), topFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "top";
        selectedItemIndex = -1;
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), bottomFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "bottom";
        selectedItemIndex = -1;
        return;
    }

    Rectangle itemsPanel = {
        popupBox.x + 20,
        popupBox.y + 110,
        popupBox.width * 0.55f,
        popupBox.height - 130
    };

    float slotSize = 70.0f;
    float slotSpacing = 15.0f;
    int columns = 3;
    int visibleIndex = 0;

    for (int i = 0; i < (int)allItems.size(); i++) {
        if (selectedCategory != "all" && allItems[i].category != selectedCategory) {
            continue;
        }

        int row = visibleIndex / columns;
        int col = visibleIndex % columns;

        float slotX = itemsPanel.x + 20 + col * (slotSize + slotSpacing);
        float slotY = itemsPanel.y + 20 + row * (slotSize + slotSpacing);

        Rectangle itemSlot = {slotX, slotY, slotSize, slotSize};

        if (CheckCollisionPointRec(GetMousePosition(), itemSlot) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selectedItemIndex = i;
            return;
        }

        visibleIndex++;
    }

    if(CheckCollisionPointRec(GetMousePosition(), buyButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(user.CoinCount >= allItems[selectedItemIndex].price){
            allItems[selectedItemIndex].owned = true;
            user.CoinCount -= allItems[selectedItemIndex].price;
            popupMessage = "SUCCESS!";
            popupMessageTimer = 1.0f;
    
        } else{
            std::cout << "Price: " << allItems[selectedItemIndex].price << "\n";
            std::cout << "User Coin Coint: " << user.CoinCount << "\n";
            popupMessage = "NOT ENOUGH COINS";
            popupMessageTimer = 1.0f;
        }

    }
    if(popupMessageTimer > 0){
        popupMessageTimer = popupMessageTimer - GetFrameTime();
    }
}

bool Shop::GetIsOpen(){
    return isOpen;
}