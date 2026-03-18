/*
Find the frequency of a number in array
*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout<<"Enter the size of array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the array elements: ";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    
    int num;
    cout<<"Enter the number to find frequency: ";
    cin>>num;

    int count = 0;
    for(int i=0;i<n;i++)
    {
        if(arr[i] == num)
            count++;
    }

    cout<<"Frequency of "<<num<<" is: "<<count<<endl;

    return 0;
}