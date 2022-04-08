#include "Sandbox.h"

int MyShape::count = 0;

Sandbox::Sandbox()
	: m_IsRunning(true)
{
	m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "ImGui SFML Demo");
	m_Window->setFramerateLimit(60);
	ImGui::SFML::Init(*m_Window);
    LoadTexture();
}

Sandbox::~Sandbox()
{
    ImGui::SFML::Shutdown();
}

void Sandbox::Update()
{
    HandleInput();
    ImGui::SFML::Update(*m_Window, m_DeltaClock.restart());
    HandleUserInput();

    MouseClicking();
    Draw();
}

void Sandbox::HandleInput()
{
    while (m_Window->pollEvent(m_Event)) {
        ImGui::SFML::ProcessEvent(m_Event);

        if (m_Event.type == sf::Event::Closed) {
            m_IsRunning = false;
            m_Window->close();
        }
    }
}

void Sandbox::Draw()
{
    m_Window->clear();
    ImGui::Begin("Sandbox");

    DrawTexture();

    for (auto& shape : m_Shapes)
        m_Window->draw(*shape.shape);

    DrawLines();
    RenderText();
    ShapesGUI();
    ImGui::End();

    ImGui::SFML::Render(*m_Window);
    m_Window->display();
}


void Sandbox::ShapesGUI()
{
    ImGui::Text(fmt::format("frame rate: {}", ImGui::GetIO().Framerate).c_str());
    ImGui::Separator();
    ImGui::Separator();
    TextInput();
    ImGui::Separator();
    ImGui::Separator();

    if (auto button = ImGui::Button("Spawn Circle");button)
    {
        auto& shape = m_Shapes.emplace_back("Circle", std::make_unique<sf::CircleShape>(50.0f));
        shape.shape->setFillColor(m_ColorChoices[rand() % 5]);
    }
    ImGui::SameLine();
    if (auto Rectbutton = ImGui::Button("Spawn Rectangle"); Rectbutton)
    {
        auto& shape = m_Shapes.emplace_back("Rectangle", std::make_unique<sf::RectangleShape>(sf::Vector2f(50.0f, 50.0f)));
        if (rand() % 2 == 0)
        {
            shape.shape->setTexture(&m_Texture);
        }
    }
    ImGui::Separator();
    ImGui::Separator();

    for (auto& shape : m_Shapes)
    {
        ImGui::Checkbox(fmt::format("{} ID: {}", shape.type, shape.id).c_str(), &shape.isClicked);
    }

    ImGui::Separator();
    ImGui::Separator();
    for (auto& shape : m_Shapes)
    {
        ImGui::Text(fmt::format("{} ID: {}\nx pos: {:f}\ny pos: {:f}", shape.type, shape.id, shape.shape->getPosition().x, shape.shape->getPosition().y).c_str());
        ImGui::Separator();
    }
}

void Sandbox::DrawLines()
{
    sf::CircleShape c1(25.0f);
    c1.setPosition(0.0f, 50.0f);
    sf::CircleShape c2(25.0f);
    c2.setPosition(200.0f, 50.0f);

    sf::Vertex line[] =
    {
        sf::Vertex(c1.getPosition() + sf::Vector2(c1.getRadius(), c1.getRadius()), sf::Color::Red),
        sf::Vertex(c2.getPosition(), sf::Color::Red)
    };

    m_Window->draw(c1);
    m_Window->draw(c2);
    m_Window->draw(line, 2, sf::Lines);
}

void Sandbox::HandleUserInput()
{
    for (auto& shape : m_Shapes)
    {
        if (shape.isClicked)
        {
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
        }
        else
        {
            shape.shape->setOutlineThickness(0.0f);
        }
    }
}

void Sandbox::RenderText()
{
    sf::Font font;
    font.loadFromFile("assets/Fonts/arial.ttf");
    sf::Text text("Welcome to Sandbox", font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(m_Window->getSize().x * 0.5f - text.getLocalBounds().width * 0.5f, 0);
    m_Window->draw(text);
}

void Sandbox::DrawTexture()
{  
    m_Window->draw(m_Sprite);
}

void Sandbox::LoadTexture()
{
    std::string path = std::filesystem::current_path().u8string();
    spdlog::info("path: {}",path );
    if (!m_Texture.loadFromFile("assets/Textures/WoodTexture.jpg"))
    {
        // error...
        spdlog::error("failed to load texture");
    }
       
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setScale(sf::Vector2f(0.1f, 0.1f));
}

void Sandbox::MouseClicking()
{
    auto mousePos = sf::Mouse::getPosition(*m_Window);

    for(auto& shape : m_Shapes)
        if (m_Event.type == sf::Event::MouseButtonPressed) // && myMouseBool == false
        {
            // check mouse pos vs global bounds of your object
            if (shape.shape->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                spdlog::info("shape {} pressed!", shape.id);
            }
            // mymousebool =true
        }
        // if event is mouserelease - set mymousebool false
        //if (event.type == sf::Event::MouseButtonReleased)
}

void Sandbox::TextInput()
{
    const int buffsize = 128;
    char buffer[buffsize] = "Input text here:";
    bool isChanged;
    buffer, isChanged = ImGui::InputText("", buffer, buffsize, 0);
    std::string textstr(buffer);
    // press enter to stop
    if (isChanged)
        spdlog::info("Your message: {}", buffer);
}
