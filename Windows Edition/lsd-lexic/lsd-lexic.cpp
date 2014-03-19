// lsd-lexic.cpp: ���������� ����� ����� ��� ����������� ����������.

#include "stdafx.h"

//������������������ ���������� ����� � ������� ����������� LSD ����������
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

#define COUNT_OF_SYMBOLS 256

void lsd(string array[], int num)
{
	vector< list<string> > v;
	int depth = 0;

	v.resize(COUNT_OF_SYMBOLS); //������������� ������ �������
	// ��������������� ����������
	for (int i = 0; i < num; i++)
	{
		v[0].push_back(array[i]); //������� ���� ������ � ������� ������
		if (array[i].length() > depth) depth = array[i].length();//���� ����. ����� �����
	}

	//����������, ������� � ��������� ����
	for (depth = depth - 1; depth >= 0; depth--)
	{
		//��������� ������� ������ �� �����. �����
		list<string>::iterator i = v[0].begin();

		for (int k = 0; k < num; ++k)
		{
			if ((*i).size() > depth)
			{
				v[(*i)[depth] + 128].push_back(*i);//��������� � �����. ������
				i = v[0].erase(i);//������� �� ��������				
			}
			else
				i++;
		}

	    //��������� � �������� ������ ��� ���������
	    for (int i = 1; i < COUNT_OF_SYMBOLS; ++i)
	    	v[0].splice(v[0].end(), v[i]);
	}

	//���������� ������� ������ � ������
	list<string>::iterator i = v[0].begin();
	for (int k = 0; k < num; ++i, ++k)
	{
	    array[k] = *i;		
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
    string s;
	string arr[10] = {"bac","abc","dbac","abc","aa","a","aaaa","adb","bd","dddd"};

	for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	cout << endl;

	lsd(arr, 10);

	for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	cout << endl;

	cout << "add strings to empty array" << endl;
	for (int i = 0; i < 10; i++)
	{
	    cin >> s;
	    arr[i] = s;
	}

	lsd(arr, 10);

	for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	cout << endl;

	cin >> s;
	return 0;
}

