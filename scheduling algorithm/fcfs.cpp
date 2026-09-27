#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cout << "Enter number of Process : ";
    cin >> n;
    vector<int>burstTime(n+1),responseTime(n+1);
    responseTime[1]=0;
    for(int i=1 ; i<=n ;i++){
        cout << "Enter the brust time for Process " << i << ": ";
        cin >> burstTime[i];
    }
    for(int i=2 ; i<=n ;i++){
        responseTime[i]=responseTime[i-1]+burstTime[i-1];
    }

    for(int i=1 ; i<=n ;i++){
        cout << "Response time for Process : " << responseTime[i] << endl;
    }
    cout << "Avg Response time: " << responseTime[n]/n << endl;
    
    return 0;
}
