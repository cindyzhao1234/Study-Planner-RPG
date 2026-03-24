#include "CharacterRender.h"

void CharacterRenderer::DrawCharacter(const User& user, const Assets& assets, std::vector<Accessories> allItems, Rectangle dest) {
    // draw base
    DrawTexturePro(
        assets.characterTexture,
        Rectangle{0, 0, (float)assets.characterTexture.width, (float)assets.characterTexture.height},
        dest,
        Vector2{0, 0},
        0.0f,
        WHITE
    );

    for (int i = 0; i < allItems.size(); i++) {
        //draw bottoms
        if(allItems[i].category == "bottom" && allItems[i].equipped){
            auto it = assets.loadedTextures.find(allItems[i].name);
    
            if (it != assets.loadedTextures.end()) {
                const Texture2D& tex = it->second;
    
                DrawTexturePro(
                    tex,
                    Rectangle{0, 0, (float)tex.width, (float)tex.height},
                    dest,
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }
        }

    }

    for (int i = 0; i < allItems.size(); i++) {
        //draw bottoms
        if(allItems[i].category == "top" && allItems[i].equipped){
            auto it = assets.loadedTextures.find(allItems[i].name);
    
            if (it != assets.loadedTextures.end()) {
                const Texture2D& tex = it->second;
    
                DrawTexturePro(
                    tex,
                    Rectangle{0, 0, (float)tex.width, (float)tex.height},
                    dest,
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }
        }

    }

    for (int i = 0; i < allItems.size(); i++) {
        //draw bottoms
        if(allItems[i].category == "hair" && allItems[i].equipped){
            auto it = assets.loadedTextures.find(allItems[i].name);
    
            if (it != assets.loadedTextures.end()) {
                const Texture2D& tex = it->second;
    
                DrawTexturePro(
                    tex,
                    Rectangle{0, 0, (float)tex.width, (float)tex.height},
                    dest,
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }
        }

    }

    for (int i = 0; i < allItems.size(); i++) {
        //draw bottoms
        if(allItems[i].category == "hat" && allItems[i].equipped){
            auto it = assets.loadedTextures.find(allItems[i].name);
    
            if (it != assets.loadedTextures.end()) {
                const Texture2D& tex = it->second;
    
                DrawTexturePro(
                    tex,
                    Rectangle{0, 0, (float)tex.width, (float)tex.height},
                    dest,
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }
        }

    }

    // draw equipped top
    // if (user.equippedTop == "Blue Dress") {
    //     DrawTexturePro(
    //         assets.blueDress,
    //         Rectangle{0, 0, (float)assets.blueDress.width, (float)assets.blueDress.height},
    //         dest,
    //         Vector2{0, 0},
    //         0.0f,
    //         WHITE
    //     );
    // }

    // later:
    // if (user.equippedHat == "Red Hat") { ... }
    // if (user.equippedBottom == "Black Pants") { ... }
}