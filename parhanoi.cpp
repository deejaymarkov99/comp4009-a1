#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cilk/cilk.h>
#include <stdio.h>
#include "hwtimer.h"
using namespace std;

char* Hanoi_cilk(int n, char* s, char* a, char* d) {
	
	char* l; 
	char* r;
	
	string left, center, right, sr, ds; 
	
	sr = string(s);
	ds = string(d);
	sr = sr + " to ";
	ds = ds + "\n";
	sr = sr + ds;
	center = "Move from " + sr;
	
	if(n == 1) {
		
		int size = center.size();
		char* c = new char[size+1];
		copy(center.begin(), center.end(), c);
		c[size]='\0';
		
		return c;
	
	}
	else {
		
		l = cilk_spawn Hanoi_cilk(n-1, s, d, a);
		r = cilk_spawn Hanoi_cilk(n-1, a, s, d);
		cilk_sync;
		
		left = string(l);
		right = string(r);
		
		center = left + center;
		center = center + right;
		int size = center.size();
		
		char* c = new char[size+1];
		copy(center.begin(), center.end(), c);
		c[size]='\0';
		
		return c;
	
	}
}

int main(int argc, char* argv[])
	{
		if (argc != 5) {
			cout << "Usage: parhanoi <num>" << endl;
			return 1;
		}
		
		ofstream testfile;
		testfile.open("parallel_tests.txt");
		
		hwtimer_t timer;
		initTimer(&timer);
	
		int param1 = atoi(argv[1]);
		int param2 = atoi(argv[2]);
		int param3 = atoi(argv[3]);
		int param4 = atoi(argv[4]);
		
		char* s = "Source";
		char* a = "Auxillary";
		char* d = "Destination";
		char* x;
		
		int i = 0;
		int j;
		int param;
		long time;
		
		Hanoi_cilk(3, s, a, d); //this is here to "get the blood pumping", on the machine I'm running this on it appears to run slower on the first call to Hanoi
		
		while(i < 4) {
			
			j = i + 1;
			param = atoi(argv[j]);
		
			testfile << "Test run " << j << " on input of size " <<  param << " (small input size)\n" << endl;
			
			
			if (i < 2) {
				startTimer(&timer);
				testfile << Hanoi_cilk(param, s, a, d);
				stopTimer(&timer);
			} else {
				startTimer(&timer);
				Hanoi_cilk(param, s, a, d);
				stopTimer(&timer);
			}
				
			time = getTimerNs(&timer);
			
			
			testfile << "\nTotal time: " << time << "\n" << endl;
			
			initTimer(&timer);
			++i;
		
		}
		testfile.close();
		return 0;
		
	};
