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
    void UpdatePopup(std::vector<Accessories>& allItems, User& user);

    bool GetIsOpen();

private:


    std::string selectedCategory = "all";
    int selectedItemIndex = -1;
    Rectangle previewPanel;

    Rectangle allFilter, hatFilter, hairFilter, topFilter, bottomFilter;
    Rectangle popupBox;
    Rectangle shopButton;
    Rectangle buyButton;
    bool isOpen = false;

    std::string popupMessage;
    float popupMessageTimer;

    std::vector<Accessories> shopItems;
};