#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

struct Song
{
    string isrc;
    double acousticness;
    double danceability;
    double duration;
    double energy;
    double instrumentality;
    double key; //NOT USED
    double livelihood;
    double loudness;
    double mode; // NOT USED
    double speechiness; // DONT USE IF YOU DONT WANT TO
    double tempo;
    double valence; // THIS IS SO COOLLLL
};

int main() {
    vector<Song> songList;
    ifstream input("updated_audio_features.csv");

    return 0;
}