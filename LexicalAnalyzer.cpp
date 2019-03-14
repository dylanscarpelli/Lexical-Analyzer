#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

ifstream myFile;
string myLine;
vector<string> v1;
vector<string> v2;
string yaya;

string myIdentifiers[50] = { "int", "bool", "string", "char", "double", "float", "vector",
"public", "private", "extern", "operator", "break", "system", "continue", "delete", "register", "volatile"
, "for", "while", "if", "else", "do", "explicit", "switch", "void", "false", "true", "class" };

string myPrimIdens[5] = { "int", "double", "float", "char", "string" };

string mySpecialChars[3] = { ",", "|", ";" };
bool isASpecialChar = false;
bool isReservedString;

bool checkforSpace(string passedString)
{
	size_t myTruth = passedString.find(' ');
	if (myTruth != string::npos)
	{
		return true;
	}
	else
		return false;
}

bool isIdentifier(string S)
{


	bool returnedValue = checkforSpace(S);
	if (returnedValue == true)
	{
		return false;
	}

	for (int i = 0; i < S.length(); i++)
	{
		if (isdigit(S.at(0)))
		{
			return false;
		}

		else if (isalnum(S[i]) == 0 && S.at(i) != '_')
		{
			return false;
		}

	}
}



int main()
{
	myFile.open("text.txt");
	if (myFile.is_open())
	{
		while (myFile >> myLine)
		{
			v2.push_back(myLine);
		}
	}
	else
	{

		cout << "File was not opened successfully" << endl;
	}


	for (size_t i = 0; i < v2.size(); i++)
	{
		isReservedString = false;
		for (size_t j = 0; j < sizeof(myPrimIdens) / sizeof(myPrimIdens[0]); j++)
		{
			if (myPrimIdens[j] == v2[i])
			{
				cout << myPrimIdens[j] << "           " << "Reserved Word" << endl;
				isReservedString = true;

			}

		}

		//Determines whether the variable has been set properly 
		/*
		Currently only working with integers NEEDS FLOAT/DOUBLE support
		*/
		size_t found = v2[i].find("=");
		if (found != string::npos)
		{
			string findtheNum = v2[i];
			string theCompleteNum;
			string theWrongNum;
			string workingTemp;
			int saveThatPosition;
			bool goodNum = true;
			for (size_t m = 0; m < findtheNum.length() - 1; m++)
			{
				if (!isdigit(findtheNum[m]) && findtheNum[m] != '=')
				{
					workingTemp += findtheNum[m];
				}

				if (isdigit(findtheNum[m]))
				{
					saveThatPosition = m;
					for (size_t n = m; n < findtheNum.length() - 1; n++)
					{


						if (isdigit(findtheNum[n]))
						{
							theCompleteNum += findtheNum[n];
							theWrongNum += findtheNum[n];
						}
						else
						{
							theWrongNum += findtheNum[n];
							goodNum = false;
						}
					}
					cout << workingTemp << "      " << "identifier" << endl;
					break;
				}
			}
			if (goodNum)
			{
				cout << theCompleteNum << "      Valid Number" << endl;
			}
			else
				cout << theWrongNum << "         not valid number " << endl;
		}







		else
		{
			bool isInvalidToken = false;
			if (isdigit(v2[i].front()))
			{

				isInvalidToken = true;
				cout << v2[i] << "      " << "Invalid Token" << endl;
			}
			else {
				string determineIdentifier = v2[i].substr(0, v2[i].length() - 1);
				if (isIdentifier(determineIdentifier) && isReservedString == false)
				{
					cout << determineIdentifier << "       " << "Identifier" << endl;
				}
				else if (isReservedString)
				{
					continue;
				}
				else
				{
					isInvalidToken = true;
					cout << determineIdentifier << "       " << "INVALID TOKEN" << endl;
				}
			}
		}


		//Special Characters

		for (size_t k = 0; k < sizeof(mySpecialChars) / sizeof(mySpecialChars[0]); k++)
		{

			if (v2[i].substr(v2[i].length() - 1, v2[i].length() - 1) == mySpecialChars[k])
			{
				size_t found1 = yaya.find(mySpecialChars[k]);
				if (found1 != string::npos)
				{
					//special character already exists within the string
					break;
				}
				else
				{
					//we have not seen the special character so we add it to a string of found special chars
					yaya += mySpecialChars[k];
					cout << mySpecialChars[k] << "      " << "Special Character " << endl;
				}
			}


		}

	}
	system("PAUSE");
}
