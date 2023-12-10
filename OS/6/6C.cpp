// LRU (Least Recently Used) Page Replacement Algorithm.
#include<bits/stdc++.h>
#include<iostream>
using namespace std;
int LRU(int time[], int f)
{	int i, minimum = time[0], pos = 0;
	for(i=1; i<f; i++)
	{	if(time[i] < minimum)
		{	minimum = time[i];
			pos = i;
		}
	}
	return pos;
}
int main(){
	int nf, np, alloc[20], pages[30], counter=0, time[20];
	int flag1, flag2, i, j, pos, faults=0;
	cout << "Enter number of Frames: ";
	cin >> nf;
	cout << "Enter number of pages: ";
	cin >> np;
	cout << "Enter pages: ";
	for(i=0; i<np; i++)
		cin >> pages[i];
	for(i=0; i<nf; i++)
		alloc[i] = -1;
	cout <<"\n";
	for(i=0; i<nf; i++){
		cout << "F" <<i+1 << " ";
	}
	cout <<"\n";
	for(i=0; i<np; i++)
	{	flag1 = flag2 = 0;
		for(j=0; j<nf; j++)
		{	if(alloc[j] == pages[i])
			{	counter++;
				time[j] = counter;
				flag1 = flag2 = 1;
				break;
			}
		}
		if(flag1 == 0)
		{	for(j=0; j<nf; j++)
			{	if(alloc[j] == -1)
				{	counter++;
					faults++;
					alloc[j] = pages[i];
					time[j] = counter;
					flag2 = 1;
					break;
				}
			}
		}
		if(flag2 == 0)
		{	pos = LRU(time, nf);
			counter++;
			faults++;
			alloc[pos] = pages[i];
			time[pos] = counter;
		}
		cout << "\n";
		for(j=0; j<nf; j++)
			cout << alloc[j] << "  ";
	}
	cout << "\n\nTotal Page faults = " << faults;
	return 0;
}
// 3
// 15
// 6 7 8 9 6 7 1 6 7 8 9 1 7 9 6
