#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    int grade;
    int mx = INT_MIN;
    
    while(cin >> grade, grade >= 0){ 
        v.push_back(grade);
        if(grade > mx){mx = grade;}
    }
    
    int* a = new int[mx+5];
    int sz = v.size();
    
    for(int i = 0 ; i <= mx ; ++i){
        a[i] = 0;
    }
    
    for(int i = 0 ; i < sz ; ++i){
        a[v[i]]++;
    }
    
    for(int i = 0 ; i <= mx ; ++i){
        if(a[i])
        cout << "Number of " << i << "'s:    " << a[i] << endl;
    }

    return 0;
}
