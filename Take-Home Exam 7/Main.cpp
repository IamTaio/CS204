/****************************************************************************************
Title: A C++ Program for simulating production, filler and packager lines
Date: 05/25/2021
Any known bugs: none
****************************************************************************************/



#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>
#include <ctime>
#include <random>
#include <time.h>
#include <mutex>
#include "DynIntQueue.h"

using namespace std;

mutex CoutMutex;
mutex FillMutex;
mutex PackMutex;
int total_box_count;
int producecount = 1;
int fillcount = 0;
int packcount = 0;
HW7DynIntQueue fillingqueue;

/* Begin: code taken from threads16.cpp*/
/*Function for generating thread safe random integers*/
int random_range(const int & min, const int & max) 
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}
/* End: code taken from threads16.cpp*/

/*Function to simulate empty box production*/
void produce(int mintime, int maxtime, struct tm *ptm)
{
	for(int i = 1; i <= total_box_count; i++)
	{
		this_thread::sleep_for (chrono::seconds(random_range(mintime,maxtime)));
		FillMutex.lock();
		fillingqueue.enqueue(producecount);
		int size = fillingqueue.getCurrentSize();
		FillMutex.unlock();
		CoutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		localtime_s(ptm, &tt);
		cout << "Producer has enqueued a new box " << producecount << " to filling queue (filling queue size is "; 
		cout << size << " ): " << put_time(ptm,"%X") << endl; 
		CoutMutex.unlock();
		producecount++;
	}
	/* At the end of loop total_box_count number of boxes have been created*/
}

void fill(int fillerid, HW7DynIntQueue & packagingqueue, int mintime, int maxtime, struct tm* ptm)
{
	while (fillcount < total_box_count)
	{
		FillMutex.lock();
		if (!fillingqueue.isEmpty())
		{
			int id;
			fillingqueue.dequeue(id);
			fillcount++;
			FillMutex.unlock();
			int size = fillingqueue.getCurrentSize();
			CoutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
			localtime_s(ptm, &tt);
			cout << "Filler " << fillerid << " started filling the box " << id << " (filling queue size is "; 
			cout << size << " ): " << put_time(ptm,"%X") << endl;
			CoutMutex.unlock();
			this_thread::sleep_for (chrono::seconds(random_range(mintime,maxtime)));
			CoutMutex.lock();
			tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
			localtime_s(ptm, &tt);
			cout << "Filler " << fillerid << " finished filling the box " << id << ": " << put_time(ptm, "%X") << endl;
			CoutMutex.unlock();
			PackMutex.lock();
			packagingqueue.enqueue(id);
			int packsize = packagingqueue.getCurrentSize();
			PackMutex.unlock();
			CoutMutex.lock();
			tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
			localtime_s(ptm, &tt);
			cout << "Filler " << fillerid << " put box " << id << " into packaging queue (packaging queue size is "; 
			cout << packsize<< " ): " << put_time(ptm,"%X") << endl; 
			CoutMutex.unlock();
		}
		else
		{
			FillMutex.unlock();
		}
	}
	/* At the end of loop total_box_count number of boxes have been filled and placed into packaging queue*/
}

void pack(int packid, HW7DynIntQueue & packagingqueue, int mintime, int maxtime, struct tm* ptm)
{
	while (packcount < total_box_count)
	{
		PackMutex.lock();
		if (!packagingqueue.isEmpty())
		{
			int id;
			packagingqueue.dequeue(id);
			packcount++;
			PackMutex.unlock();
			int packsize = packagingqueue.getCurrentSize();
			CoutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
			localtime_s(ptm, &tt);
			cout << "Packager " << packid << " started packaging the box " << id; 
			cout << " (packaging queue size is " << packsize << "):" << put_time(ptm,"%X") << endl;
			CoutMutex.unlock();
			this_thread::sleep_for (chrono::seconds(random_range(mintime,maxtime)));
			CoutMutex.lock();
			tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
			localtime_s(ptm, &tt);
			cout << "Packager " << packid << " finished packaging the box " << id << ": " << put_time(ptm, "%X") << endl;
			CoutMutex.unlock();
		}
		else
		{
			//if there are no boxes in the packaging queue unlock so another thread might access
			PackMutex.unlock();
		}
	}
	/* At the end of loop total_box_count number of boxes have been packaged*/
}


int main()
{
	int min_production, max_production;
	int min_filling_time, max_filling_time;
	int min_packaging_time, max_packaging_time;
	cout << "Please enter the total number of items:";
	cin >> total_box_count;
	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: ";
	cin >> min_production;
	cout << "Max: ";
	cin >> max_production;
	cout << "Please enter the min-max waiting time range of filler workers:"<< endl;
	cout << "Min: ";
	cin >> min_filling_time;
	cout << "Max: ";
	cin >> max_filling_time;
	cout << "Please enter the min-max waiting time range of packager workers:" << endl;
	cout << "Min: ";
	cin >> min_packaging_time;
	cout << "Max: ";
	cin >> max_packaging_time;
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
	struct tm *ptm = new struct tm;
	localtime_s(ptm, &tt); 
	cout << "Simulation starts " << put_time(ptm, "%X")<<endl;
	HW7DynIntQueue packagingqueue;
	thread producer = (thread(&produce, min_production, max_production, ptm));
	thread filler1 = (thread(&fill, 1, ref(packagingqueue), min_filling_time, max_filling_time, ptm));
	thread filler2 = (thread(&fill, 2, ref(packagingqueue), min_filling_time, max_filling_time, ptm));
	thread packager1 = (thread(&pack, 1, ref(packagingqueue), min_packaging_time, max_packaging_time, ptm));
	thread packager2 = (thread(&pack, 2, ref(packagingqueue), min_packaging_time, max_packaging_time, ptm));
	producer.join();
	filler1.join();
	filler2.join();
	packager1.join();
	packager2.join();
	cout << "End of the simulation ends: " << put_time(ptm, "%X")<<endl;
	delete ptm;
	return 0;
}
