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
    bool runMenu2 = true;
    bool error;
    cout << "Welcome to the Song Search Filter!" << endl;
    while (runMenu) {
        int menuOption = -1;
        cout << endl;
        cout << "Select an action:" << endl;
        cout << "0. Exit Program" << endl;
        cout << "1. Filter Information" << endl;
        cout << "2. Search" << endl;
        string temp;
        cin >> temp;
        try {
            menuOption = stoi(temp);
        }
        catch(...) {
            cout << "Error! Not a valid number!" << endl;
            error = true;

        }
        if (!error) {
            if ((menuOption > 2) || (menuOption < 0)) {
                cout << "Enter a number between 0 and 2!" << endl;
            }
        }
        error = false;
        if (menuOption == 0) {
            break;
        }
        else if (menuOption == 1) {
            while (runMenu2)
            {
                int subOption = -1;
                string temp2;
                cout << endl;
                cout << "Filter Information" << endl;
                cout << "__________________" << endl;
                cout << "Select a category to learn more about it's filter!" << endl;
                cout << "0. Back" << endl;
                cout << "1. ISRC" << endl;
                cout << "2. Acousticness" << endl;
                cout << "3. Danceability" << endl;
                cout << "4. Duration" << endl;
                cout << "5. Energy" << endl;
                cout << "6. Instrumentalness" << endl;
                cout << "7. Liveness" << endl;
                cout << "8. Loudness" << endl;
                cout << "9. Speechiness" << endl;
                cout << "10. Tempo" << endl;
                cout << "11. Valence" << endl;
                cin >> temp2;
                try {
                    subOption = stoi(temp2);
                }
                catch (...) {
                    cout << "Error! Not a valid number!" << endl;
                    error = true;
                }
                error = false;
                if (!error)
                {
                    if (((subOption > 11) || (subOption < 0)) && (subOption != -1))
                    {
                        cout << "Enter a number between 0 and 11!" << endl;
                    }
                    else
                    {
                        if (subOption == 0) {
                            runMenu2 = false;
                            runMenu = true;
                        }
                        else if (subOption == 1) {
                            cout << "ISRC" << endl;
                            cout << "__________________" << endl;
                            cout << "International Standard Recording Code. You can find the information about" << endl
                                 << "the particular song by searching for the ISRC code on BeatPort.com." << endl;
                        }
                        else if (subOption == 2) {
                            cout << "Acousticness" << endl;
                            cout << "__________________" << endl;
                            cout << "A confidence measure of how acoustic a particular song is. A higher value" << endl
                                 << "indicates a higher confidence that the song is acoustic." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                        else if (subOption == 3) {
                            cout << "Danceability" << endl;
                            cout << "__________________" << endl;
                            cout << "A measure of how danceable a particular song is, based off various musical" << endl
                                 << "elements such as tempo, rhythm stability, and beat strength. A higher value" << endl
                                 << "indicates that the song is more danceable." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                        else if (subOption == 4) {
                            cout << "Duration" << endl;
                            cout << "__________________" << endl;
                            cout << "The duration of the song in minutes and seconds." << endl;
                        }
                        else if (subOption == 5) {
                            cout << "Energy" << endl;
                            cout << "__________________" << endl;
                            cout << "A measure of how intense a particular song is. More energetic songs are" << endl
                                 << "usually faster, louder, or noisier." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                        else if (subOption == 6) {
                            cout << "Instrumentalness" << endl;
                            cout << "__________________" << endl;
                            cout << "A confidence measure of whether a particular song contains vocals. Values" << endl
                                 << "closer to 1 have a higher likelihood of being instrumental." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                        else if (subOption == 7) {
                            cout << "Liveness" << endl;
                            cout << "__________________" << endl;
                            cout << "A confidence measure of whether an audience is present in a particular song." << endl
                                 << "Used to indicate whether the song was performed live in the recording. A" << endl
                                 << "value above 0.8 indicates a strong likelihood that the song was recorded live." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                        else if (subOption == 8) {
                            cout << "Loudness" << endl;
                            cout << "__________________" << endl;
                            cout << "A measure of how loud a particular song is, measured in decibels (dB). The" << endl
                                 << "value is an average of the entire song." << endl;
                            cout << "Typical range: -60 to 0." << endl;
                        }
                        else if (subOption == 9) {
                            cout << "Speechiness" << endl;
                            cout << "__________________" << endl;
                            cout << "A measure of how much a particular audio track is comprised of spoken words." << endl
                                 << "Values between 0 and 0.33 are most likely mostly music. Values between 0.33" << endl
                                 << "and 0.66 are most likely songs with verbal lyrics. Values between 0.66 and" << endl
                                 << "1.00 are most likely not musical tracks." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                        else if (subOption == 10) {
                            cout << "Tempo" << endl;
                            cout << "__________________" << endl;
                            cout << "The overall estimated tempo of a track in beats per minute (BPM). Higher" << endl
                                 << "values are likely faster paced songs." << endl;
                            cout << "Range: 0 to 250" << endl;
                        }
                        else if (subOption == 11) {
                            cout << "Valence" << endl;
                            cout << "__________________" << endl;
                            cout << "A measure of how much a particular song is likely to elicit positive" << endl
                                 << "emotions. Higher values are likely songs that are happy, cheerful, and" << endl
                                 << "uplifting, whereas lower values are sadder, more depressing, or angry." << endl;
                            cout << "Range: 0 to 1" << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}