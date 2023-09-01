/*
g++ -o music_player main.cpp -lsfml-audio -lsfml-system
*/
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
       cerr << "Usage: music_player <music_file.mp3>" << endl;
        return 1;
    }

    const string musicFilePath = argv[1];

    sf::Music music;

    if (!music.openFromFile(musicFilePath))
    {
       cerr << "Failed to open music file: " << musicFilePath << endl;
        return 1;
    }

    music.play();

    while (music.getStatus() == sf::Music::Playing)
    {
        // Add any additional features you want here, such as playback controls.

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
    