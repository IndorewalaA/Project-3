//
// Created by phill on 4/17/2024.
//

#ifndef PROJECT_3_SORTINGSSONGS_H
#define PROJECT_3_SORTINGSSONGS_H
#include <vector>
#include <functional>

using namespace std;

template<typename  T, typename Compare>
void sorting_part(vector<T>& arr, int left, int right, Compare comp);

template<typename  T, typename Compare>
int sorting_again(vector<T>& arr, int left, int right, Compare comp);

#endif //PROJECT_3_SORTINGSSONGS_H
