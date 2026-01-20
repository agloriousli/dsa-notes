#include <bits/stdc++.h>
using namespace std;

//LCS
string A;
int N;
string B;
int M;


void swap(int A[], int B[]){
    return;
}


int main(){
    cin >> A >> B;
    N = A.length();
    M = B.length();
    int dpr1 [N+1];
    int dpr2 [N+1];
    memset(dpr2, 0, N+1);
    dpr1[0] = 0;
    for(int i = 1; i <= N; i++){
        swap(dpr1,dpr2);
        for(int j = 0; j < M; j++){
            if(A[i] == B[j]){
                dpr2[j] = dpr1[j-1] + 1;
            }else{
                dpr2[j] = max(dpr1[j-1], dpr2[j-1]);
            }
        }
    }
    return 0;
}

/*

     "" B P D E
   "" 0 0 0 0 0
    A 0 
    P 0
    P 0
    L 0
    E 0

*/