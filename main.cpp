#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "SortingSSongs.h"
#include <iostream>
#include <iomanip>

using namespace std::chrono;
using namespace std;

struct Song
{
    string isrc;
    double acousticness = 0;
    double danceability = 0;
    double duration = 0;
    double energy = 0;
    double instrumentality = 0;
    double key = 0; //NOT USED
    double livelihood = 0;
    double loudness = 1;
    double mode = 0; // NOT USED
    double speechiness = 0; // DONT USE IF YOU DONT WANT TO
    double tempo = 0;
    string time_signature; // NOT USED
    double valence = 0; // THIS IS SO COOLLLL
};

template<typename  T, typename Compare>
void quick_part(vector<T>& arr, int left, int right, Compare T::*songPtr){
    if(left < right){
        int direction= quick_again(arr, left, right, songPtr);
        quick_part(arr, left, direction-1, songPtr);
        quick_part(arr,direction+1, right, songPtr);
    }
}

template<typename  T, typename Compare>
int quick_again(vector<T>& arr, int left, int right, Compare T::*songPtr){
    T direction= arr[right];
    int i = (left-1);
    for(int j = left; j<=right-1; j++){
        if(arr[j].*songPtr < direction.*songPtr){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]);
    return (i+1);
}

template<typename T, typename Compare>
void merge(vector<T>& songList, int left, int middle, int right, Compare T::*songPtr) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<T> lVec(n1), rVec(n2);
    for (int i = 0; i < n1; i++) {
        lVec[i] = songList[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rVec[j] = songList[middle + 1 + j];
    }
    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (lVec[i].*songPtr <= rVec[j].*songPtr) {
            songList[k] = lVec[i];
            i++;
        }
        else {
            songList[k] = rVec[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        songList[k] = lVec[i];
        i++;
        k++;
    }
    while (j < n2) {
        songList[k] = rVec[j];
        j++;
        k++;
    }
}

template<typename T, typename Compare>
void merge_sort(vector<T>& songList, int left, int right, Compare T::*songPtr) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        merge_sort(songList, left, middle, songPtr);
        merge_sort(songList, middle + 1, right, songPtr);
        merge(songList, left, middle, right, songPtr);
    }
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
            bool runMenu2 = true;
            while (runMenu2)
            {
                int menuOption2 = -1;
                string temp2;
                cout << "                     Filter Information                     " << endl;
                cout << "____________________________________________________________" << endl;
                cout << "Select a category to learn more about it's filter!" << endl;
                cout << "0. Back               1. ISRC               2. Acousticness" << endl;
                cout << "3. Danceability       4. Duration           5. Energy" << endl;
                cout << "6. Instrumentalness   7. Liveness           8. Loudness" << endl;
                cout << "9. Speechiness        10. Tempo             11. Valence" << endl;
                cin >> temp2;
                try {
                    menuOption2 = stoi(temp2);
                }
                catch (...) {
                    cout << "Error! Not a valid number!" << endl;
                    error = true;
                }
                error = false;
                if (((menuOption2 > 11) || (menuOption2 < 0)) && (menuOption2 != -1))
                {
                    cout << "Enter a number between 0 and 11!" << endl;
                }
                else
                {
                    if (menuOption2 == 0)
                    {
                        runMenu2 = false;
                        runMenu = true;
                    }
                    else if (menuOption2 == 1)
                    {
                        cout << "ISRC" << endl;
                        cout << "__________________" << endl;
                        cout << "International Standard Recording Code. You can find the information about" << endl
                             << "the particular song by searching for the ISRC code on BeatPort.com." << endl;
                    }
                    else if (menuOption2 == 2)
                    {
                        cout << "Acousticness" << endl;
                        cout << "__________________" << endl;
                        cout << "A confidence measure of how acoustic a particular song is. A higher value" << endl
                             << "indicates a higher confidence that the song is acoustic." << endl;
                        cout << "Range: 0 to 1" << endl;
                    }
                    else if (menuOption2 == 3)
                    {
                        cout << "Danceability" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how danceable a particular song is, based off various musical" << endl
                             << "elements such as tempo, rhythm stability, and beat strength. A higher value" << endl
                             << "indicates that the song is more danceable." << endl;
                        cout << "Range: 0 to 1" << endl;
                    }
                    else if (menuOption2 == 4)
                    {
                        cout << "Duration" << endl;
                        cout << "__________________" << endl;
                        cout << "The duration of the song in minutes and seconds." << endl;
                    }
                    else if (menuOption2 == 5)
                    {
                        cout << "Energy" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how intense a particular song is. More energetic songs are" << endl
                             << "usually faster, louder, or noisier." << endl;
                        cout << "Range: 0 to 1" << endl;
                    }
                    else if (menuOption2 == 6)
                    {
                        cout << "Instrumentalness" << endl;
                        cout << "__________________" << endl;
                        cout << "A confidence measure of whether a particular song contains vocals. Values" << endl
                             << "closer to 1 have a higher likelihood of being instrumental." << endl;
                        cout << "Range: 0 to 1" << endl;
                    }
                    else if (menuOption2 == 7)
                    {
                        cout << "Liveness" << endl;
                        cout << "__________________" << endl;
                        cout << "A confidence measure of whether an audience is present in a particular song." << endl
                             << "Used to indicate whether the song was performed live in the recording. A" << endl
                             << "value above 0.8 indicates a strong likelihood that the song was recorded live."
                             << endl;
                        cout << "Range: 0 to 1" << endl;
                    }
                    else if (menuOption2 == 8)
                    {
                        cout << "Loudness" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how loud a particular song is, measured in decibels (dB). The" << endl
                             << "value is an average of the entire song." << endl;
                        cout << "Typical range: -60 to 0." << endl;
                    }
                    else if (menuOption2 == 9)
                    {
                        cout << "Speechiness" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how much a particular audio track is comprised of spoken words." << endl
                             << "Values between 0 and 0.33 are most likely mostly music. Values between 0.33" << endl
                             << "and 0.66 are most likely songs with verbal lyrics. Values between 0.66 and" << endl
                             << "1.00 are most likely not musical tracks." << endl;
                        cout << "Range: 0 to 1" << endl;
                    }
                    else if (menuOption2 == 10)
                    {
                        cout << "Tempo" << endl;
                        cout << "__________________" << endl;
                        cout << "The overall estimated tempo of a track in beats per minute (BPM). Higher" << endl
                             << "values are likely faster paced songs." << endl;
                        cout << "Range: 0 to 250" << endl;
                    }
                    else if (menuOption2 == 11)
                    {
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
        else if (menuOption == 2) {
            bool runMenu3 = true;
            while(runMenu3) {

                int menuOption3 = -1;
                string temp3;
                cout << "                        Track Search                        " << endl;
                cout << "____________________________________________________________" << endl;
                cout << "Select a category to filter by:" << endl;
                cout << "0. Back               1. Acousticness       2. Danceability" << endl;
                cout << "4. Duration           5. Energy             6. Instrumentalness" << endl;
                cout << "7. Liveness           8. Loudness           9. Speechiness" << endl;
                cout << "10. Tempo             11. Valence" << endl;
                cin >> temp3;
                try {
                    menuOption3 = stoi(temp3);
                }
                catch (...) {
                    cout << "Error! Not a valid number!" << endl;
                    error = true;
                }
                error = false;
                if (((menuOption3 > 10) || (menuOption3 < 0)) && (menuOption3 != -1))
                {
                    cout << "Enter a number between 0 and 10!" << endl;
                }
                else {
                    if (menuOption3 == 0) {
                        runMenu3 = false;
                        runMenu = true;
                    }
                    else {
                        string sortingAlgorithm;
                        if (menuOption3 == 1) {
                            runMenu3 = false;
                            bool runMenu4 = true;
                            while (runMenu4) {
                                bool error = false;
                                cout << "Sorting and searching by acousticness!" << endl;
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values you would like displayed (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        cout << "Error! Enter a valid number!" << endl;
                                        cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::acousticness);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].acousticness >= min && newSongList[i].acousticness <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code     Length(ms)    Acousticness  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.acousticness << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " miliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::acousticness);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].acousticness >= min && newSongList[i].acousticness <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code     Length(ms)    Acousticness  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.acousticness << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " miliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << "Error! enter a number between 0 and 1." << endl;
                                            cout << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << "Error! Enter either 'merge' or 'quicksort'." << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}