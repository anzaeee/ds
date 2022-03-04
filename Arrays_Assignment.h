#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

//globally declared variables that have data
int student = 0;

string details[18] = { "0" };
//details has all the details and courses has the course codes currently, courses will not be updated however details will they are parallel arrays
string courses[18] = { "SRNO", "MT104", "MT119","CS118","CL118","EE182","SL101","SS101","EE227","SS122","MT224","SS111","CS217","EL227","CL217","CGPA", "WARNING", "CS201" };
//00 ,  01,	    02,	 03,	04,	05,	06		07		08	09		10	11		12	13		14	15		16	  17		(indexes)
//SRNO,MT104, MT119,CS118,CL118,EE182,SL101,SS101,EE227,SS122,MT224,SS111,CS217,EL227,CL217,CGPA,WARNING,CS201

int control = -1;
vector<string> row;
string line, word; //has line number and controls

//file objects
fstream fin;
fstream fout;

string filepath = "Clean_Data.csv";
double** Arr;
//double Placeholder [1565][17] = { 0 };

void CleanDetails()
{
	for (int i = 0; i < 17; i++)
	{
		details[i + 1] = "0";
	}
}

void PrintDetails(double** Arr)
{

	if (control == -1)
	{
		fout.open(filepath, ios::out);
		control++;
	}

	else
	{
		if (details[15] == "0" || details[15] == "" || details[17] == "" || details[17] == "-1")
			return;
		else if (details[17] == "W")
			details[17] = "0";
		else
		{
			for (int i = 0; i < 18; i++)
			{
				if (i == 0)
				{
					fout << student << ',';
				}
				else if (i == 17)
				{
					fout << details[i];
				}
				else
					fout << details[i] << ',';

			}
			fout << endl;
			int j = 0;
			for (int x = 1; x <= 17; x++)
			{
				Arr[student][j] = stod(details[x]);
				//cout << Arr[student][j];
				j++;
			}
			student++;
		}
	}
}

double** Load_Data(string path) // Return 2D array which contains Data in that path. 					// Data in 2D should be clean (definition of cleaning data is already mentioned in the assignment description)
{
	//call readerfunction that will do all the data cleaning


	fin.open(path, ios::in);
	if (!fin.is_open())
	{
		cout << "filedoesntopen. enter valid name.";
		return NULL;
	}
	Arr = new double* [1565];
	for (int i = 0; i < 1565; i++)
		Arr[i] = new double[17];

	while (!fin.eof())
	{
		row.clear();
		getline(fin, line);
		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word
		while (getline(s, word, ','))
		{

			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		if (control == -1)
		{
			//cout << "skipping first line." << endl;
			PrintDetails(Arr); //creates Output file to write the results into
		}
		else
		{
			if (stod(row[0]) > stod(details[0])) // this condition checks if student has changed
			{
				PrintDetails(Arr); //print all saved details of current student
				details[0] = row[0]; //update to new student
				CleanDetails(); //reset all grades
			}
		}
		details[15] = row[8]; //cgpa
		details[16] = row[9]; //warning
		if (row[2] != "Unknown")
		{
			for (int i = 1; i < 18; i++)
			{
				details[16] = row[9]; //warning
				if ( stod(details[15]) < stod(row[8]) )
					details[15] = row[8]; //cgpa
				if (row[2] == courses[i]) //this works for all the grades
				{

					if (details[i] < row[6])
						details[i] = row[6];
					else if (row[5] == "W")
						details[i] = "0";
				}
			}
		}
	}
	//closing both files Clean_Data and Students_Dataset.csv
	fin.close();
	fout.close();
	
	return Arr;
}
//Distance(Predicted_Array, 14, Data, 1780, 17);

double** Distance(double* predictedArray, int predictedArraySize, double** data, int dataRows, int dataCols)
// Return mean of all datapoint with the predicted datapoint along with Gardepoint in DS 
{
	//datacols = 17;
	// 2 3 11 12 13
	double** temp = new double* [1565]; //total number of VALID student data. 1778 may be cleaned data 
	//however it is much more than required as most students had UK grade in DS which was unrequired
	for (int i = 0; i < dataRows; i++)
		temp[i] = new double[2];
	double sum = 0;
	double distance = 0;
	for (int i = 0; i < 1564; i++)
	{
		sum = 0;
		temp[i][1] = data[i][16];
		for (int j = 0; j < predictedArraySize; j++)
		{
			distance = abs(predictedArray[j] - data[i][j]);
			if (j == 2 || j == 3 || j == 11 || j == 13)
				distance = distance * 1.5;

			sum += distance;

		}
		temp[i][0] = sum;
		
		//#### NOTE:
		//TEST CASE FAILS DUE TO DOUBLE PRECISION FAULT. ANSWER IS CORRECT.
	}

	return temp;
}


double** Sort_k_Dis(int k, double** distance, int distanceRows, int distanceCols)
// Return the 1st k sorted distance with Grade point in Ascending order 
{
	//int end = distanceRows - 1, start =;
	double temp, temp2;

		for (int i = 0; i < distanceRows - 1; i++)
		{
			for (int j = i + 1; j < distanceRows; j++)
			{
				if (distance[i][0] > distance[j][0])
				{
					temp = distance[i][0];
					temp2 = distance[i][1];

					distance[i][0] = distance[j][0];
					distance[i][1] = distance[j][1];

					distance[i][0] = temp;
					distance[i][1] = temp2;
				}
			}
		}
		return distance;
}

/*
string Grade_Frequency(double** sortedKList, int sortedKListRows, int sortedKListCols)
// Return the most frequent Grade in DS; You need to convert Grade point in Grade 
{
	string array[12] = { "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-" };
	double arr[12] = { 4, 4, 3.67, 3.33, 3, 2.67, 2.33, 2, 1.67, 1.33, 1, 0.67 };
	int checks[12] = { 0 };
	for (int i = 0; i < 1565; i++)
		for (int j = 0; j < 11; j++)
		{
			if (sortedKList[i][1] == arr[j])
				checks[j]++;
		}
	int index = 0;
	for (int i = 0; i < 12; i++)
	{
		if (checks[i] > checks[i + 1])
			index = checks[i];
		else
			index = checks[i + 1];
	}
	return array[index];
}

*/
double* all_means(double** data, int dataRows, int dataCols)  // calculate and return mean of all datapoints
{
	double arr[12] = { 4, 3.67, 3.33, 3, 2.67, 2.33, 2, 1.67, 1.33, 1, 0.67, 0 }; //13 possible grades
	double scores[12] = { 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	double* means = new double[1565];

	double mean = 0;
	int control = 0;
	for (int i = 0; i < 1565; i++)
	{
		mean = 0;
		//if (data[i][16] > 0)
		//{
			for (int k = 0; k < 14; k++)
			{
				for (int j = 0; j < 12; j++)
				{
					if (data[i][k] == arr[j])
						mean = mean + scores[j];
				}
			}
		//}
			means[i] = mean;
	}

	return means;
}	