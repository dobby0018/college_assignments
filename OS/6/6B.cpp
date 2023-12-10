// Optimal Page Replacement Algorithm.
#include<iostream>
#include<string.h>
using namespace std;
int faults=0;
int return_index(int *arr,int n,int search);
int ifpresent(int n,int *arr,int value,int start);
int last_page(int n,int *arr,int *frames,int curr,int fn);
int main()
{
    int n,ch,page_no,flag,j=0,replace_index,nop,frames_empty,lp,lp_index;
    cout<<"\nEnter the number of frames: ";
    cin>>n;
    frames_empty=n;
    int frames[n],replace[n],y=0;
    char c[1];
    for(int i=0;i<n;i++)
    {
        replace[i]=frames[i]=-1;
    }
    cout<<"\nEnter number of page references: ";
    cin>>nop;
    int pages[nop];
    cout<<"Enter Page Reference String: ";
    for(int i=0;i<nop;i++)
    {
        cin>>pages[i];
    }
    cout<<endl;

    for(int y=0;y<nop;y++)
    {  
        page_no=pages[y];
        for(int i=0;i<n;i++)
        {
            if(frames[i]!=page_no)
            {
                flag=1;
            }
            else
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {
            if(frames_empty>0)
            {
                frames[n-frames_empty]=page_no;
            }
            else
            {
                lp=last_page(nop,pages,frames,y,n);
                if(lp!=-1)
                {
                    lp_index=return_index(frames,n,lp);
                }
                else
                {
                    lp_index=0;
                }
                frames[lp_index]=page_no;
            }
            frames_empty--;
            faults++;
        }
        else
        {
        }
        for(int i=0;i<n;i++)
        {
            cout<<frames[i]<<" ";
        }
        cout<<endl;
    }
    cout << "\n\nTotal Page faults = " << faults;
	return 0;
}
int return_index(int *arr,int n,int search)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i]==search)
        {
            return i;
        }
    }
    return -1;
}
int ifpresent(int n,int *arr,int value,int start)
{
    for(int i=start;i<n;i++)
    {
        if(arr[i]==value)
        {
            return 1;
        }
    }
    return 0;
}
int last_page(int n,int *arr,int *frames,int curr,int fn)
{
    int got[fn],k=0;
    for(int i=0;i<fn;i++)
    {
        if(!ifpresent(n,arr,frames[i],curr+1))
        {
            return frames[i];
        }
    }
    int last=-1;
    for(int i=curr+1;i<n;i++)
    {
        for(int j=0;j<fn;j++)
        {
            if(arr[i]==frames[j] && !ifpresent(k,got,arr[i],0))
            {
                last=arr[i];
                got[k++]=last;
            }
        }
    }
    return got[--k];
}
// 3
// 15
// 6 7 8 9 6 7 1 6 7 8 9 1 7 9 6
