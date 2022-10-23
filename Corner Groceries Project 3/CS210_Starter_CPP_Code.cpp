#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

#define SCENARIO_1 1
#define SCENARIO_2 2
#define SCENARIO_3 3
#define OP_EXIT 4

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
* Calls the python function to list the frequency of all the words
*/
void scenario_1() {
	CallProcedure("listAllWordFreq");
}

/*
* Takes a word as input and passes it to the python script, which returns
* the frequency of the given word and its printed in this function.
*/
void scenario_2() {
	string word;
	cout << "Enter a word: ";
	cin >> word;
	int freq = callIntFunc("getWordFreq", word);
	cout << "Item: " << word << endl << "Freq: " << freq;
}

/*
* Calls the python script to generate the frequency data file, then
* reads it and prints a histogram.
*/
void scenario_3() {

	// Geneate frequency file
	CallProcedure("saveFreqData");

	// Open the file
	fstream freqFile("frequency.dat");

	// Go through the file and print histogram
	while (freqFile.good()) {

		string word;
		int freq;
		freqFile >> word >> freq;
		
		// String to store the required number of stars
		string star = "";

		if (word.length() > 0) {
			// Append the required number of stars to the string
			for (int i = 0; i < freq; i++)
				star += "*";

			// print the word and its freq
			printf("%15s %s\n", word.c_str(), star.c_str());
		}
	}
}

void menu() {
	while (true) {

		int choice = -1;

		system("cls");
		cout
			<< "---------------------------------------" << endl
			<< "Corner Grocer" << endl
			<< "---------------------------------------" << endl
			<< "1 - List all items purchased in a day" << endl
			<< "2 - Specific item stats" << endl
			<< "3 - Histogram of all purchases" << endl
			<< "4 - Exit" << endl << endl
			<< "Please select an option:" << endl;

		cin >> choice;

		switch (choice)
		{
		case SCENARIO_1:
			system("cls");
			scenario_1();
			break;
		case SCENARIO_2:
			system("cls");
			scenario_2();
			break;
		case SCENARIO_3:
			system("cls");
			scenario_3();
			break;
		case OP_EXIT:
			return;
		default:
			cout << "Invalid option selected!";
			break;
		}
		cout << endl;
		system("pause");
	}
}


int main()
{
	menu();
	system("pause");
	return 0;
}