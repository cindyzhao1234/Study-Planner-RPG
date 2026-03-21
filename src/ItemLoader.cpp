#include "Items.h"
#include "ItemLoader.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Accessories> LoadItems() {
    std::vector<Accessories> items;
    std::ifstream file("../src/Items.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open file: Items.csv\n";
        return items;
    }

    std::string line;

    // skip header
    if (!std::getline(file, line)) {
        return items;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, category, priceStr, ownedStr, equippedStr;

        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, ownedStr, ',');
        std::getline(ss, equippedStr, ',');

        Accessories item;
        item.name = name;
        item.category = category;
        item.price = std::stoi(priceStr);
        item.owned = (ownedStr == "true");
        item.equipped = (equippedStr == "true");

        items.push_back(item);
    }

    return items;
}