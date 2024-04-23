// reset CMAKE cache (main menu>>file>>invalidate caches) if it doesn't run
// referenced from lecture slides, discussion slides, and OH w/ TAs
// created by abdul, alexis, and helen
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include "SortingSSongs.h"
using namespace std;
using namespace chrono;

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
        cout << "2. Search Audio Features" << endl;
        string temp;
        cin >> temp;
        try {
            menuOption = stoi(temp);
        }
        catch(...) {
            //cout << "Error! Not a valid number!" << endl;
            error = true;

        }
        if (!error) {
            if ((menuOption > 2) || (menuOption < 0)) {
                cout << endl << "Invalid! Enter a number between 0 and 11!" << endl;
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
                // prints out all menu information the user wants to know abt
                cout << endl << "                     Filter Information                     " << endl;
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
                    //cout << "Error! Not a valid number!" << endl;
                    error = true;
                }
                error = false;
                if (((menuOption2 > 11) || (menuOption2 < 0)) && (menuOption2 != -1))   // if input is outside menu range, then its invalid
                {
                    cout << endl << "Invalid! Enter a number between 0 and 11!" << endl;
                }
                else
                {
                    if (menuOption2 == 0)
                    {
                        //runMenu2 = false;
                        //runMenu = true;
                        break;
                    }
                    else if (menuOption2 == 1)
                    {
                        cout << endl << "ISRC" << endl;
                        cout << "__________________" << endl;
                        cout << "aka International Standard Recording Code. Information about the particular\n"
                                "song can be found by searching for the ISRC code on BeatPort.com." << endl;
                    }
                    else if (menuOption2 == 2)
                    {
                        cout << endl << "Acousticness" << endl;
                        cout << "__________________" << endl;
                        cout << "A confidence measure of how acoustic a particular song is. A higher value\n"
                                "indicates a higher confidence that the song is acoustic." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                    else if (menuOption2 == 3)
                    {
                        cout << endl << "Danceability" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how danceable a particular song is, based off various musical\n"
                                "elements such as tempo, rhythm stability, and beat strength. A higher value\n"
                                "indicates that the song is more danceable." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                    else if (menuOption2 == 4)
                    {
                        cout << endl << "Duration" << endl;
                        cout << "__________________" << endl;
                        cout << "The duration of the song in milliseconds." << endl;
                    }
                    else if (menuOption2 == 5)
                    {
                        cout << endl << "Energy" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how intense a particular song is. More energetic songs are\n"
                                "usually faster, louder, or noisier." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                    else if (menuOption2 == 6)
                    {
                        cout << endl << "Instrumentalness" << endl;
                        cout << "__________________" << endl;
                        cout << "A confidence measure of whether a particular song contains vocals. Values\n"
                                "closer to 1 have a higher likelihood of being instrumental." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                    else if (menuOption2 == 7)
                    {
                        cout << endl << "Liveness" << endl;
                        cout << "__________________" << endl;
                        cout << "A confidence measure of whether an audience is present in a particular song.\n"
                                "Used to indicate whether the song was performed live in the recording. A\n"
                                "value above 0.8 indicates a strong likelihood that the song was recorded live." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                    else if (menuOption2 == 8)
                    {
                        cout << endl << "Loudness" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how loud a particular song is, measured in decibels (dB). The\n"
                                "value is an average of the entire song." << endl;
                        cout << "(typical range from -60 to 0)" << endl;
                    }
                    else if (menuOption2 == 9)
                    {
                        cout << endl << "Speechiness" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how much a particular audio track is comprised of spoken words.\n"
                                "Values between 0 and 0.33 are most likely mostly music. Values between 0.33\n"
                                "and 0.66 are most likely songs with verbal lyrics. Values between 0.66 and\n"
                                "1.00 are most likely not musical tracks." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                    else if (menuOption2 == 10)
                    {
                        cout << endl << "Tempo" << endl;
                        cout << "__________________" << endl;
                        cout << "The overall estimated tempo of a track in beats per minute (BPM). Higher\n"
                                "values are likely faster paced songs." << endl;
                        cout << "(ranges from 0 to 250)" << endl;
                    }
                    else if (menuOption2 == 11)
                    {
                        cout << endl << "Valence" << endl;
                        cout << "__________________" << endl;
                        cout << "A measure of how much a particular song is likely to elicit positive\n"
                                "emotions. Higher values are likely songs that are happy, cheerful, and\n"
                                "uplifting, whereas lower values are sadder, more depressing, or angry." << endl;
                        cout << "(ranges from 0 to 1)" << endl;
                    }
                }
            }
        }
        else if (menuOption == 2) {
            bool runMenu3 = true;
            while(runMenu3) {

                int menuOption3 = -1;
                string temp3;
                cout << endl << "                       Audio Features                       " << endl;
                cout << "____________________________________________________________" << endl;
                cout << "Select a category to filter by:" << endl;
                cout << "0. Back               1. Acousticness       2. Danceability" << endl;
                cout << "3. Duration           4. Energy             5. Instrumentalness" << endl;
                cout << "6. Liveness           7. Loudness           8. Speechiness" << endl;
                cout << "9. Tempo              10. Valence" << endl;
                cin >> temp3;
                try {
                    menuOption3 = stoi(temp3);
                }
                catch (...) {
                    //cout << "Error! Not a valid number!" << endl;
                    error = true;
                }
                error = false;
                if (((menuOption3 > 10) || (menuOption3 < 0)) && (menuOption3 != -1))
                {
                    cout << endl << "Invalid! Enter a number between 0 and 10!" << endl;
                }
                else {
                    if (menuOption3 == 0) {
                        //runMenu3 = false;
                        //runMenu = true;
                        break;
                    }
                    else {
                        string sortingAlgorithm;
                        runMenu3 = false;
                        bool runMenu4 = true;
                        if (menuOption3 == 1) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl <<"You chose acousticness!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << endl << "(Invalid! Enter a number within range!)" << endl;
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
                                                cout << "ISRC Code  |  Length(ms)  |  Acousticness  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.acousticness << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
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
                                                cout << "ISRC Code  |  Length(ms)  |  Acousticness  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.acousticness << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
                                }
                            }
                        }
                        else if (menuOption3 == 2) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose danceability!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << endl << "(Invalid! Enter a number within range!)!" << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::danceability);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].danceability >= min && newSongList[i].danceability <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Danceability  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.danceability << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::danceability);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].danceability >= min && newSongList[i].danceability <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Danceability  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.danceability << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
                                }
                            }
                        }
                        else if (menuOption3 == 3) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose duration!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values you would like displayed (in milliseconds):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        // cout << endl << "(Invalid! Enter a number within range!)!" << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        // min 3000
                                        if (min >= 3000 && max <= 10000000) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::duration);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].duration >= min && newSongList[i].duration <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(MM:SS:MM)" << endl;
                                                for (auto ele : subarr) {
                                                    int ms = ele.duration;
                                                    int totalSeconds = ms / 1000;
                                                    int minute = totalSeconds / 60;
                                                    int second = totalSeconds % 60;
                                                    int millisecond = ms % 1000;
                                                    std::cout << ele.isrc << "  "
                                                              << std::setfill('0') << std::setw(2) << minute << ":"
                                                              << std::setfill('0') << std::setw(2) << second << ":"
                                                              << std::setfill('0') << std::setw(3) << millisecond << std::endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::duration);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].duration >= min && newSongList[i].duration <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(MM:SS:MM)" << endl;
                                                for (auto ele : subarr) {
                                                    int ms = ele.duration;
                                                    int totalSeconds = ms / 1000;
                                                    int minute = totalSeconds / 60;
                                                    int second = totalSeconds % 60;
                                                    int millisecond = ms % 1000;
                                                    std::cout << ele.isrc << "  "
                                                              << std::setfill('0') << std::setw(2) << minute << ":"
                                                              << std::setfill('0') << std::setw(2) << second << ":"
                                                              << std::setfill('0') << std::setw(3) << millisecond << std::endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range (from 3000 to 10000000)!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;                                }
                            }
                        }
                        else if (menuOption3 == 4) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose energy!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << "Error! Enter a valid number!" << endl;
                                        //cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::energy);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].energy >= min && newSongList[i].energy <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Energy  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.energy << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::energy);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].energy >= min && newSongList[i].energy <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Energy  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.energy << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;                                }
                            }
                        }
                        else if (menuOption3 == 5) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose instrumentalness!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << "Error! Enter a valid number!" << endl;
                                        //cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::instrumentality);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].instrumentality >= min && newSongList[i].instrumentality <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Instrumentalness  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.instrumentality << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::instrumentality);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].instrumentality >= min && newSongList[i].instrumentality <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Instrumentalness  " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.instrumentality << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;                                }
                            }
                        }
                        else if (menuOption3 == 6) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose liveess!" << endl;       // Sorting and searching by {user input}
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
                                        //cout << "Error! Enter a valid number!" << endl;
                                        //cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::livelihood);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].livelihood >= min && newSongList[i].livelihood <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Liveness " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.livelihood << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::livelihood);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].livelihood >= min && newSongList[i].livelihood <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Liveness" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.livelihood << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
                                }
                            }
                        }
                        else if (menuOption3 == 7) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose loudness!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between -60 and 0):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << "Error! Enter a valid number!" << endl;
                                        //cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= -60 && max <= 0) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::loudness);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].loudness >= min && newSongList[i].loudness <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Loudness(dB)" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.loudness << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::loudness);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].loudness >= min && newSongList[i].loudness <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Loudness(dB)" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.loudness << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
                                }
                            }
                        }
                        else if (menuOption3 == 8) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose speechiness!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << "Error! Enter a valid number!" << endl;
                                        //cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::speechiness);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].speechiness >= min && newSongList[i].speechiness <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Speechiness " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.speechiness << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::speechiness);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].speechiness >= min && newSongList[i].speechiness <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Speechiness" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.speechiness << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
                                }
                            }
                        }
                        else if (menuOption3 == 9) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose tempo!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1200):" << endl;
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
                                        if (min >= 0 && max <= 1200) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::tempo);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].tempo >= min && newSongList[i].tempo <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Tempo(BPM)" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(1) << ele.tempo << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::tempo);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].tempo >= min && newSongList[i].tempo <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Tempo(BPM)" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.tempo << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
                                }
                            }
                        }
                        else if (menuOption3 == 10) {
                            while (runMenu4) {
                                bool error = false;
                                cout << endl << "You chose valence!" << endl;       // Sorting and searching by {user input}
                                cout << "What sorting algorithm would you like to use? Enter either 'merge' or 'quicksort'." << endl;
                                cin >> sortingAlgorithm;
                                if (sortingAlgorithm == "merge" || sortingAlgorithm == "quicksort") {
                                    string temp, temp2;
                                    double min, max;
                                    cout << "Enter the minimum and maximum values within range (between 0 and 1):" << endl;
                                    cout << "Minimum:";
                                    cin >> temp;
                                    cout << "Maximum:";
                                    cin >> temp2;
                                    try {
                                        min = stod(temp);
                                        max = stod(temp2);
                                    }
                                    catch(...) {
                                        //cout << "Error! Enter a valid number!" << endl;
                                        //cout << endl;
                                        error = true;
                                    }
                                    if (!error) {
                                        if (min >= 0 && max <= 1) {
                                            vector<Song> newSongList = songList;
                                            if (sortingAlgorithm == "quicksort") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                quick_part(newSongList, 0, newSongList.size(), &Song::valence);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].valence >= min && newSongList[i].valence <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Valence " << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.valence << endl;
                                                }
                                                cout << "Quicksort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            else if (sortingAlgorithm == "merge") {
                                                vector<Song> subarr;
                                                auto start = high_resolution_clock::now();
                                                merge_sort(newSongList, 0, newSongList.size() - 1, &Song::valence);
                                                auto stop = high_resolution_clock::now();
                                                auto duration = duration_cast<milliseconds>(stop - start);
                                                for (int i = 0; i < newSongList.size(); i++) {
                                                    if (newSongList[i].valence >= min && newSongList[i].valence <= max) {
                                                        subarr.push_back(newSongList[i]);
                                                    }
                                                }
                                                cout << subarr.size() << " Results!" << endl;
                                                cout << "ISRC Code  |  Length(ms)  |  Valence" << endl;
                                                for (auto ele : subarr) {
                                                    cout << ele.isrc << "  " << ele.duration << "        " << setprecision(6) << ele.valence << endl;
                                                }
                                                cout << "Merge sort took " << duration.count() << " milliseconds!" << endl;
                                            }
                                            runMenu4 = false;
                                            runMenu3 = true;
                                        }
                                        else
                                        {
                                            cout << endl << "(Invalid! Enter a number within range!)" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << endl <<  "(Invalid! Enter 'merge' or 'quicksort')" << endl;
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