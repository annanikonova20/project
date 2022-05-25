// ConsoleApplication.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream> 
#include <string>
#include "stdlib.h"
using namespace std;

void coding(string code[256], int num) //assign code
{
	for (int i = 0; i < num - 2; i++)
	{
		code[i] = code[i] + '0';
		for (int j = i + 1; j < num; j++)
			code[j] = code[j] + '1';
	}
	code[num - 2] = code[num - 2] + '0';
	code[num - 1] = code[num - 1] + '1';
}
int main()
{
	string s;
	const int max = 256;
	int num = 0;
	cout << "Enter a string:" << endl;
	getline(cin, s);
	char sym[257];
	int freq[257];
	char meetsym[257];
	int meetfreq[257];

	for (int i = 0; i < max;i++) //filling arrays of symbols and frequencies
		sym[i] = (char)i;
	for (int i = 0; i < max;i++)
		freq[i] = 0;

	for (int i = 0;i < s.size();i++) //count the frequency for each element
		for (int j = 0;j < max;j++)
		{
			if (s[i] == sym[j])
			{
				freq[j]++;
				break;
			}
		}
	for (int i = 0;i < max;i++)//determine which symbols are met
	{
		if (freq[i] > 0)
		{
			meetsym[num] = sym[i];
			meetfreq[num] = freq[i];
			num++;
		}
	}
//
	for (int i = num - 1;i >= 0;i--) //sort symbols in order of increasing frequency
		for (int j = 0;j < i;j++)
		{
			if (meetfreq[j] < meetfreq[j + 1])
			{
				int Old = meetfreq[j];
				meetfreq[j] = meetfreq[j + 1];
				meetfreq[j + 1] = Old;

				Old = (int)meetsym[j];
				meetsym[j] = meetsym[j + 1];
				meetsym[j + 1] = (char)Old;
			}
		}

	string node[256];
	for (int i = 0; i < num; i++)
	{
		node[i] = meetsym[i];
	}
	for (int i = num - 1; i > 1; i--)
	{
		meetfreq[i - 1] = meetfreq[i - 1] + meetfreq[i]; //forming a Huffman tree
		node[i - 1] = node[i - 1] + node[i];
		if (i != 2)
		{
			for (int k = num - 1;k >= 0;k--)
				for (int j = 0;j < i;j++)
				{//
					if (meetfreq[j] < meetfreq[j + 1])
					{
						int Old = meetfreq[j];
						meetfreq[j] = meetfreq[j + 1];
						meetfreq[j + 1] = Old;

						string Old1 = (string)node[j];
						node[j] = node[j + 1];
						node[j + 1] = (string)Old1;
					}
				}
		}
	}

	string code0[256]; //assign code
	int num0 = node[0].size();
	for (int i = 0; i < num0; i++)
		code0[i] = '0';
	if (num0 != 1)
		coding(code0, num0);

	string code1[256];
	int num1 = node[1].size();
	for (int i = 0; i < num1; i++)
		code1[i] = '1';
	if (num1 != 1)
		coding(code1, num1);

	string c[256]; 
	for (int i = 0; i < num0; i++)
		c[i] = code0[i];
	for (int i = 0; i < num1; i++)
		c[i + num0] = code1[i];

	for (int i = 0;i < s.size();i++) //compressed string output
		for (int j = 0;j < num;j++)
		{
			if (s[i] == meetsym[j])
			{
				cout << c[j] << ' ';
				break;
			}
		}

	system("pause");
	return 0;
}
