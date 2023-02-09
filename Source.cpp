#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Camera.h"
#include "Cube.h"
#define PI 3.14159265359

int main()
{
    int window_width = 1000;
    int window_height = 800;
    sf::ContextSettings context_settings;
    context_settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "3D testing", sf::Style::Default, context_settings);
    window.setMouseCursorVisible(false);
    sf::View view;
    view.setSize(window_width, window_height);
    view.setCenter(window_width / 2, window_height / 2);
    Camera camera;
    sf::Mouse mouse;
    camera.setSize(sf::Vector2f(window_width, window_height));
    camera.setCenter(Vector3f(0, 0, 0));
    std::vector<Cube*> cubes;
    sf::Texture side;
    if (!side.loadFromFile("assets/grass.png"))
        std::cout << "could not load wall side" << std::endl;
    /*
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Cube* cube = new Cube(50, Vector3f(-250 + 50 * i, -250 + 50 * j, -100));
            if (i > 0) cube->adjacent[0] = true;
            if (i < 9) cube->adjacent[1] = true;
            if (j > 0) cube->adjacent[2] = true;
            if (j < 9) cube->adjacent[3] = true;
            cubes.push_back(cube);
        }
    }
   */
    Cube* cube = new Cube(50, Vector3f(0, 0, -100), &side);
    cubes.push_back(cube);
    cube = new Cube(50, Vector3f(100, 100, 200), &side);
    cubes.push_back(cube);
    cube = new Cube(50, Vector3f(200, 50, 300), &side);
    cubes.push_back(cube);
    cube = new Cube(50, Vector3f(-100, 0, 0), &side);
    cubes.push_back(cube);
    float dt = 0;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                view.setSize(event.size.width, event.size.height);
                camera.setSize(sf::Vector2f(event.size.width, event.size.height));
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                    camera.moving_states[0] = true;
                if (event.key.code == sf::Keyboard::W)
                    camera.moving_states[1] = true;
                if (event.key.code == sf::Keyboard::D)
                    camera.moving_states[2] = true;
                if (event.key.code == sf::Keyboard::A)
                    camera.moving_states[3] = true;
                if (event.key.code == sf::Keyboard::Q)
                    camera.moving_states[4] = true;
                if (event.key.code == sf::Keyboard::E)
                    camera.moving_states[5] = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::S)
                    camera.moving_states[0] = false;
                if (event.key.code == sf::Keyboard::W)
                    camera.moving_states[1] = false;
                if (event.key.code == sf::Keyboard::D)
                    camera.moving_states[2] = false;
                if (event.key.code == sf::Keyboard::A)
                    camera.moving_states[3] = false;
                if (event.key.code == sf::Keyboard::Q)
                    camera.moving_states[4] = false;
                if (event.key.code == sf::Keyboard::E)
                    camera.moving_states[5] = false;
            }
        }
        camera.update(mouse, window, dt);
        std::vector<Cube*> sorted_cubes;
        if (cubes.size() > 0)
        {
            for (Cube* cube1 : cubes)
            {
                bool added = false;
                float displacement1 = (cube1->position - camera.position).length();
                for (int i = 0; i < sorted_cubes.size(); i++)
                {
                    Cube* cube2 = sorted_cubes[i];
                    float displacement2 = (cube2->position - camera.position).length();
                    if (displacement2 < displacement1)
                    {
                        sorted_cubes.insert(sorted_cubes.begin() + i, cube1);
                        added = true;
                        break;
                    }
                }
                if (!added)
                    sorted_cubes.push_back(cube1);
                cube1->update(camera);
            }
        }

        // window.setView(view);
        window.clear(sf::Color(210, 210, 210, 255));
        for (Cube* cube : sorted_cubes)
        {
            window.draw(*cube);
        }
        window.draw(camera);
        window.display();
        // std::cout << 1 / dt << std::endl;
        dt = clock.restart().asSeconds();
    }

    return 0;
}