#pragma once
#include <string>

struct Accessories {
    std::string name;
    std::string category;   // "hat", "top", "bottom"
    int price = 0;
    bool owned = false;
    bool equipped = false;
};