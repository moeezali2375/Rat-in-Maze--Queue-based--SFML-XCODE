
//====================================================
//
//              ###    ###    ###    ##  ##     ##
//              ## #  # ##   ## ##   ##  ####   ##
//              ##  ##  ##  ##   ##  ##  ##  ## ##
//              ##      ##  #######  ##  ##    ###
//              ##      ##  ##   ##  ##  ##     ##
//
//====================================================

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "board.cpp"
#include "stacks.cpp"
using namespace std;
void display_board(board &a, sf::RenderWindow &window);
int option_selector(int x, int y);
int option_selector2(int x, int y);

void enter(int &i, int &j, board &a, stacks &stack, int flag);

int main()
{

    //=========================================================
    //
    //               ####  ######    ###    #####    ######
    //              ##       ##     ## ##   ##  ##     ##
    //               ###     ##    ##   ##  #####      ##
    //                 ##    ##    #######  ##  ##     ##
    //              ####     ##    ##   ##  ##   ##    ##
    //
    //=========================================================

    sf::RenderWindow start_screen(sf::VideoMode(1200, 628), "Rat in Maze", sf::Style::Close);

    sf::Texture background_texture;
    background_texture.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#3/Assignment 3/Rat in Maze/Rat in Maze/wallpaper.png");

    sf::Sprite background;
    background.setTexture(background_texture);

    sf::Font font;
    font.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#3/Assignment 3/Rat in Maze/Rat in Maze/font.ttf");

    sf::Text start_game("Start Game", font, 40);
    start_game.setColor(sf::Color::Black);
    start_game.setPosition(708, 400);
    sf::Text exit_game("Exit Game", font, 40);
    exit_game.setColor(sf::Color::Black);
    exit_game.setPosition(708, 445);

    while (start_screen.isOpen())
    {
        sf::Event event;
        while (start_screen.pollEvent(event))
        {
            start_screen.clear();
            start_screen.draw(background);
            start_screen.draw(start_game);
            start_screen.draw(exit_game);
            start_screen.display();

            if (event.type == sf::Event::Closed)
            {
                start_screen.close();
                break;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(start_screen);
                int check = option_selector(mouse_position.x, mouse_position.y);
                if (check == 1)
                {
                    //=================================================================
                    //
                    //               ####  ######    ###    #####    ######   ####
                    //              ##       ##     ## ##   ##  ##     ##    #    #
                    //               ###     ##    ##   ##  #####      ##       ##
                    //                 ##    ##    #######  ##  ##     ##     ##
                    //              ####     ##    ##   ##  ##   ##    ##    ######
                    //
                    //=================================================================

                    cout << "Enter the size of the 2-D matrix: ";
                    int size;
                    cin >> size;

                    sf::Texture mouse;
                    mouse.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#3/Assignment 3/Rat in Maze/Rat in Maze/rat.png");
                    sf::Sprite rat_sprite;
                    rat_sprite.setTexture(mouse);
                    rat_sprite.setPosition(580, 350);
                    int flag = 0;
                    sf::Texture rep;
                    rep.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#3/Assignment 3/Rat in Maze/Rat in Maze/replay.png");
                    sf::Sprite replay;
                    replay.setTexture(rep);
                    replay.setPosition(800, 300);

                    cout << "1.Left-Up Corner: " << endl;
                    cout << "2.Right-Up Corner: " << endl;
                    cout << "3.Left-Down Corner: " << endl;
                    cout << "4.Right-Down Corner: " << endl;
                    cout << "Please enter the source cell: " << endl;
                    int source;
                    cin >> source;
                    int destination;
                    int ii = 0, j = 0;
                    int i = 0;
                    while (i < 1)
                    {
                        cout << "Please enter the destination cell: " << endl;
                        cin >> destination;
                        if (destination == source)
                        {
                            cout << "Please don't choose the destination same as source!\n";
                            i--;
                        }
                        i++;
                    }
                replay:
                    board a(size, size);
                    a.load_data();

                    if (source == 1)
                    {
                        ii = 0;
                        j = 0;
                        a.array[ii][j] = 0;
                    }
                    else if (source == 4)
                    {
                        ii = size - 1;
                        j = size - 1;
                        a.array[ii][j] = 0;
                    }
                    else if (source == 2)
                    {
                        ii = 0;
                        j = size - 1;
                        a.array[ii][j] = 0;
                    }
                    else if (source == 3)
                    {
                        ii = size - 1;
                        j = 0;
                        a.array[ii][j] = 0;
                    }

                    a.set(destination);

                    start_screen.close();

                    sf::RenderWindow game_screen(sf::VideoMode(1200, 628), "Rat in Maze", sf::Style::Close);

                    stacks stack(a.rows * a.columns);

                    //=====================================================
                    //
                    //               ####      ###    ###    ###  #####
                    //              ##        ## ##   ## #  # ##  ##
                    //              ##  ###  ##   ##  ##  ##  ##  #####
                    //              ##   ##  #######  ##      ##  ##
                    //               ####    ##   ##  ##      ##  #####
                    //
                    //=====================================================

                    while (game_screen.isOpen())
                    {
                        sf::Event event2;
                        while (game_screen.pollEvent(event2))
                        {
                            game_screen.clear(sf::Color::White);
                            game_screen.draw(rat_sprite);
                            game_screen.draw(replay);
                            display_board(a, game_screen);
                            game_screen.display();

                            if (event2.type == sf::Event::Closed)
                            {
                                game_screen.close();
                                break;
                            }

                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mouse2_position = sf::Mouse::getPosition(game_screen);
                                if (option_selector(mouse2_position.x, mouse2_position.y) == 3)
                                {
                                    enter(ii, j, a, stack, flag);
                                    if (flag == 1)
                                    {
                                        cout << "hui\n";
                                        game_screen.clear(sf::Color::Green);
                                        sf::Text you_win("GAME ENDED!", font, 100);
                                        you_win.setColor(sf::Color::Black);
                                        you_win.setPosition(600, 300);
                                    }
                                }
                                else if (option_selector(mouse2_position.x, mouse2_position.y) == 4)
                                {
                                    goto replay;
                                }
                            }
                        }
                    }
                }
                else if (check == 2)
                {
                    cout << "Game closed successfully\n";
                    start_screen.close();
                }
            }
        }
    }
}

void display_board(board &a, sf::RenderWindow &window)
{
    sf::Texture rat_texture;
    rat_texture.loadFromFile("/Users/moeezali/Documents/VS/SEMESTER#3/Assignment 3/Rat in Maze/Rat in Maze/rat.png");
    sf::Sprite rat(rat_texture);

    sf::Texture t;
    sf::Sprite s(t);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.columns; j++)
        {
            int w = 25;
            if (a.array[i][j] == 1)
            {
                s.setTextureRect(sf::IntRect(0, 0, w, w));
                s.setColor(sf::Color(255, 165, 0));
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }

            if (a.array[i][j] == -1)
            {
                s.setTextureRect(sf::IntRect(0, 0, w, w));
                s.setColor(sf::Color::Blue);
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }

            if (a.array[i][j] == 2)
            {
                s.setTextureRect(sf::IntRect(0, 0, w, w));
                s.setColor(sf::Color::Red);
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }

            if (a.array[i][j] == 0)
            {
                s.setTextureRect(sf::IntRect(0, 0, w, w));
                s.setColor(sf::Color::Yellow);
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }

            if (a.array[i][j] == 3)
            {
                s.setTextureRect(sf::IntRect(0, 0, w, w));
                s.setColor(sf::Color::Green);
                s.setPosition(j * (w + 10) + 50, i * (w + 10) + 100);
                window.draw(s);
            }
        }
    }
}

int option_selector(int x, int y)
{
    if (x >= 706 && x <= 892 && y >= 400 && y <= 442)
        return 1;
    if (x >= 706 && x <= 892 && y >= 444 && y <= 486)
        return 2;
    return 0;
}

int option_selector2(int x, int y)
{
    if (x >= 628 && x <= 1000 && y >= 360 && y <= 506)
        return 3;
    if (x >= 794 && x <= 1092 && y >= 380 && y <= 506)
        return 4;
    return 0;
}

void enter(int &i, int &j, board &a, stacks &stack, int flag)
{
    // GAME_STOP
    if (a.array[i][j] == 3)
    {
        flag = 1;
        return;
    }

    // PUSH_DOWN
    if (i >= 0 && i < a.rows - 1 && a.array[i + 1][j] != -1 && a.array[i + 1][j] != 0 && a.array[i + 1][j] != 2)
    {
        a.array[i][j] = 0;
        stack.push(++i, j);
        // a.array[i][j] = 4;
        return;
    }

    // PUSH_RIGHT
    if (j >= 0 && j < a.rows - 1 && a.array[i][j + 1] != -1 && a.array[i][j + 1] != 0 && a.array[i][j + 1] != 2)
    {
        a.array[i][j] = 0;
        stack.push(i, ++j);
        // a.array[i][j] = 4;
        return;
    }

    // PUSH_UP
    if (i > 0 && i <= a.rows - 1 && a.array[i - 1][j] != -1 && a.array[i - 1][j] != 0 && a.array[i - 1][j] != 2)
    {
        a.array[i][j] = 0;
        stack.push(--i, j);
        // a.array[i][j] = 4;
        return;
    }

    // PUSH_LEFT
    if (j > 0 && j <= a.rows - 1 && a.array[i][j - 1] != -1 && a.array[i][j - 1] != 0 && a.array[i][j - 1] != 2)
    {
        a.array[i][j] = 0;
        stack.push(i, --j);
        // a.array[i][j] = 4;
        return;
    }
    // BACK
    a.array[i][j] = 2;
    stack.pop(i, j);
    stack.pop(i, j);
    a.array[i][j] = 0;
}
