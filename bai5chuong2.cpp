#include<iostream>

using namespace std;

int b[100][100] = {0};

bool check(int i, int j){
    if(i>0 && j>0) return true;
    else return false;
}

int main(){
    int a[10][10];
    int k=1;
    for(int i=1; i<=8; i++){
        for(int j=1; j<=8; j++){
            a[i][j]=k;
            k++;
        }
    }
    for(int i=1; i<=8; i++){
        for(int j=1; j<=8; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    for(int i=1; i<=8; i++){
        for(int j=1; j<=8; j++){
            
        }
    }
}