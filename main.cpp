#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>


//bubbles
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
    double loudness = 0;
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

    bool runMenu = true;
    bool error;
    int menuOption = -1;
    cout << "Welcome to the Song Search Filter!" << endl;
    while (runMenu) {
        cout << endl;
        cout << "Select an action:" << endl;
        cout << "0. Exit Program" << endl;
        cout << "1. Filter Information" << endl;
        cout << "2. Search" << endl;
        string temp;
        cin >> temp;
        try {
            menuOption = stoi(temp);
            //error= false;
        }
        catch(...) {
            cout << "Error! Not a valid number!" << endl;
            //error = true;

        }
        switch(menuOption){
            case 0:
                runMenu= false;
                break;
            case 1:
                cout<< "Filter Information feature has not been selected yet."<<endl;
                break;
            case 2:
                if(songList.empty()){
                    cout<<"No songs available to display"<<endl;
                }else{
                    static default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
                    uniform_int_distribution<size_t>uniformIntDistribution(0, songList.size()-1);
                    int randomsongs= uniformIntDistribution(engine);
                    const Song& randomsong= songList[randomsongs];
                    cout<<"Random Song: "<< randomsong.isrc <<endl;

                }
                break;
           default:
            cout << "Enter a number between 0 and 2!" << endl;
            break;
        }
    }
    return 0;
}