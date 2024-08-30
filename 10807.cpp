#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    int totalCount;
    cin >> totalCount;

    int* arr = new int[totalCount];
    for(int i = 0; i < totalCount; i++){
        cin >> arr[i];
    }
    
    int findNum;
    cin >> findNum;

    int count = 0;
    for(int i = 0; i < totalCount; i++){
        if(arr[i] == findNum){
            count++;
        }
    }
    cout << count << endl;

    delete []arr;
    return 0;
}

