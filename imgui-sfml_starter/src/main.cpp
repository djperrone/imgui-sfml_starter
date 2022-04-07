#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <spdlog/spdlog.h>

#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

static bool MOUSEBUTTONPRESSED = FALSE;
int main() {



    struct MyShape
    {
        MyShape(const char* t, sf::Shape* s, int i)
            : type(t), shape(s), id(i) {}
        sf::Shape* shape;
        const char* type;
        int id;
    };

    std::vector<std::pair<bool, MyShape>> shapes;

    //shapes.push_back(std::pair(false, MyShape(sf::CircleShape(100.0f), 0)));



    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    std::vector<sf::CircleShape> circles;

    bool checkBox = false;

    float sliderFloat = 0.0f;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    bool test = false;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Shape Spawner");
        // ImGui::Button("Look at this pretty button");        


        auto button = ImGui::Button("Spawn Circle");
        if (button)
        {
            shapes.push_back(std::pair(false, MyShape("Circle", new sf::CircleShape(50.0f), shapes.size())));
        }

        auto Rectbutton = ImGui::Button("Spawn Rectangle");
        if (Rectbutton)
        {
            //MyShape shape = MyShape(new sf::RectangleShape(sf::Vector2f(10.0f, 10.0f)), 2);
            shapes.push_back(std::pair(false, MyShape("Rectangle", new sf::RectangleShape(sf::Vector2f(50.0f, 50.0f)), shapes.size())));

        }



        ImGui::End();

        /* ImGui::SliderFloat("slider",&sliderFloat, 0.0f,100.0f);*/

        shape.setRadius(sliderFloat);
        window.clear();

        for (auto& shape : shapes)
        {
            window.draw(*shape.second.shape);
        }

        ImGui::Begin("Circle List");
        int index = 0;
        for (auto& shape : shapes)
        {
            ImGui::Checkbox(fmt::format("{} ID: {}", shape.second.type, shape.second.id).c_str(), &shape.first);
        }
        ImGui::End();

        std::size_t i = 0;
        for (auto& [state, shape] : shapes)
        {

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (MOUSEBUTTONPRESSED == true)
                {
                    MOUSEBUTTONPRESSED = false;
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (shape.shape->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        if (!state)
                            state = true;
                        else
                        {
                            state = false;
                        }

                        spdlog::info("testing\n");

                    }
                }

            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                MOUSEBUTTONPRESSED = true;
            }


            if (state)
            {
                /*shape.shape.move(5.0f, 5.0f);*/
                //ImGui::Begin("Circle Controller");
                shape.shape->setOutlineColor(sf::Color::Red);
                shape.shape->setOutlineThickness(5.0f);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    shape.shape->move(0.0f, 1.0f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    shape.shape->move(0.0f, -1.0f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    shape.shape->move(1.0f, 0.0f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    shape.shape->move(-1.0f, 0.0f);
                }

                ImGui::Begin("Shape Info");
                ImGui::Text(fmt::format("{} ID: {}\nx pos: {}\ny pos: {}", shape.type, shape.id, shape.shape->getPosition().x, shape.shape->getPosition().y).c_str());
                ImGui::End();
            }
            else
            {
                shape.shape->setOutlineThickness(0.0f);

            }

        }

        ImGui::SFML::Render(window);
        window.display();

        if (sliderFloat > 50)
            spdlog::info("testing\n");
    }

    ImGui::SFML::Shutdown();
}