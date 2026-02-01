#include <iostream>
#include <vector>
#include <string>

using namespace std;

int S = 32;

void merge(vector<int>& arr, int left, int mid, int right){
    int n1 = mid-left+1;
    int n2 = right-mid;

    // create temporary vectors by init and copying over
    vector<int> L(n1), R(n2);
    for(int i=0; i<n1; i++){
        L[i] = arr[left+i];
    }
    for(int j=0; j<n2; j++){
        R[j] = arr[mid+1+j];
    }

    // merge arrays back by comparing each of left and right
    int i=0, j=0;
    int k = left;
    while (i<n1 && j<n2){
        if(L[i]<R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // add remainning elements of L and R into the array
    while(i<n1){
        arr[k] = L[i];
        k++;
        i++;
    }
    while(j<n2){
        arr[k] = R[j];
        k++;
        j++;
    }
}
void insert(vector<int>& arr, int left, int right){
    // assume the first index is already sorted
    for (int i=left+1; i<=right; i++){
        int key = arr[i];
        int j=i-1;
        // keep swappng until key > j
        while (j>= left && key < arr[j]){ 
            arr[j+1] = arr[j]; 
            j--;
        }
        arr[j+1] = key;
    }
}
void hybridSort(vector<int>& arr, int left, int right){
    if(left >= right)
        return;
    int diff =  right-left+1;
    if (diff<=S){
        insert(arr,left, right);
        return;
    }
    // recursively split the arrays first
    int mid = left + (right - left) / 2;
    hybridSort(arr, left, mid);
    hybridSort(arr, mid + 1, right);
    // merge then back 
    merge(arr, left, mid, right);
}
int main(){
    vector<int> arr = {
        39, 12, 5, 18, 7, 33, 2, 29, 14, 1,
        26, 10, 31, 6, 22, 17, 9, 25, 8, 30,
        13, 21, 4, 28, 16, 11, 35, 3, 24, 19,
        27, 15, 37, 0, 23, 34, 20, 38, 32, 36
    };

    int n = arr.size();

    hybridSort(arr, 0, n-1);
    for(int i=0; i<arr.size();i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}