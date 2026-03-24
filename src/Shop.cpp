#include "Shop.h"
#include "User.h"
#include <format>
#include <iostream>

void Shop::DrawButton() {
    shopButton = {900.0f, 200.0f, 50.0f, 50.0f};
    DrawRectangleLines((int)shopButton.x, (int)shopButton.y,
                       (int)shopButton.width, (int)shopButton.height, BLACK);
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

void Shop::DrawPopup(std::vector<Accessories>& allItems) {
    if (!isOpen) {
        return;
    }

    popupBox = {150.0f, 100.0f, 724.0f, 520.0f};
    DrawRectangle((int)popupBox.x, (int)popupBox.y,
                  (int)popupBox.width, (int)popupBox.height, RED);

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

    Color allColour    = (selectedCategory == "all")    ? YELLOW : LIGHTGRAY;
    Color hatColour    = (selectedCategory == "hat")    ? YELLOW : LIGHTGRAY;
    Color hairColour   = (selectedCategory == "hair")   ? YELLOW : LIGHTGRAY;
    Color topColour    = (selectedCategory == "top")    ? YELLOW : LIGHTGRAY;
    Color bottomColour = (selectedCategory == "bottom") ? YELLOW : LIGHTGRAY;

    DrawRectangleRec(allFilter, allColour);
    DrawRectangleRec(hatFilter, hatColour);
    DrawRectangleRec(hairFilter, hairColour);
    DrawRectangleRec(topFilter, topColour);
    DrawRectangleRec(bottomFilter, bottomColour);

    DrawRectangleLines((int)allFilter.x, (int)allFilter.y, (int)allFilter.width, (int)allFilter.height, BLACK);
    DrawRectangleLines((int)hatFilter.x, (int)hatFilter.y, (int)hatFilter.width, (int)hatFilter.height, BLACK);
    DrawRectangleLines((int)hairFilter.x, (int)hairFilter.y, (int)hairFilter.width, (int)hairFilter.height, BLACK);
    DrawRectangleLines((int)topFilter.x, (int)topFilter.y, (int)topFilter.width, (int)topFilter.height, BLACK);
    DrawRectangleLines((int)bottomFilter.x, (int)bottomFilter.y, (int)bottomFilter.width, (int)bottomFilter.height, BLACK);

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

    DrawRectangleLines((int)itemsPanel.x, (int)itemsPanel.y, (int)itemsPanel.width, (int)itemsPanel.height, BLACK);
    DrawRectangleLines((int)previewPanel.x, (int)previewPanel.y, (int)previewPanel.width, (int)previewPanel.height, BLACK);

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

        DrawRectangleRec(itemSlot, slotColor);
        DrawRectangleLines((int)itemSlot.x, (int)itemSlot.y, (int)itemSlot.width, (int)itemSlot.height, BLACK);

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
            DrawRectangleLines((int)buyButton.x, (int)buyButton.y, (int)buyButton.width, (int)buyButton.height, BLUE);
            DrawText(TextFormat("Buy: %d coins", allItems[selectedItemIndex].price), buyButton.x + 10, buyButton.y + 10, 16, BLACK);
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