#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "GameObjects/wall.hpp"
#include "GameObjects/destructable_wall.hpp"
#include "GameObjects/zombie.hpp"
#include "player.hpp"

struct Map {
    std::vector<sf::Sprite*> background;
    sf::Texture* background_texture = new sf::Texture();
    PhysicsVector player_location;
    std::vector<PhysicsVector> zombie_spawns;
    std::vector<GameObject*> objects;
    std::vector<Zombie*> enemies;
    int enemies_left = 0;
    int enemies_total = 0;
    GameObject* goal = new GameObject(PhysicsVector(0, 0), "src/Textures/portal.png", RectHitbox(5.f, 5.f));
    sf::Sound portal_sound;
    sf::SoundBuffer portal_buffer;
};

class MapLoader {
public:
    /* Helper method to split a string given as input. Return a vector containing the token split by the delimiter */
    static std::vector<std::string> Split(std::string str, char delim) {
        std::vector<std::string> split;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            split.push_back(token);
        }
        return split;
    }

    /* Read the map file given as parameter and create game objects according to it.
       Returns a map struct. */
    static Map LoadMap(std::string filename) {
        std::ifstream is(filename); // Open the file to be read
        if (is.fail()) {
            is.close();
            std::cout << "Couldn't open the file!" << std::endl;
            exit(EXIT_FAILURE);
        }

        float x = 0.0f, y = 0.0f;
        Map map;
        std::string line;

        while (std::getline(is, line)) {
            if (line == "#background") {
                std::getline(is, line);

                if (!map.background_texture->loadFromFile(line)) {
                    std::cout << "ERROR while opening" << line << std::endl;
                }
            }

            else if (line == "#map") {
                while (std::getline(is, line)) {
                    x = 0.0f;
                    std::vector<std::string> line_objects = Split(line, '-');
                    for (auto object : line_objects) {
                        // Player
                        if (object == "P") {
                            map.player_location = PhysicsVector(x + 32, y + 32);
                        }

                        // Wall object
                        else if (object == "w") {
                            Wall* wall = new Wall(PhysicsVector(x, y));
                            map.objects.push_back(wall);
                        }

                        // Destructable wall object
                        else if (object == "d") {
                            DestructableWall* d_wall = new DestructableWall(PhysicsVector(x, y));
                            map.objects.push_back(d_wall);
                        }

                        // Zombie
                        else if (object == "Z") {
                            Zombie* zombie = new Zombie(PhysicsVector(x + 32, y + 32));
                            map.objects.push_back(zombie);
                            map.enemies.push_back(zombie);
                            map.enemies_left++;
                        }

                        // Zombie spawner
                        else if (object == "S") {
                            map.zombie_spawns.push_back(PhysicsVector(x + 32, y + 32));
                        }

                        // Goal
                        else if (object == "X") {
                            map.goal->SetPosition(PhysicsVector(x + 32, y + 32));
                            map.goal->SetOrigin(47, 47);
                            map.goal->SetHitboxPosition(map.goal->GetPosition() + PhysicsVector(42, 42));
                            map.goal->collidable_ = false;
                        }

                        x += 64.f;
                    }

                    y += 64.f;
                }
            }
        }

        auto texture_size = map.background_texture->getSize();
        int offset = 500;
        for (int j = -offset; j < (y + offset); j += texture_size.y) {
            for (int i = -offset; i < (x + offset); i += texture_size.x) {
                sf::Sprite* sprite = new sf::Sprite();
                sprite->setTexture(*map.background_texture);
                sprite->setPosition(i, j);
                map.background.push_back(sprite);
            }
        }

        is.close();
        return map;
    }

    static void SpawnZombies(Map& map) {
        for (PhysicsVector z : map.zombie_spawns) {
            Zombie* zombie = new Zombie(PhysicsVector(z.x, z.y));
            map.objects.push_back(zombie);
            map.enemies.push_back(zombie);
            map.enemies_left++;
        }
    }
};
