#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>
#include <ctime>
#include <random>
#include <time.h>
#include <mutex>
#include "HW7DynIntQueue.h"

using namespace std;

mutex CoutMutex;
mutex FillMutex;
mutex PackMutex;
mutex MyMutex;
int total_box_count;
int producecount = 1;
int fillcount = 0;
int packcount = 0;
HW7DynIntQueue fillingqueue;
HW7DynIntQueue packagingqueue;
int random_range(const int & min, const int & max) 
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

struct timerange //Struct for the timerange 
{
	int max;
	int min;
};

void produce(const timerange & duration, struct tm *ptm)
{
	int maxtime = duration.max;
	int mintime = duration.min;
	this_thread::sleep_for (chrono::seconds(random_range(mintime,maxtime)));
	if (fillingqueue.getCurrentSize() != total_box_count)
	{
		fillingqueue.enqueue(producecount);
		CoutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		localtime_s(ptm, &tt);
		cout << "Producer has enqueued a new box " << producecount << " to filling queue (filling queue size is "; 
		cout << fillingqueue.getCurrentSize() << " ): " << put_time(ptm,"%X") << endl; 
		CoutMutex.unlock();
		producecount++;
	}
}

void fill(int fillerid, const timerange & duration, struct tm *ptm)
{
	FillMutex.lock();
	if(!fillingqueue.isEmpty())
	{
		int id;
		int maxtime = duration.max;
		int mintime = duration.min;
		fillingqueue.dequeue(id);
		fillcount++;
		FillMutex.unlock();
		CoutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		localtime_s(ptm, &tt);
		cout << "Filler " << fillerid << " started filling the box " << id << " (filling queue size is "; 
		cout << fillingqueue.getCurrentSize() << " ): " << put_time(ptm,"%X") << endl;
		CoutMutex.unlock();
		this_thread::sleep_for (chrono::seconds(random_range(mintime,maxtime)));
		CoutMutex.lock();
		tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		localtime_s(ptm, &tt);
		cout << "Filler " << fillerid << " finished filling the box " << id << ": " << put_time(ptm, "%X") << endl;
		CoutMutex.unlock();
		PackMutex.lock();
		if (packagingqueue.getCurrentSize() != total_box_count)
		{
			packagingqueue.enqueue(id);
		}
		PackMutex.unlock();
		CoutMutex.lock();
		tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		localtime_s(ptm, &tt);
		cout << "Filler " << fillerid << " put box " << id << " into packaging queue (packaging queue size is "; 
		cout << packagingqueue.getCurrentSize() << " ): " << put_time(ptm,"%X") << endl; 
		CoutMutex.unlock();
	}
	else
	{
		FillMutex.unlock();
	}
}

void package(HW7DynIntQueue & pqueue, int packid, const timerange & duration, struct tm *ptm)
{
	cout << "pack" << packid << endl;
	PackMutex.lock();
	if (!pqueue.isEmpty())
	{
		int id;
		cout << "peller" << packid << endl;
		pqueue.dequeue(id);
		int maxtime = duration.max;
		int mintime = duration.min;
		PackMutex.unlock();
		CoutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		localtime_s(ptm, &tt);
		cout << "Packager " << packid << " started packaging the box " << id; 
		cout << " (packaging queue size is " << pqueue.getCurrentSize() << "):" << put_time(ptm,"%X") << endl;
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
		PackMutex.unlock();
	}
}


int main ()
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
	timerange producetime;
	producetime.max = max_production;
	producetime.min = min_production;
	timerange fillertime;
	fillertime.max = max_filling_time;
	fillertime.min = min_filling_time;
	timerange packagetime;
	packagetime.max = max_packaging_time;
	packagetime.min = min_packaging_time;
	thread producer;
	thread filler1;
	thread filler2;
	thread packager1;
	thread packager2;
	HW7DynIntQueue fillingqueue;
	HW7DynIntQueue packagingqueue;
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
	struct tm *ptm = new struct tm;
	localtime_s(ptm, &tt); 
	cout << "Simulation starts " << put_time(ptm, "%X")<<endl;
	while (fillcount <= total_box_count) //Fillcount is used to ensure the correct number of boxes are filled
	{
		producer = (thread(&produce, producetime, ptm));
		filler1 = (thread(&fill, 1, fillertime, ptm));
		filler2 = (thread(&fill, 2, fillertime, ptm));
		if (producer.joinable())
		{
			producer.join();
		}
	}
	/*while (packcount < total_box_count)
	{
		packager1 = (thread(&package, packagingqueue, 1, packagetime, ptm));
		packager2 = (thread(&package, packagingqueue, 2, packagetime, ptm));
	}
	if (filler1.joinable())
	{
		filler1.join();
	}
	if (filler2.joinable())
	{
		filler2.join();
	}
	if (packager1.joinable())
	{
		packager1.join();
	}
	if (packager2.joinable())
	{
		packager2.join();
	}*/
	

	if (filler1.joinable())
	{
		filler1.join();
	}
	if (filler2.joinable())
	{
		filler2.join();
	}
	cout << "Simulation ends " << put_time(ptm, "%X")<<endl;
	delete ptm;
	return 0;
}