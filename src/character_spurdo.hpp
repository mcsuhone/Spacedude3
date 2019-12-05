#pragma once

#include "character.hpp"

// Unique character "template"
// Makes use of functions held within Character class.
// Also used to store all unique attributes of a character

class CharacterSpurdo : public Character {
public:
    CharacterSpurdo() :
    Character("src/Textures/duderinosmall.png", "Spurdo", 100, 7.0f, 1.5f, RectHitbox(70.f, 70.f)) {}
private:
};
