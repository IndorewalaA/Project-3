// Created by phill on 4/17/2024.
#include <vector>
#include <functional>

using namespace std;

template<typename  T, typename Compare>
void quick_part(vector<T>& arr, int left, int right, Compare T::*songPtr);

template<typename  T, typename Compare>
int quick_again(vector<T>& arr, int left, int right, Compare T::*songPtr);
