#pragma once
#include "Accessories.h"
#include <vector>
#include <raylib.h>

class Inventory{
    public:
        void DrawButton(); //draw a rectangle button
        void UpdateButton(); //make the button clickable
        void DrawPopup(); //big rectangle center of screen
        void UpdatePopup(); //loop over every items rectangle, if clicked, equipped = true

    private:
        bool isOpen;
        Rectangle inventoryButton;
        Rectangle popupBox;
        
        std::vector<Accessories> accessories;
};