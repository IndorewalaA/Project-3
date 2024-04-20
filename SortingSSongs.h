//
// Created by phill on 4/17/2024.
//

#ifndef PROJECT_3_SORTINGSSONGS_H
#define PROJECT_3_SORTINGSSONGS_H
#include <vector>
#include <functional>

using namespace std;

template<typename  T, typename Compare>
void quick_part(vector<T>& arr, int left, int right, Compare T::*songPtr);

template<typename  T, typename Compare>
int quick_again(vector<T>& arr, int left, int right, Compare T::*songPtr);

#endif //PROJECT_3_SORTINGSSONGS_H
