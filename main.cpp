/*
g++ -o music_player main.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
*/
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h> // For usleep

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: music_player <music_file.wav>" << endl;
    return 1;
  }

  const string musicFilePath = argv[1];

  sf::Music music;

  if (!music.openFromFile(musicFilePath)) {
    cerr << "Failed to open music file: " << musicFilePath << endl;
    return 1;
  }

  music.play();
  sf::Clock clock;

  // Create an SFML window that automatically adjusts its size
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Shader Animation");

  // Create a shader and load it from a file (e.g., shader.frag)
  sf::Shader shader;
  if (!shader.loadFromFile("shader.frag", sf::Shader::Fragment)) {
    cerr << "Failed to load shader" << endl;
    return 1;
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (music.getStatus() == sf::Music::Playing) {
      // Calculate elapsed time in seconds
      float elapsedTime = clock.getElapsedTime().asSeconds();

      // Set the time and resolution uniforms for the shader
      shader.setUniform("time", elapsedTime);
      shader.setUniform("resolution", sf::Glsl::Vec2(window.getSize()));

      // Clear the window
      window.clear();

      // Apply the shader effect to the entire window
      sf::RectangleShape fullscreenRect(sf::Vector2f(window.getSize().x, window.getSize().y));
      fullscreenRect.setFillColor(sf::Color::White);
      window.draw(fullscreenRect, &shader);

      // Display the result
      window.display();

      usleep(10000); // Sleep for 10 milliseconds (adjust as needed)
    } else {
      window.close();
    }
  }

  return 0;
}
