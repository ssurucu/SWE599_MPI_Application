// MPI1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream.h"
#include<conio.h>
#include <fstream>
#include <list>

int * GetFileContent();
int GetFileLineCount();
void main()
{
	int i1;
	int i, j, it, ii, ij, ik, il, im, in;

	bool isCentroidsChanged = false;

	//mean count
	int k;
	int countLine;
	countLine = 0;
	countLine = GetFileLineCount();

	cout << "\nEnter number of K:\n";
	cin >> k;

	double *centroids = new double[k];
	double *newCentroids = new double[k];
	int *iterators = new int[k];

	//assigning random numbers to the centroids according to entered k number
	for (i = 0; i < k; i++)
	{
		centroids[i] = i * 5;
	}

	for (i = 0; i < k; i++)
	{
		newCentroids[i] = i * 5;
	}

	//defining 2-dim array for keeping clustered data
	int** clusteredArray = new int*[k];
	for (int i = 0; i < k; ++i)
		clusteredArray[i] = new int[countLine];

	//getting the data from text file
	int* theArray = GetFileContent();

	do
	{
		isCentroidsChanged = false;

		//iterators for clusters. !!making equal to 0, after clustering again
		for (it = 0; it < k; it++)
		{
			iterators[it] = 0;
		}

		printf("------------------------ \n");
		//calculate nearest centroid for every 
		//for every point
		for (j = 0; j < countLine; j++)
		{
			double distance = -1;
			int nearestCentroidIndex = 0;
			//for very centroid
			for (ii = 0; ii < k; ii++)
			{

				double tempDistance = 0;
				tempDistance = newCentroids[ii] - theArray[j];
				if (tempDistance < 0)
					tempDistance = -tempDistance;

				if (distance == -1)
					distance = tempDistance;
				else {
					if (tempDistance < distance || tempDistance == distance) {
						nearestCentroidIndex = ii;
						distance = tempDistance;
					}
				}
			}
			distance = -1;

			//the element is assigned to the clustered array according to the nearest centroid and the iterator that belongs to that centroid
			clusteredArray[nearestCentroidIndex][iterators[nearestCentroidIndex]] = theArray[j];
			iterators[nearestCentroidIndex] = iterators[nearestCentroidIndex] + 1;

		}

		//printing the centroids and the numbers related to them
		for (ij = 0; ij < k; ij++)
		{
			printf("cluster:%lf - ", centroids[ij]);
			for (ik = 0; ik < iterators[ij]; ik++)
			{
				printf(" %i, ", clusteredArray[ij][ik]);
			}
			printf("--------- \n");
		}

		//calculate new centroids
		for (il = 0; il < k; il++)
		{
			double tempSum = 0.0;
			double tempAvg = 0.0;
			if (iterators[il] != 0)
			{
				for (im = 0; im < iterators[il]; im++)
				{
					tempSum = tempSum + clusteredArray[il][im];
				}
				tempAvg = tempSum / iterators[il];
				newCentroids[il] = tempAvg;
			}
		}

		//check if there is any change on centroids
		for (in = 0; in < k; in++)
		{
			if (newCentroids[in] != centroids[in])
			{
				isCentroidsChanged = true;
				break;
			}
		}

		//assign the new centroids as initial centroids to re-run algorithm again with the new values
		for (i = 0; i < k; i++)
		{
			centroids[i] = newCentroids[i];
		}

	} while (isCentroidsChanged); //if centroids are the same with the previous ones, then stop

	cout << "\n Clusters created";

	_getch();
	delete[] centroids;
	delete[] clusteredArray;
}

//to get file content line by line into an array
int * GetFileContent()
{
	std::fstream myfile("D:\\data.txt", std::ios_base::in);

	float a;
	int i = 0;
	int myArray[9999];

	while (myfile >> a) {
		myArray[i] = a;
		++i;
	}
	getchar();

	return myArray;
}

//to get file line count
int GetFileLineCount()
{
	std::ifstream f("D:\\data.txt");
	char c;
	int i = 0;
	while (f.get(c))
		if (c == '\n')
			++i;

	return i;
}
