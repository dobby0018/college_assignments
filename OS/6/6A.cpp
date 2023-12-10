//FIFO (first come first out)Page Replacement Algorithm.
#include<iostream>
using namespace std;
int main()
{
	int f, n;	
    cout<<"\nEnter the number of frames: ";
    cin>>f;
    cout<<"\nEnter number of processes: ";
    cin>>n;
    int data[n], alloc[f];
    for(int i=0; i<f; i++)
    	alloc[i]=-1;
    cout<<"\nEnter Process IDs: ";
    for(int i=0;i<n;i++)
        cin>>data[i];  
   cout<<endl; 
    int ind=0, fault=0;
	for(int i=0; i<n; i++)
	{	int flag=0;
		for(int j=0; j<f; j++)
		{
			if(alloc[j]==data[i])
				flag=1;
		}
		if(flag!=1)
		{				
			alloc[ind]=data[i];
			ind = (ind+1)%f;
			fault++;
		}
		for(int k=0; k<f; k++)
			cout<<alloc[k]<<"   ";
		cout<<endl;
	}
	cout<<"\nPage Faults: "<<fault;
}
// 4

// 12

// 0 2 1 6 4 0 1 0 3 1 2 1            
