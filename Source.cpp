#include<stdio.h>
#include<limits.h>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// Mazimum number of inputs is equal to 100
const int MaxInputs = 100;

//funtion that reads in a file
int* ReadFile(ifstream &infile, int list[]) {
	int line = 0;
	while (!infile.eof())
	{
		for (int i = 0; i < MaxInputs; i++)
		{
			infile >> list[i];
		}
	}
	return list;
}

//returning which integer is higher
int max(int a, int b)
{
	return (a > b) ? a : b;
}

int knapsack(int weight, int weightArray[], int valueArray[], int size)
{
	//if weight or size is 0, we return that it is 0
	if (size == 0 || weight == 0)
		return 0;
	//if weight at the of the nth item is more than the weight that is input, then
	//the item at hand can't be brought
	if (weightArray[size - 1] > weight)
		return knapsack(weight, weightArray, valueArray, size - 1);
	else // returning the highest value possible 
		return max(valueArray[size - 1] + knapsack(weight - weightArray[size - 1], weightArray, valueArray, size - 1), 
			knapsack(weight, weightArray, valueArray, size - 1));
}


int main()
{
	int valueSize = 0, weightSize = 0, weight, endNum, option, number;
	int* weightArray = new int[MaxInputs];
	int* valueArray = new int[MaxInputs];
	string reRun;
	ifstream valueFile, weightFile;

	//initializing array of matricies
	for (int i = 0; i < MaxInputs; i++) {
		weightArray[i] = 0;
		valueArray[i] = 0;
	}

	while (true)
	{
		cout << "~~~~~~~~~~~~MENU~~~~~~~~~~~~" << endl
			<< "1) Type into the command line" << endl
			<< "2) Use default set of files 1" << endl
			<< "3) Use default set of files 2" << endl
			<< "4) Use default set of files 3" << endl
			<< "5) Use default set of files 4" << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "What's the number of items?" << endl;
			cin >> number;
			for (int i = 0; i < number; i++)
			{
				cout << "enter weight of item " << i+1 << endl;
				cin >> weightArray[i];
				cout << "enter value of item " << i+1 << endl;
				cin >> valueArray[i];
			}
			cout << "What's the weight you're willing to carry?" << endl;
			cin >> weight;
			break;
		case 2:
			valueFile.open("v1.txt");
			valueArray = ReadFile(valueFile, valueArray);
			weightFile.open("w1.txt");
			weightArray = ReadFile(weightFile, valueArray);
			weight = 5;
			break;
		case 3:
			valueFile.open("v2.txt");
			valueArray = ReadFile(valueFile, valueArray);
			weightFile.open("w2.txt");
			weightArray = ReadFile(weightFile, valueArray);
			weight = 10;
			break;
		case 4:
			valueFile.open("v3.txt");
			valueArray = ReadFile(valueFile, valueArray);
			weightFile.open("w3.txt");
			weightArray = ReadFile(weightFile, valueArray);
			weight = 20;
			break;
		case 5:
			valueFile.open("v4.txt");
			valueArray = ReadFile(valueFile, valueArray);
			weightFile.open("w4.txt");
			weightArray = ReadFile(weightFile, valueArray);
			weight = 40;
			break;
		default:
			break;
		}


		//getting the size of the array after ran through the file.
		for (int i = 0; i < MaxInputs; i++)
		{
			if (weightArray[i] != 0)
				weightSize++;
			if (valueArray[i] != 0)
				valueSize++;
		}

		//running through the knapsack method
		if (weightSize == valueSize && weightSize != 0 || valueSize != 0)
		{
			endNum = knapsack(weight, weightArray, valueArray, weightSize);
			cout << "\nThe highest value: " << endNum << "\n\n\n";
		}
		else
		{
			cout << "\nYou have unequal lists of weights and values" << endl;
		}
		cout << "\nWould you like to run again?" << endl;
		cin >> reRun;
		if (reRun.at(0) == 'n' || reRun.at(0) == 'N')
			break;

	}
	cout << endl;
	system("pause");
	return 0;
}