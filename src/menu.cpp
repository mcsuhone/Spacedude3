#include "menu.hpp"

/* Construct and load default main menu */
Menu::Menu() {
    if (!main_menu_texture_.loadFromFile("src/Textures/MenuButtons/mainmenu.png")) {
        // Error checking
    }
    if (!main_menu_background_.loadFromFile("src/Textures/MenuButtons/menu_background.png")) {
        // Error checking
    }
    if (!font_.loadFromFile("src/Textures/MenuButtons/MenuFont.ttf")) {
        // Error checking
    }
    menu_status = 0;
    Load_MainMenu();
    Draw();
}

Menu::~Menu() {
    for (sf::Sprite* i : menu_items_) {
        delete i;
    }
    for (sf::Text* i : menu_text_items_) {
        delete i;
    }
    menu_items_.clear();
    menu_text_items_.clear();
}

/* Draws all the sprites in the menu items vector */
void Menu::Draw() {
    sf::Sprite background;
    background.setTexture(main_menu_background_);
    main_window->draw(background);
    for (sf::Sprite* it : menu_items_) {
        main_window->draw(*it);
    }
    for (sf::Text* it : menu_text_items_) {
        main_window->draw(*it);
    }
    if (menu_status == 2) {
        std::string inputstr = playername_.getString().toAnsiString();
        sf::Text userinput;
        userinput.setFont(font_);
        userinput.setCharacterSize(50);
        userinput.setPosition(main_window->getSize().x / 3.4 , main_window->getSize().y / 3);
        userinput.setString(inputstr);
        main_window->draw(userinput);
    }
}

/* Initialize the window and loads main menu by default. menu_status indicates
   the screen to be loaded. 0 = Main menu, 1 = Settings menu... */
void Menu::Init() {
    main_window->setFramerateLimit(g_fps);
    while (main_window->isOpen()) {
        main_window->clear();
        sf::Event event;
        main_window->pollEvent(event);

        // Main menu
        if (menu_status == 0) {
            if (event.type == sf::Event::Closed) {
                main_window->close();
            }            sf::Text text;

            if (event.type == sf::Event::MouseMoved) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[0]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[0]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[1]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[1]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[2]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[2]->setColor(sf::Color(sf::Color::White));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    Load_NameMenu();
                }

                else if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    Load_SettingsMenu();
                }

                else if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                    main_window->close();
                }


            }
        }

        // Settings menu
        else if (menu_status == 1) {
            if (event.type == sf::Event::Closed) {
                main_window->close();
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[0]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[0]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[1]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[1]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[2]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[2]->setColor(sf::Color(sf::Color::White));
                }

            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    Load_MainMenu();
                }

                else {
                    if (sound_on) {
                        if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                            menu_items_[1]->setTextureRect(sf::Rect(0, 840, 250, 120));
                            sound_on = false;
                        }
                    }

                    else {
                        if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                            menu_items_[1]->setTextureRect(sf::Rect(0, 720, 250, 120));
                            sound_on = true;
                        }
                    }

                    if (music_on) {
                        if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                            menu_items_[2]->setTextureRect(sf::Rect(0, 600, 250, 120));
                            music_on = false;
                        }
                    }

                    else {
                        if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                            menu_items_[2]->setTextureRect(sf::Rect(0, 480, 250, 120));
                            music_on = true;
                        }
                    }
                }
            }
        }

        // Name menu
        else if (menu_status == 2) {
            sf::String name;

            if (event.type == sf::Event::Closed) {
                main_window->close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8 && playername_.getString().getSize() > 0) {
                    sf::String temporary = playername_.getString();
                    temporary.erase(temporary.getSize() - 1, temporary.getSize());
                    playername_.setString(temporary);
                }

                else if (event.text.unicode < 127 && event.text.unicode > 31 && playername_.getString().getSize() < 15) {
                    name += event.text.unicode;
                    playername_.setString(playername_.getString() + name);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                Load_PlayMenu();
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[0]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[0]->setColor(sf::Color(sf::Color::White));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    Load_MainMenu();
                }
            }
        }

        // Play menu
        else if (menu_status == 3) {
            if (event.type == sf::Event::Closed) {
                main_window->close();
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[0]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[0]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[1]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[1]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[2]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[2]->setColor(sf::Color(sf::Color::White));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    Load_NameMenu();
                }

                else if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    Load_HostMenu();
                }

                else if (menu_items_[2]->getGlobalBounds().contains(mouse_pos)) {
                    Load_JoinMenu();
                }


            }
        }

        // Host menu
        else if (menu_status == 4) {
            if (event.type == sf::Event::Closed) {
                main_window->close();
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[0]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[0]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[1]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[1]->setColor(sf::Color(sf::Color::White));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    Load_PlayMenu();
                }

                else if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    Clear_MenuItems();
                    scene->Init();
                    delete scene;
                }
            }
        }

        // Join menu
        else if (menu_status == 5) {
            if (event.type == sf::Event::Closed) {
                main_window->close();
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[0]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[0]->setColor(sf::Color(sf::Color::White));
                }

                if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    menu_items_[1]->setColor(sf::Color(sf::Color::Red));
                }
                else {
                    menu_items_[1]->setColor(sf::Color(sf::Color::White));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Mouse cursor;
                sf::Vector2i mouse_position = cursor.getPosition(*main_window);
                sf::Vector2f mouse_pos(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));

                if (menu_items_[0]->getGlobalBounds().contains(mouse_pos)) {
                    Load_PlayMenu();
                }

                else if (menu_items_[1]->getGlobalBounds().contains(mouse_pos)) {
                    Clear_MenuItems();
                    scene->Init();
                    delete scene;
                }
            }
        }
        Draw();
        main_window->display();
    }
}

/* Add main menu sprites to the menuitems vector */
void Menu::Load_MainMenu() {
    Clear_MenuItems();
    menu_status = 0;
    sf::Vector2u window_size = main_window->getSize();
    sf::Sprite* play = new sf::Sprite();
    sf::Sprite* settings = new sf::Sprite();
    sf::Sprite* exit = new sf::Sprite();

    play->setTexture(main_menu_texture_);
    play->setTextureRect(sf::Rect(0, 0, 250, 120));
    play->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 4));

    settings->setTexture(main_menu_texture_);
    settings->setTextureRect(sf::Rect(0, 120, 250, 120));
    settings->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 2.4));

    exit->setTexture(main_menu_texture_);
    exit->setTextureRect(sf::Rect(0, 240, 250, 120));
    exit->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 1.7));

    menu_items_.push_back(play);
    menu_items_.push_back(settings);
    menu_items_.push_back(exit);
}

/* Add settings menu sprites to the menuitems vector */
void Menu::Load_SettingsMenu() {
    Clear_MenuItems();
    menu_status = 1;
    sf::Vector2u window_size = main_window->getSize();
    sf::Sprite* music = new sf::Sprite();
    sf::Sprite* sound = new sf::Sprite();
    sf::Sprite* back = new sf::Sprite();

    back->setTexture(main_menu_texture_);
    back->setTextureRect(sf::Rect(0, 360, 250, 120));
    back->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 1.7));

    music->setTexture(main_menu_texture_);
    music->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 4));

    if (music_on) {
        music->setTextureRect(sf::Rect(0, 480, 250, 120));
    }
    else {
        music->setTextureRect(sf::Rect(0, 600, 250, 120));
    }

    sound->setTexture(main_menu_texture_);
    sound->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 2.4));

    if (sound_on) {
        sound->setTextureRect(sf::Rect(0, 720, 250, 120));
    }
    else {
        sound->setTextureRect(sf::Rect(0, 840, 250, 120));
    }

    menu_items_.push_back(back);
    menu_items_.push_back(sound);
    menu_items_.push_back(music);
}

/* Add name menu sprites to the menuitems vector */
void Menu::Load_NameMenu() {
    Clear_MenuItems();
    menu_status = 2;
    sf::Vector2u window_size = main_window->getSize();
    sf::Sprite* back = new sf::Sprite();
    sf::Text* enter_name = new sf::Text();

    std::string str = "Enter player name (max 15 characters)";
    enter_name->setFont(font_);
    enter_name->setString(str);
    enter_name->setPosition(sf::Vector2f(window_size.x / 4.3 , window_size.y / 4));

    back->setTexture(main_menu_texture_);
    back->setTextureRect(sf::Rect(0, 360, 250, 120));
    back->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 1.7));

    menu_items_.push_back(back);
    menu_text_items_.push_back(enter_name);
}

/* Add play menu sprites to the menuitems vector */
void Menu::Load_PlayMenu() {
    Clear_MenuItems();
    menu_status = 3;
    sf::Vector2u window_size = main_window->getSize();
    sf::Sprite* back = new sf::Sprite();
    sf::Sprite* host = new sf::Sprite();
    sf::Sprite* join = new sf::Sprite();
    sf::Text* help = new sf::Text();

    std::string str = "Choose whether to host or join a game";
    help->setFont(font_);
    help->setString(str);
    help->setPosition(sf::Vector2f(window_size.x / 4.2 , window_size.y / 4));

    back->setTexture(main_menu_texture_);
    back->setTextureRect(sf::Rect(0, 360, 250, 120));
    back->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 1.7));

    host->setTexture(main_menu_texture_);
    host->setTextureRect(sf::Rect(0, 960, 250, 120));
    host->setPosition(sf::Vector2f(window_size.x / 5 , window_size.y / 3));

    join->setTexture(main_menu_texture_);
    join->setTextureRect(sf::Rect(0, 1080, 250, 120));
    join->setPosition(sf::Vector2f(window_size.x / 1.75 , window_size.y / 3));

    menu_items_.push_back(back);
    menu_items_.push_back(host);
    menu_items_.push_back(join);
    menu_text_items_.push_back(help);
}

/* Add host menu sprites to the menuitems vector */
void Menu::Load_HostMenu() {
    Clear_MenuItems();
    menu_status = 4;
    sf::Vector2u window_size = main_window->getSize();
    sf::Sprite* back = new sf::Sprite();
    sf::Sprite* play = new sf::Sprite();

    back->setTexture(main_menu_texture_);
    back->setTextureRect(sf::Rect(0, 360, 250, 120));
    back->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 1.7));

    play->setTexture(main_menu_texture_);
    play->setTextureRect(sf::Rect(0, 0, 250, 120));
    play->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 4));

    menu_items_.push_back(back);
    menu_items_.push_back(play);
}

/* Add join menu sprites to the menuitems vector */
void Menu::Load_JoinMenu() {
    Clear_MenuItems();
    menu_status = 5;
    sf::Vector2u window_size = main_window->getSize();
    sf::Sprite* back = new sf::Sprite();
    sf::Sprite* play = new sf::Sprite();

    back->setTexture(main_menu_texture_);
    back->setTextureRect(sf::Rect(0, 360, 250, 120));
    back->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 1.7));

    play->setTexture(main_menu_texture_);
    play->setTextureRect(sf::Rect(0, 0, 250, 120));
    play->setPosition(sf::Vector2f(window_size.x / 2.6 , window_size.y / 4));

    menu_items_.push_back(back);
    menu_items_.push_back(play);
}

/* Clear menu items vector of sprites */
void Menu::Clear_MenuItems() {
    for (sf::Sprite* i : menu_items_) {
        delete i;
    }
    for (sf::Text* i : menu_text_items_) {
        delete i;
    }
    menu_items_.clear();
    menu_text_items_.clear();
}