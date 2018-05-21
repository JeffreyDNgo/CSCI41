//*************************************************
//Jeffrey Ngo, csci 41

// Below are the functions for sorting algorithms/randomized arrays
// The main function has the concept for making the randomized vector/arrays
// main is currently set to test shellsorts with 3 different randomized vectors~ (2k,4k,8k)

//*************************************************/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>


using namespace std;
using namespace std::chrono; // for clock/stopwatch

//stopwatch
class Stopwatch {
private:
	high_resolution_clock::time_point start; //timer is specific, returns decimal
	high_resolution_clock::time_point now;
public:
	Stopwatch() { reset(); } // for testing convenience, don't have to call stopwatch multiple times
	void reset() { start = high_resolution_clock::now(); }
	duration<double> elapsedTime() {
		now = high_resolution_clock::now();
		return duration_cast<duration<double>>(now - start);
	}
};



void randomize(vector<int> &v,int vSize) //randomizes vector with specified size -- used for shellsort
{
	for (int i = 0; i < vSize; i++)
	{
		int s = (rand() % (vSize + 1)) - (vSize / 2);
		v.push_back(s);
	}
}

void randomizeArr(int array[], int arrSize) //randomizes array with specified size
{
	int num;
	for (int i = 0; i < arrSize; i++)
	{
		num = (rand() % (arrSize + 1)) - (arrSize / 2);
		array[i] = num;
	}
}

//1. Shellsort, Pratt 1971 -- (3 ^ h - 1) / 2

//a.

void prattSort(vector<int> &v)
{
	int h = 1, j, a = 0;
	while (h < v.size() + 1)
	{

		for (int i = h; i < v.size(); i++)
		{
			int temp = v.at(i);
			j = i;
			while (j >= h && v.at(j - h) > temp)
			{
				v.at(j) = v.at(j - h);
				j = j - h;
			}
			v.at(j) = temp;
		}
		a = a + 1;
		while (h >! h / 3)
		{
			h = pow(3,h) - 1 / 2; //implement algorithm
		}
	}
}


//b.
void gonnetSort(vector<int> &v) //this is shellsort with gonnet/yates' theorem, 5 * h - 1 /11
{
	int h = 1, j, a = 0;
	while (h < v.size() + 1)
	{

		for (int i = h; i < v.size(); i++)
		{
			int temp = v.at(i);
			j = i;
			while (j >= h && v.at(j - h) > temp)
			{
				v.at(j) = v.at(j - h);
				j = j - h;
			}
			v.at(j) = temp;
		}
		if (h == 2)
		{
			h = 1;
		}
		else
		{
			h = 5 * h - 1 / 11; //implement algorithm
		}
	}
}

//2. Mergesort

//a.
void mergesort(int* A,int* temp, int left, int right)
{
	int i = 0;
	if (left == right)
	{
		return;
	}
	int mid = (left + right) / 2;
	mergesort(A, temp, left, mid); //sort first half
	mergesort(A, temp, (mid + 1), right); //sort second half
	for (i = left; i <= right; i++)
	{
		temp[i] = A[i];
	}
	int i1 = left;
	int i2 = mid + 1;
	for (int curr = left; curr <= right; curr++)
	{
		if (i1 == mid + 1)
		{
			A[curr] = temp[i2++];
		}
		else if (i2 > right)
		{
			A[curr] = temp[i1++];
		}
		else if (temp[i1] <= temp[i2])
		{
			A[curr] = temp[i1++];
		}
		else {
			A[curr] = temp[i2++];
		}
	}
}

int findpivot(int left, int right)
{
	return rand() % (right - left + 1) + left;
}


//b. 3 way mergesort

void threewayMergesort(int* A, int* temp, int left, int right)
{
	int i = 0;
	if (left == right)
	{
		return;
	}
	int mid = (left + right) / 2;
	mergesort(A, temp, left, mid-left); //sort first half
	mergesort(A, temp, mid - left, mid + right); //sort center
	mergesort(A, temp, (mid + right), right); //sort second half
	for (i = left; i <= right; i++)
	{
		temp[i] = A[i];
	}
	//create pivots for sorting 3 way merge
	int i1 = left;
	int i2 = left + (right - left) / 3;
	int i3 = left + 2 * (right - left) / 3;
	for (int curr = left; curr <= right; curr++)
	{
		if (i1 == mid + 1)
		{
			A[curr] = temp[i2++];
		}
		else if (i2 > right)
		{
			A[curr] = temp[i1++];
		}
		else if (temp[i1] <= temp[i2])
		{
			A[curr] = temp[i1++];
		}
		else {
			A[curr] = temp[i2++];
		}
	}
}


//3. Quicksort

//a.
void shuffle(int* A, int N)
{
	for (int i = 0; i < N; i++)
	{
		int j = rand() % (i + 1);
		if (j != i)
		{
			A[i] = A[j];
		}
		A[j] = i;
	}
}


void swap(int array[], int index1, int index2)
{
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

void quicksort(int array[], int start, int end)
{
	int l = start; //left to right
	int r = end; //right to left
	if (end - start >= 1) //checking hi lo, else return, finished sorting
	{
		int pivot = array[start];
		while (r > l)
		{
			while (array[l] <= pivot && l <= end && r > l)
			{
				l++;
			}
			while (array[r] > pivot && r >= start && r >= l)
			{
				r--;
			}
			if (r > l)
			{
				swap(array, l, r);
			}
			swap(array, start, r);
			quicksort(array, start, r - 1);
			quicksort(array, r + 1, end);
		}
	}
	else //end of partition, exit
	{
		return;
	}
}

//b. --ninth median quicksort

void ninthQuicksort(int array[], int start, int end) //pivots at median of 9
{
	int l = start; //left to right
	int r = end; //right to left
	if (end - start >= 1) // hi, lo check, else return at end
	{
		int pivot = array[start];
		while (r > l)
		{
			while (array[l] <= pivot && l <= end && r > l)
			{
				l++;
			}
			while (array[r] > pivot && r >= start && r >= l)
			{
				r--;
			}
			int m = (array, l, l + (r ^ 3 - l) / 2, r); //median of 9 pivot
			swap(array, l, m);
			}
			swap(array, start, r);
			quicksort(array, start, r - 1);
			quicksort(array, r + 1, end);
		}
	else
	{
		return;
	}
}

//3. 3-way quicksort

void threewayQuicksort(int array[], int start, int end)
{
	int l = start; //left to right
	int r = end; //right to left
	if (end - start >= 1) //checking hi lo, else return, finished sorting
	{
		int pivot = array[start];
		while (r >= l) //lo lessthan or = hi
		{
			while (array[l] <= pivot && l <= end && r > l)
			{
				l++;
			}
			while (array[r] > pivot && r >= start && r >= l)
			{
				r--;
			}
			if (r > l)
			{
				swap(array, l, r--);
			}
			else
			{
				l++;
			}
			swap(array, start, r);
			quicksort(array, start, l - 1);
			quicksort(array, r + 1, end);
		}
	}
	else //end of partition, exit
	{
		return;
	}
}

void printArray(const int array[], int count) //prints array--for during sorting
{
	for (int i = 0; i < count; i++)
		cout << array[i] << endl;
}

// 4. Heapsort

//a.
//first implementing sink for heapsort, only uses sink

/*
int N = 0;
void sink(int s, int N, int A[])
{
	while (2 * s <= N) //
	{
		int j = s * 2; //declaring left of root
		if (j < N && j < j + 1) //left and right children of node
		{
			j++;
		}
		if (s <! j)
		{
			break;
		}
		swap(s, j);
		s = j;
	}
}

void heapSort(int A[])
{
	int N = A.length;
	for (int s = N / 2; s >= 1; s--)
		sink(A, s, N);
	while (N > 1)
	{
		swap(A, 1, N);
		sink(A, 1, N--);
	}
}
*/
int main()
//*************************************************
// In main, create a randomized array/vector using const size(1-2), then call sorting function from above
// In the examples, the stopwatch function is called to measure the time complexities

//*************************************************/

{
	//time
	//double timeBegin, timeEnd, totalTime;

	const int size = 2000;
	const int size1 = 4000;
	const int size2 = 8000;
	srand((unsigned)time(NULL)); //seeds generator

	//Creates three vectors, with randomly generated integers -- 2000, 4000, 8000
	vector<int> v = { 0 };
	randomize(v, size);
	
	vector<int> v1 = { 0 };
	randomize(v1, size1);

	vector<int> v2 = { 0 };
	randomize(v2, size2);
	
	/*
	int array1[size2] = { 0 };
	randomizeArr(array1, size2);
	*/
	Stopwatch stopwatch;
	cout << "sorting...";
	prattSort(v);
	duration<double> time = stopwatch.elapsedTime();
	cout << "execution time for shellsort vector 1. is " << time.count() << endl;
	
	stopwatch.reset();
	cout << "sorting...";
	gonnetSort(v1);
	time = stopwatch.elapsedTime();
	cout << "execution time for shellsort vector 2. is " << time.count() << endl;

	stopwatch.reset();
	cout << "sorting...";
	gonnetSort(v2);
	time = stopwatch.elapsedTime();
	cout << "execution time for shellsort vector 3. is " << time.count() << endl;
	
	
	/*
	Stopwatch stopwatch;
	cout << "sorting...";
	quicksort(array1, 0, sizeof(array1) / sizeof(array1[0]) - 1);
	duration<double>time = stopwatch.elapsedTime();
	cout << "execution time for quicksort. is " << time.count() << endl;
	system("pause");
	*/
}


	/*
	//printing contents of array
	
	srand((unsigned)time(NULL));
	int array1[size] = { 0 };
	randomizeArr(array1, size);

	for (int i = 0; i < size; i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;

	cout << "mergesort for vector 1: ";
	Stopwatch* stopwatch = new Stopwatch();
	quicksort(array1,0, 4999);
	duration<double> time = stopwatch->elapsedTime();
	
	for (int i = 0; i < size; i++)
	{
		cout << array1[i];
	}
	cout << " execution time for quicksort is " << time.count() << endl;

	
	for (int i = 0; i < size1; i++)
	{
		cout << v1.at(i) << " ";
	}
}

*/


