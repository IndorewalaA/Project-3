//
// Created by phill on 4/17/2024.
//

#include "SortingSSongs.h"


template<typename  T, typename Compare>
void sorting_part(vector<T>& arr, int left, int right, Compare comp){
    if(left < right){
        int direction= sorting_again(arr, left, right, comp);
        sorting_part(arr, left, direction-1, comp);
        sorting_part(arr,direction+1, right, comp);
    }
}

template<typename  T, typename Compare>
int sorting_again(vector<T>& arr, int left, int right, Compare comp){
    T direction= arr[right];
    int i = (left-1);
    for(int j = left; j<=right-1; j++){
        if(comp(arr[j], direction)){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]);
    return (i+1);
}
