// ConsoleApplication.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream> 
#include <string>
#include "stdlib.h"
using namespace std;


int main()
{
	string S;
	const int max = 256;
	int num = 0;
	cout << "Enter a string" << endl;
	getline(cin, S);
	char Sym[257];
	int Freq[257];
	char MeetSym[257];
	int MeetFreq[257];
	for (int i = 0; i < max;i++)
		Sym[i] = (char)i;
	for (int i = 0; i < max;i++)
		Freq[i] = 0;
	for (int i = 0;i < S.size();i++)
		for (int j = 0;j < max;j++)
		{
			if (S[i] == Sym[j])
			{
				Freq[j]++;
				break;
			}
		}
	for (int i = 0;i < max;i++)
	{
		if (Freq[i] > 0)
		{
			MeetSym[num] = Sym[i];
			MeetFreq[num] = Freq[i];
			num++;
		}
	}
	for (int i = num - 1;i >= 0;i--)
		for (int j = 0;j < i;j++)
		{
			if (MeetFreq[j] < MeetFreq[j + 1])
			{
				int Old = MeetFreq[j];
				MeetFreq[j] = MeetFreq[j + 1];
				MeetFreq[j + 1] = Old;

				Old = (int)MeetSym[j];

				MeetSym[j] = MeetSym[j + 1];
				MeetSym[j + 1] = (char)Old;
			}
		}
	for (int i = 0;i < num;i++)
		cout << MeetSym[i] << " " << MeetFreq[i] << endl;

	string node[256];
	for (int i = 0; i < num; i++)
	{
		node[i] = MeetSym[i];
	}
	for (int i = num - 1; i > 1; i--)
	{
		MeetFreq[i - 1] = MeetFreq[i - 1] + MeetFreq[i];
		node[i - 1] = node[i - 1] + node[i];
		if (i != 2)
		{
			for (int k = num - 1;k >= 0;k--)
				for (int j = 0;j < i;j++)
				{
					if (MeetFreq[j] < MeetFreq[j + 1])
					{
						int Old = MeetFreq[j];
						MeetFreq[j] = MeetFreq[j + 1];
						MeetFreq[j + 1] = Old;

						string Old1 = (string)node[j];
						node[j] = node[j + 1];
						node[j + 1] = (string)Old1;
					}
				}
		}
	}

	string code0[256];
	int num0 = node[0].size();
	for (int i = 0; i < num0; i++)
		code0[i] = '0';
	if (num0 != 1)
	{
		for (int i = 0; i < num0 - 2; i++)
		{
			code0[i] = code0[i] + '0';
			for (int j = i + 1; j < num0; j++)
				code0[j] = code0[j] + '1';
		}
		code0[num0 - 2] = code0[num0 - 2] + '0';
		code0[num0 - 1] = code0[num0 - 1] + '1';
	}


	string code1[256];
	int num1 = node[1].size();
	for (int i = 0; i < num1; i++)
		code1[i] = '1';
	if (num1 != 1)
	{
		for (int i = 0; i < num1 - 2; i++)
		{
			code1[i] = code1[i] + '0';
			for (int j = i + 1; j < num1; j++)
				code1[j] = code1[j] + '1';
		}
		code1[num1 - 2] = code1[num1 - 2] + '0';
		code1[num1 - 1] = code1[num1 - 1] + '1';
	}

	string C[256];
	for (int i = 0; i < num0; i++)
		C[i] = code0[i];
	for (int i = 0; i < num1; i++)
		C[i + num0] = code1[i];
	for (int i = 0;i < S.size();i++)
		for (int j = 0;j < num;j++)
		{
			if (S[i] == MeetSym[j])
			{
				cout << C[j] << ' ';
				break;
			}
		}

	system("pause");
	return 0;
}