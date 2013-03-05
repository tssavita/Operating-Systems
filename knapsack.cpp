#include <iostream>

using namespace std;

void knapsack(int n, int W, int *w, int *b) {
    int i = 0, j = 1;
    int benefit[10][10];

    for (j = 1; j <= W; j++) 
        benefit[0][j] = 0;

    for (i = 0; i <= n; i++) {
        for (j = 1; j <= W; j++) {
            if (i == 0)
                benefit[0][j] = 0;
            else if ((j - w[i-1]) >= 0) {
                benefit[i][j] = max(benefit[i-1][j], (benefit[i][j-w[i-1]] + b[i-1]));
                cout<<w[i-1]<<"w - "<<b[i-1]<<"b "<<i<<" "<<j<<" "<<benefit[i][j]<<"\n";
            }
            else 
                benefit[i][j] = benefit[i-1][j];
        }
    }

    for (i = 0; i <= n; i++) {
        for (j = 1; j <= W; j++) 
            cout<<benefit[i][j]<<" ";
        cout<<"\n";
    }   
}

int main(int argc, char ** argv) {
    int i = 0, j = 0; // loop variables
    int W = 0, n = 0; // W => maximum weight, n => number of objects
    int benefit[10][10]; // total benefit
    int *w, *b;

    cout<<"Enter the number of objects - ";
    cin>>n;

    cout<<"Enter the maximum weight possible - ";
    cin>>W;

    b = new int(n);
    cout<<"Enter the benefit for each object - ";
    for (i = 0; i < n; i++)
        cin>>b[i];

    w = new int(n);
    cout<<"Enter the weight for each object - ";
    for (i = 0; i < n; i++)
        cin>>w[i];

    knapsack(n, W, w, b);
 
    return 0;
}
