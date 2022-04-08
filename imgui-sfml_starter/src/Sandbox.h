#pragma once

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <filesystem>

struct MyShape
{
	MyShape(const char* t, std::unique_ptr<sf::Shape> s)
		: type(t), shape(std::move(s)), id(MyShape::count++) {}

	std::unique_ptr<sf::Shape> shape;
	const char* type = nullptr;
	bool isClicked = false;
	int id = 0;
	static int count;

};

class Sandbox
{
public:
	Sandbox();
	~Sandbox();
	inline bool IsRunning() const { return m_IsRunning; }

	void HandleInput();

	void Update();
	void Draw();
private:

	void DrawLines();
	void ShapesGUI();
	void HandleUserInput();
	void RenderText();
	void DrawTexture();
	void LoadTexture();
	void MouseClicking();
	void TextInput();
private:

	std::vector<MyShape> m_Shapes;	

	std::unique_ptr<sf::RenderWindow> m_Window;
	sf::Clock m_DeltaClock;

	bool m_IsRunning = false;
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::Event m_Event;

	const std::array<sf::Color, 5> m_ColorChoices = { sf::Color::White, sf::Color::Magenta, sf::Color::Green, sf::Color::Blue, sf::Color::Cyan };

};

