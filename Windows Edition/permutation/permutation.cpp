// permutation.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

//��� ��������� ��������� ������������
//		- � ������� ������������� ������ � ��������� (������������������ �������)
//		- � ������� ������� ������������
#include <iostream>
#include <vector>
#include <list>
using namespace std;

//���������� ���������� n
long long factorial(int n)
{
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
//��������� ������������ � ������� ������������� ������ � ���������
vector< vector<int> > generate_using_backtracking(int n) //n - �������� ���������
{
    int i, j, k, m, t;
    vector< vector<int> > v;
    int power_of_set = factorial(n);

    v.resize(power_of_set);

    //������� ������� ������������ = 1 2 3 ... n
    v[0].resize(n);
    for (i = 0; i < n; i++) v[0][i] = i + 1;

    n--;//������ n - ������ ������ ������� ��������

    for (k = 1; k < power_of_set; k++) //�� 1 �� ����� ���� ������������
    {
        v[k].resize(n); //������ ������ ���������� ������

        v[k] = v[k-1]; //������� = ����������

		//���� ������ �������� - "������ �� ����� �����"
		//�.� � ������������ 3 1 6 5 8 7 2 ��� 5
        for (i = n - 1; v[k][i] > v[k][i+1]; i--);

		//���� ������ ������� � "�����", ������� > i-��
		//�.� � ������������ 3 1 6 5 8 7 2 ��� 7
        for (j = n; v[k][i] > v[k][j]; j--);

        //������ i � j ��������
		//�.� �� ������������ 3 1 6 5 8 7 2 �������� 3 1 6 7 8 5 2
        t = v[k][i];
        v[k][i] = v[k][j];
        v[k][j] = t;

        //����������� "����"
		//�.� �� ������������ 3 1 6 7 8 5 2 �������� 3 1 6 7 2 5 8
        m = (n-i)/2; //����� �������� "�����"
        for (j = 0; j < m; j++)
        {
            t = v[k][j+i+1];
            v[k][j+i+1] = v[k][n-j];
            v[k][n-j] = t;
        }
    }
    return v;
}

//��������� ������������ � ������� ������� ������������
list< vector<int> > generate_using_transposition(int n)
{
    vector<int> temp;
    list< vector<int> > l1, l2;

	temp.resize(n);
	temp[0] = 1;
	l1.push_back(temp); //������� ����������� {1} � ������ ������
    //
    for(int k = 1; k < n; k++) //���������� ��� �������� ���������, �� ������� ������ ������������
    {
    	list< vector<int> >::iterator i;
    	for (i = l1.begin(); i != l1.end(); i++) //���������� ������ ������
    	{
    		temp = *i;
    		temp[k] = k + 1;//"���������" ����� ������� � ������ ������������
    		l2.push_back(temp);//������� �� ������ ������

    		for (int j = k; j > 0; j--) //��������� k-1 ������������ � ������������
    		{
    			int t = temp[j];
    			temp[j] = temp[j-1];
    			temp[j-1] = t;
    			l2.push_back(temp); //����� ������������ ������� �� ������
    		}
    	}
    	l1 = l2; //������ ���������� ������
    	l2.clear(); //������ ���������� ������
    }

    return l1;
}

int main()
{
    int n = 4;
    vector< vector<int> > a;
    list< vector<int> > l;
    a = generate_using_backtracking(n);

    for (int i = 0; i < factorial(n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;
    l = generate_using_transposition(n);

    list< vector<int> >::iterator i;
    for (i = l.begin(); i != l.end(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (*i)[j] << ' ';
        }
        cout << endl;
    }

	int end;
	cin >> end;
}
