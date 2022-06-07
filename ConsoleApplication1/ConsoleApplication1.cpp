// ConsoleApplication.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream> 
#include <string>
#include "stdlib.h"
using namespace std;

void coding(string code[256], int num, char meetSym[256], string node, int freq[256]) //assign code
{
	int freq1 = 0, freq2 = 0; int ifFour = 0;
	for (int i = 0; i < num - 2; i++)
	{
		for (int k = 0; k < num; k++)
			if (node[i] == meetSym[k])
			{
				freq1 = freq[k];
				break;
			}
		for (int k = 0; k <= num; k++)
			if (node[i+1] == meetSym[k])
			{
				freq2 = freq[k];
				break;
			}
		if (freq1 > freq2)
		{
		code[i] = code[i] + '0';
		for (int j = i + 1; j < num; j++)
			code[j] = code[j] + '1';
		//break;
		}
		else
		{
			if (i == num - 3)
				code[i] = code[i] + '0';
			if (i == num - 4)
			{
				code[i] = code[i] + '0';
				code[i] = code[i] + '0';
				code[i + 1] = code[i + 1] + '0';
				code[i + 1] = code[i + 1] + '1';
				code[i + 2] = code[i + 2] + '1';
				code[i + 2] = code[i + 2] + '0';
				code[i + 3] = code[i + 3] + '1';
				code[i + 3] = code[i + 3] + '1';
				ifFour += 1;
				break;
			}

			code[i+1] = code[i+1] + '1';
			code[i+2] = code[i+2] + '1';
			i++;
		}

	}
	if (ifFour != 1)
	{
		code[num - 2] = code[num - 2] + '0';
		code[num - 1] = code[num - 1] + '1';
	}
}
int main()
{
	string s;
	const int maxNum = 256;
	int num = 0;
	cout << "Enter a string:" << endl;
	getline(cin, s);
	char symbols[maxNum];
	int freq[maxNum];
	char meetSym[maxNum];
	int meetFreq[maxNum];
	int meetFreqForOutput[maxNum];

	for (int i = 0; i < maxNum;i++) //filling arrays of symbols and frequencies
		symbols[i] = (char)i;
	for (int i = 0; i < maxNum;i++)
		freq[i] = 0;

	for (int i = 0;i < s.size();i++) //count the frequency for each element
		for (int j = 0;j < maxNum;j++)
		{
			if (s[i] == symbols[j])
			{
				freq[j]++;
				break;
			}
		}
	for (int i = 0;i < maxNum;i++)//determine which symbols are met
	{
		if (freq[i] > 0)
		{
			meetSym[num] = symbols[i];
			meetFreq[num] = freq[i];
			num++;
		}
	}

	for (int i = num - 1;i >= 0;i--) //sort symbols in order of increasing frequency
		for (int j = 0;j < i;j++)
		{
			if (meetFreq[j] < meetFreq[j + 1])
			{
				int Old = meetFreq[j];
				meetFreq[j] = meetFreq[j + 1];
				meetFreq[j + 1] = Old;

				Old = (int)meetSym[j];
				meetSym[j] = meetSym[j + 1];
				meetSym[j + 1] = (char)Old;
			}
		}
	for (int i = 0; i < num; i++)
		meetFreqForOutput[i] = meetFreq[i];
	string node[256];
	for (int i = 0; i < num; i++)
	{
		node[i] = meetSym[i];
	}
	int flag = 0;
	for (int i = num - 1; i > 1; i--)
	{
		if (node[i].size() != 1)
		{
			meetFreq[i - 1] = meetFreq[i - 1] + meetFreq[i]; //forming a Huffman tree
			node[i - 1] = node[i - 1] + node[i];
		}
		else 
		{
			meetFreq[i - 1] = meetFreq[i - 1] + meetFreq[i];
			node[i - 1] = node[i] + node[i - 1];
		}

		if (i != 2)
		{

			for (int k = num - 1;k >= 0;k--)
				for (int j = 0;j < i;j++)
				{
					if (meetFreq[j] < meetFreq[j + 1])
					{
						int Old = meetFreq[j];
						meetFreq[j] = meetFreq[j + 1];
						meetFreq[j + 1] = Old;

						string Old1 = (string)node[j];
						node[j] = node[j + 1];
						node[j + 1] = (string)Old1;
						flag = 1;
					}
				}
		}
	}

	string code0[256]; //assign code
	int num0 = node[0].size();
	for (int i = 0; i < num0; i++)
		code0[i] = '0';
	if (num0 != 1)
		coding(code0, num0, meetSym, node[0], meetFreqForOutput);

	string code1[256];
	int num1 = node[1].size();
	for (int i = 0; i < num1; i++)
		code1[i] = '1';
	if (num1 != 1)
		coding(code1, num1, meetSym, node[1], meetFreqForOutput);

	cout << node[0] << ' ' << node[1];							

	string codeArray[256]; 
	for (int i = 0; i < num0; i++)
		codeArray[i] = code0[i];
	for (int i = 0; i < num1; i++)
		codeArray[i + num0] = code1[i];
	cout << endl;
	cout << "Met symbols and their codes:" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << meetSym[i] << ' ' << meetFreqForOutput[i] << ' ' << codeArray[i] << endl;
	}

	string sOut, strDecode;
	cout << endl;  //compressed string output
	cout << "Compressed string:"; 
	for (int i = 0;i < s.size();i++)
		for (int j = 0;j < num;j++)
		{
			if (s[i] == meetSym[j])
			{
//				cout << codeArray[j] << ' ';
				sOut = sOut + codeArray[j];
				sOut +=  ' ';
				break;
			}
		}
	cout << endl << sOut << endl << endl << "Decoded string: " << endl;

	for (int i = 0; i < sOut.size(); i++)	//decoding 
	{
		if(sOut[i] != ' ')
			strDecode = strDecode + sOut[i];
		else
		{
			for (int j = 0; j < s.size(); j++)
			{
				if (strDecode == codeArray[j])
					cout << meetSym[j];
			}
			strDecode.clear();
		}
	}
	cout << endl;
	system("pause");
	return 0;
}
