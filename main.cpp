/*
g++ -o music_player main.cpp -lsfml-audio -lsfml-system
*/
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
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
  music.play();
  sf::Clock clock;
  const int progressBarWidth = 50; // Width of the progress bar

  while (music.getStatus() == sf::Music::Playing) {
    // Calculate elapsed time in seconds
    float elapsedTime = clock.getElapsedTime().asSeconds();

    // Print the progress bar
    cout << "Playing [";
    int progress = static_cast<int>(
        (elapsedTime / music.getDuration().asSeconds()) * progressBarWidth);
    for (int i = 0; i < progressBarWidth; ++i) {
      if (i < progress)
        cout << "=";
      else
        cout << " ";
    }
    cout << "] " << elapsedTime << "s\r";
    cout.flush();

    // Add any additional features you want here, such as playback controls.

    usleep(100000); // Sleep for 100 milliseconds
  }

  cout << endl; // Print a newline after stopping

  return 0;
}
