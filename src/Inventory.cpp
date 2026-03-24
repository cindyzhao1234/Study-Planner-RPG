#include "Inventory.h"
#include <algorithm>

void Inventory::DrawButton() {
    inventoryButton = {900.0f, 100.0f, 50.0f, 50.0f};
    DrawRectangleLines((int)inventoryButton.x, (int)inventoryButton.y,
                       (int)inventoryButton.width, (int)inventoryButton.height, BLACK);
}

void Inventory::UpdateButton() {
    if (CheckCollisionPointRec(GetMousePosition(), inventoryButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isOpen = !isOpen;
        return;
    }

    if (!CheckCollisionPointRec(GetMousePosition(), inventoryButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        !CheckCollisionPointRec(GetMousePosition(), popupBox)) {
        isOpen = false;
    }
}

void Inventory::DrawPopup(const User& user, const Assets& assets, CharacterRenderer& characterRenderer, std::vector<Accessories>& allItems){
    if(!isOpen){
        return;
    }

    popupBox = {150.0f, 100.0f, 724.0f, 520.0f};
    DrawRectangle(
        (int)popupBox.x,
        (int)popupBox.y,
        (int)popupBox.width,
        (int)popupBox.height, BLUE
    );

    float innerPadding = 20.0f;
    float slotSize = 60.0f;
    float slotSpacing = 15.0f;
    int columns = 3;

    Rectangle accessoriesPanel = {
        popupBox.x + innerPadding,
        popupBox.y + 60,
        popupBox.width * 0.55f - innerPadding,
        popupBox.height - 80
    };

    Rectangle previewPanel = {
        popupBox.x + popupBox.width * 0.60f,
        popupBox.y + 60,
        popupBox.width * 0.35f,
        popupBox.height - 80
    };

    DrawText("CLOSET", (int)popupBox.x + 20, (int)popupBox.y + 20, 20, BLACK);

    DrawRectangleLines((int)accessoriesPanel.x, (int)accessoriesPanel.y,
                       (int)accessoriesPanel.width, (int)accessoriesPanel.height, GREEN);

    DrawRectangleLines((int)previewPanel.x, (int)previewPanel.y,
                       (int)previewPanel.width, (int)previewPanel.height, RED);

    DrawText("Accessories", (int)accessoriesPanel.x + 10, (int)accessoriesPanel.y + 10, 20, BLACK);
    DrawText("Preview", (int)previewPanel.x + 10, (int)previewPanel.y + 10, 20, BLACK);

    // ---- preview character ----
    float maxWidth = previewPanel.width - 40;
    float maxHeight = previewPanel.height - 40;

    float scaleX = maxWidth / (float)assets.characterTexture.width;
    float scaleY = maxHeight / (float)assets.characterTexture.height;
    float scale = std::min(scaleX, scaleY);

    float previewScale = 1.15f;
    float drawWidth = assets.characterTexture.width * scale * previewScale;
    float drawHeight = assets.characterTexture.height * scale * previewScale;

    Rectangle previewDest = {
        previewPanel.x + (previewPanel.width - drawWidth) / 2,
        previewPanel.y + (previewPanel.height - drawHeight) / 2,
        drawWidth,
        drawHeight
    };

    characterRenderer.DrawCharacter(user, assets, allItems, previewDest);

    // ---- sidebar filter buttons ----
    float sidebarX = accessoriesPanel.x + 20;
    float sidebarY = accessoriesPanel.y + 60;

    allFilter = {sidebarX, sidebarY, 50, 50};
    hatFilter = {sidebarX, sidebarY + 70, 50, 50};
    hairFilter = {sidebarX, sidebarY + 140, 50, 50};
    topFilter = {sidebarX, sidebarY + 210, 50, 50};
    bottomFilter = {sidebarX, sidebarY + 280, 50, 50};

    Color allColor = (selectedCategory == "all") ? YELLOW : LIGHTGRAY;
    Color hatColor = (selectedCategory == "hat") ? YELLOW : LIGHTGRAY;
    Color hairColor = (selectedCategory == "hair") ? YELLOW : LIGHTGRAY;
    Color topColor = (selectedCategory == "top") ? YELLOW : LIGHTGRAY;
    Color bottomColor = (selectedCategory == "bottom") ? YELLOW : LIGHTGRAY;

    DrawRectangleRec(allFilter, allColor);
    DrawRectangleRec(hatFilter, hatColor);
    DrawRectangleRec(hairFilter, hairColor);
    DrawRectangleRec(topFilter, topColor);
    DrawRectangleRec(bottomFilter, bottomColor);

    DrawRectangleLines((int)allFilter.x, (int)allFilter.y, (int)allFilter.width, (int)allFilter.height, BLACK);
    DrawRectangleLines((int)hatFilter.x, (int)hatFilter.y, (int)hatFilter.width, (int)hatFilter.height, BLACK);
    DrawRectangleLines((int)hairFilter.x, (int)hairFilter.y, (int)hairFilter.width, (int)hairFilter.height, BLACK);
    DrawRectangleLines((int)topFilter.x, (int)topFilter.y, (int)topFilter.width, (int)topFilter.height, BLACK);
    DrawRectangleLines((int)bottomFilter.x, (int)bottomFilter.y, (int)bottomFilter.width, (int)bottomFilter.height, BLACK);

    DrawText("ALL", (int)allFilter.x + 8, (int)allFilter.y + 15, 14, BLACK);
    DrawText("HAT", (int)hatFilter.x + 8, (int)hatFilter.y + 15, 14, BLACK);
    DrawText("HAIR", (int)hairFilter.x + 4, (int)hairFilter.y + 15, 14, BLACK);
    DrawText("TOP", (int)topFilter.x + 8, (int)topFilter.y + 15, 14, BLACK);
    DrawText("BOT", (int)bottomFilter.x + 8, (int)bottomFilter.y + 15, 14, BLACK);

    // ---- accessory slots ----
    int visibleIndex = 0;

    for(int i = 0; i < (int)allItems.size(); i++){
        if (!allItems[i].owned) {
            continue;
        }
    
        if(selectedCategory != "all" && allItems[i].category != selectedCategory){
            continue;
        }

        int row = visibleIndex / columns;
        int col = visibleIndex % columns;

        float slotX = accessoriesPanel.x + 100 + col * (slotSize + slotSpacing);
        float slotY = accessoriesPanel.y + 60 + row * (slotSize + slotSpacing);

        Rectangle itemSlot = {slotX, slotY, slotSize, slotSize};

        Color slotColour = allItems[i].equipped ? GREEN : RED;

        DrawRectangle((int)itemSlot.x, (int)itemSlot.y,
                      (int)itemSlot.width, (int)itemSlot.height, slotColour);

        DrawText(allItems[i].name.c_str(),
                 (int)itemSlot.x + 5,
                 (int)itemSlot.y + 20,
                 10,
                 BLACK);

        visibleIndex++;
    }
}

void Inventory::UpdatePopup(User& user, std::vector<Accessories>& allItems) {
    if (!isOpen) {
        return;
    }

    // ---- filter button clicks ----
    if(CheckCollisionPointRec(GetMousePosition(), allFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        selectedCategory = "all";
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), hatFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "hat";
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), hairFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "hair";
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), topFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "top";
        return;
    }

    if (CheckCollisionPointRec(GetMousePosition(), bottomFilter) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        selectedCategory = "bottom";
        return;
    }

    // ---- item slot clicks ----
    float innerPadding = 20.0f;
    float slotSize = 60.0f;
    float slotSpacing = 15.0f;
    int columns = 3;

    Rectangle accessoriesPanel = {
        popupBox.x + innerPadding,
        popupBox.y + 60,
        popupBox.width * 0.55f - innerPadding,
        popupBox.height - 80
    };

    float sidebarX = accessoriesPanel.x + 20;
    float sidebarY = accessoriesPanel.y + 60;

    allFilter = {sidebarX, sidebarY, 50, 50};
    hatFilter = {sidebarX, sidebarY + 70, 50, 50};
    hairFilter = {sidebarX, sidebarY + 140, 50, 50};
    topFilter = {sidebarX, sidebarY + 210, 50, 50};
    bottomFilter = {sidebarX, sidebarY + 280, 50, 50};

    int visibleIndex = 0;

    for(int i = 0; i < (int)allItems.size(); i++){
        if (!allItems[i].owned) {
            continue;
        }
    
        if(selectedCategory != "all" && allItems[i].category != selectedCategory){
            continue;
        }

        int row = visibleIndex / columns;
        int col = visibleIndex % columns;

        float slotX = accessoriesPanel.x + 100 + col * (slotSize + slotSpacing);
        float slotY = accessoriesPanel.y + 60 + row * (slotSize + slotSpacing);

        Rectangle itemSlot = {slotX, slotY, slotSize, slotSize};

        if(CheckCollisionPointRec(GetMousePosition(), itemSlot) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            std::string clickedCategory = allItems[i].category;
            bool wasEquipped = allItems[i].equipped;

            // Unequip all items in same category
            for(int j = 0; j < (int)allItems.size(); j++){
                if(allItems[j].category == clickedCategory){
                    allItems[j].equipped = false;
                }
            }

            // Clicking again unequips
            if(wasEquipped){
                if (clickedCategory == "hat") {
                    user.equippedHat = "";
                } else if (clickedCategory == "hair") {
                    user.equippedHair = "";
                } else if (clickedCategory == "top") {
                    user.equippedTop = "";
                } else if (clickedCategory == "bottom") {
                    user.equippedBottom = "";
                }
            } else{
                allItems[i].equipped = true;

                if(clickedCategory == "hat"){
                    user.equippedHat = allItems[i].name;
                } else if(clickedCategory == "hair"){
                    user.equippedHair = allItems[i].name;
                } else if(clickedCategory == "top"){
                    user.equippedTop = allItems[i].name;
                } else if(clickedCategory == "bottom"){
                    user.equippedBottom = allItems[i].name;
                }
            }

            return;
        }

        visibleIndex++;
    }
}

bool Inventory::GetIsOpen(){
    return isOpen;
}