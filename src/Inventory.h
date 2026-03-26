#pragma once
#include "Items.h"
#include "CharacterRender.h"
#include "User.h"
#include <vector>
#include <raylib.h>

class Inventory {
public:
    void DrawButton(Assets assets);
    void UpdateButton();

    void DrawPopup(const User& user, const Assets& assets, CharacterRenderer& characterRenderer, std::vector<Accessories>& allItems);   
    void UpdatePopup(User& user, std::vector<Accessories>& allItems);

    Rectangle GetAccessoriesPanel() const;
    Rectangle GetPreviewPanel() const;
    Rectangle GetFilterRect(const std::string& category) const;
    Rectangle GetAccessorySlotRect(int visibleIndex, Rectangle accessoriesPanel) const;
    bool MatchesFilter(const Accessories& accessory) const;

    bool GetIsOpen();


private:
    bool isOpen = false;
    Rectangle inventoryButton;
    Rectangle popupBox;

    std::string selectedCategory = "all";

    Rectangle allFilter, topFilter, hairFilter, hatFilter, bottomFilter;
};