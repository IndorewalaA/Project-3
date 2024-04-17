#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

struct Song
{
    string isrc;
    double acousticness = 0;
    double danceability = 0;
    int duration = 0;
    double energy = 0;
    double instrumentality = 0;
    double key = 0; //NOT USED
    double livelihood = 0;
    double loudness = 1;
    int mode = 0; // NOT USED
    double speechiness = 0; // DONT USE IF YOU DONT WANT TO
    double tempo = 0;
    string time_signature;
    double valence = 0; // THIS IS SO COOLLLL
};

int main() {
    vector<Song> songList;
    ifstream input("updated_audio_features.csv");
    if (!input.is_open()) {
        cout << "File not open! Exiting program..." << endl;
        return 0;
    }
    // isrc,acousticness,danceability,duration_ms,energy,instrumentalness,key,liveness,loudness,mode,speechiness,
    // tempo,time_signature,valence,updated_on

    string header;
    getline(input, header);

    string line;
    while(getline(input, line)) {
        string temp;
        stringstream stream(line);
        Song song;

        getline(stream, song.isrc, ',');
        getline(stream, temp, ',');
        song.acousticness = stod(temp);
        getline(stream, temp, ',');
        song.danceability = stod(temp);
        getline(stream, temp, ',');
        song.duration = stoi(temp);
        getline(stream, temp, ',');
        song.energy = stod(temp);
        getline(stream, temp, ',');
        song.instrumentality = stod(temp);
        getline(stream, temp, ',');
        song.key = stod(temp);
        getline(stream, temp, ',');
        song.livelihood = stod(temp);
        getline(stream, temp, ',');
        song.loudness = stod(temp);
        getline(stream, temp, ',');
        song.mode = stoi(temp);
        getline(stream, temp, ',');
        song.speechiness = stod(temp);
        getline(stream, temp, ',');
        song.tempo = stod(temp);
        getline(stream, song.time_signature, ',');
        getline(stream, temp, ',');
        song.valence = stod(temp);
        getline(stream, temp, '\n');
        songList.push_back(song);
    }

    cout << songList.size() << endl;
    return 0;
}