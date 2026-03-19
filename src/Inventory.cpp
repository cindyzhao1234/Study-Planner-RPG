#include "Inventory.h"

void Inventory::DrawButton(){
    inventoryButton = {1100.0f, 100.0f, 50.0f, 50.0f};
    DrawRectangleLines(1100.0f, 100.0f, 50.0f, 50.0f, BLACK);
} //draw a rectangle button

void Inventory::UpdateButton(){

    if(CheckCollisionPointRec(GetMousePosition(), inventoryButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        isOpen = true;
    }
    if(!CheckCollisionPointRec(GetMousePosition(), inventoryButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        isOpen = false;
    }
} //make the button clickable

void Inventory::DrawPopup(){
    if(isOpen == true){
        popupBox = {200.0f, 100.0f, 880.0f, 520.0f};
        DrawRectangle(200.0f, 100.0f, 880.0f, 520.0f, BLUE);
    }
} //big rectangle center of screen

void Inventory::UpdatePopup(){

} //loop over every items rectangle, if clicked, equipped = true