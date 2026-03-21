#pragma once
#include "Items.h"
#include "CharacterRender.h"
#include "User.h"
#include "Inventory.h"
#include <vector>
#include <raylib.h>


class Shop{
public:
    void DrawButton();
    void UpdateButton();

    void DrawPopup(std::vector<Accessories>& allItems);
    void UpdatePopup(std::vector<Accessories>& allItems);

private:


    std::string selectedCategory = "all";
    int selectedItemIndex = -1;

    Rectangle allFilter, hatFilter, hairFilter, topFilter, bottomFilter;
    Rectangle popupBox;
    Rectangle shopButton;
    bool isOpen = false;

    std::vector<Accessories> shopItems;
};