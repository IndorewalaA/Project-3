#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

//bubbles
struct Song
{
    // {isrc,acousticness,danceability,duration_ms,energy,instrumentalness,key,liveness,loudness,mode,speechiness,tempo,time_signature,valence,updated_on}
    string isrc;
    int mode = 0;           // NOT USED
    int duration_ms = 0;
    double acousticness = 0;
    double danceability = 0;
    double energy = 0;
    double instrumentalness = 0;
    double key = 0;         // NOT USED
    double liveness = 0;
    double loudness = 0;
    double speechiness = 0; // DONT USE IF YOU DONT WANT TO
    double tempo = 0;
    double valence = 0;     // THIS IS SO COOLLLL
    string time_signature;  // [3,7] - An estimated time signature(meter)... specify how many beats are in each bar (or measure)... ranges from 3 to 7 indicating time signatures of "3/4", to "7/4".
    string updated_time;
};

// Function to read the data from a CSV file into a vector of songs
vector<Song> readData(const string& filename){
    vector<Song> songList;
    ifstream input(filename);
    if(!input.is_open()){
        cout << "Error! cannot open file: " << filename << endl;
        return songList;
    }
    // string
    return songList;
}

int main() {
    vector<Song> songList;
    ifstream input("updated_audio_features.csv");
    if (!input.is_open()) {
        cout << "File not open! Exiting program..." << endl;
        return 0;
    }

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
        song.duration_ms = stoi(temp);
        getline(stream, temp, ',');
        song.energy = stod(temp);
        getline(stream, temp, ',');
        song.instrumentalness = stod(temp);
        getline(stream, temp, ',');
        song.key = stod(temp);
        getline(stream, temp, ',');
        song.liveness = stod(temp);
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

    bool runMenu = true;
    bool error;
    int menuOption = -1;
    cout << "Welcome to the Song Search Filter!" << endl;
    while (runMenu) {
        cout << endl;
        cout << "Select an action:" << endl;
        cout << "0. Exit Program" << endl;
        cout << "1. Filter Information" << endl;
        cout << "2. Search\n" << endl;
        string temp;
        cin >> temp;
        try {
            menuOption = stoi(temp);
        }
        catch(...) {
            //cout << "Error! Not a valid number!" << endl;
            //error = true;
            return true;

        }
        if (!error) {
            switch(menuOption){
                case 0:
                    runMenu = false;
                    break;
                case 1:
                    if(songList.empty()){
                        cout << "No songs available to display" << endl;
                    }
                    else{
                        static default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
                        uniform_int_distribution<size_t>uniformIntDistribution(0, songList.size()-1);
                        int randomsongs= uniformIntDistribution(engine);
                        const Song& randomsong= songList[randomsongs];
                        cout << "Random Song: " << randomsong.isrc << endl;
                    }
                    break;
                case 2:
                    cout << "isrc: " << "\n" << "acousticness: " << "\n" << "danceability: " << "\n" << "duration_ms: " << "\n" << "energy: " << "\n" << "instrumentalness: " "key: " << "\n" << "liveness: " << "\n" << "loudness: " << "\n" << "mode: " << "\n" << "speechiness: " << "\n" << "tempo: " << "\n" << "time_signature: " << "\n" << "valence: " << "\n" << endl;
                    break;
                default:
                    cout << "Invalid! Enter a number between 0 and 2!" << endl;
                    break;
            }

        }

    }
    return 0;
}