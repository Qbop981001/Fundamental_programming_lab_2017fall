#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<iomanip>
#define MAXVAL	100
using namespace std;
class Matrix
{
private:
	int m, n;
	double A[50][50];
public:
	void input();
	void fileinput();
	void show();
	Matrix operator+(Matrix &B);
	Matrix operator-(Matrix &B);
	Matrix operator*(Matrix &B);
	Matrix inverse();
	Matrix operator/(Matrix &B);

};
void Matrix::fileinput()
{
	string filename;
	cout << "�������ļ���" << endl;
	cin >> filename;
	ifstream infile(filename);
	if (!infile) {
		cerr << "���ļ�" << filename << "ʧ�ܣ�"; exit(0);
	}
	infile >> m >> n;
	if (m < 1 || n < 1) { cout << "�ļ���������󣬾��������������������ڵ���1��" << endl; exit(0); }
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			infile >> A[i][j];
}
void Matrix::input()
{
	for (; ;) {
		cout << "����������������������" << endl;
		cin >> m >> n;
		if (m < 1 || n < 1) { cout << "������󣬾��������������������ڵ���1��" << endl; continue; }
		else break;
	}
	cout << "���������" << endl;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> A[i][j];
}
void Matrix::show()
{
	cout << "����������" << m << endl;
	cout << "����������" << n << endl;
	cout << "����" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout <<fixed<<setprecision(2)<< A[i][j] << '\t';
		cout << endl;
	}
}
Matrix Matrix::operator+(Matrix &B)
{
	Matrix X;
	if (m != B.m || n != B.n) { cout << "���������������������ȣ��޷���ӣ�" << endl; exit(0); }
	X.m = m; 
	X.n = n; 
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			X.A[i][j] = A[i][j] + B.A[i][j];

	return X;
}
Matrix Matrix::operator-(Matrix &B)
{
	Matrix X;
	if (m != B.m || n != B.n) { cout << "���������������������ȣ��޷��������" << endl; exit(0); }
	X.m = m; 
	X.n = n; 
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			X.A[i][j] = A[i][j] - B.A[i][j];
	return X;
}
Matrix Matrix::operator*(Matrix &B)
{
	Matrix X; int i, j, k;
	if ( n != B.m) { cout << "ǰһ����������������ں�һ��������������޷���ˣ�" << endl; exit(0); }
	X.m = m;
	X.n = B.n;
	for(i=0; i<X.m; i++)
		for (j = 0; j < X.n; j++) {
			X.A[i][j] = 0;
			for (k = 0; k < n; k++) {
				X.A[i][j] += A[i][k]*B.A[k][j];
			}
		}
	return X;
}

double getdet(double A[][50], const int n)
{
	double temp[50][50];
	int i, j, k;
	if (n == 1)
		return A[0][0];
	double det = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			temp[i][j] = 0.0;
	for (j = 0; j < n; j++) {
		for (i = 0; i < n - 1; i++)
			for (k = 0; k < n - 1; k++)
				temp[i][k] = A[i + 1][(k >= j) ? k + 1 : k];
		double t = getdet(temp, n - 1);
		if (j % 2 == 0)
			det += A[0][j] * t;
		else
			det -= A[0][j] * t;
	}
	return det;
}
void getAa(double A[50][50], int n, double Aa[50][50])
{
	if (n == 1)	Aa[0][0] = 1;
	double temp[50][50];
	int i, j, k, t;
	for (i = 0; i < n ;i++)
		for (j = 0; j < n; j++) {
			for (k = 0; k < n - 1; k++)
				for (t = 0; t < n - 1; t++)
					temp[k][t] = A[(k >= i) ? k + 1 : k][(t >= j) ? t + 1 : t];
			Aa[j][i] = getdet(temp, n - 1);
			if ((i + j) % 2 == 1)
				Aa[j][i] = -Aa[j][i];
		}
}
Matrix Matrix::inverse()
{
	if (m != n)	cout << "�����Ƿ��󣬲����棡" << endl;
	if (getdet(A, n) == 0) cout << "���󲻿��棡" << endl;
	int i, j;
	double Aa[50][50]; Matrix X;
	X.m = X.n = n;
	double det = getdet(A, n);
	getAa(A, n, Aa);
	for (i = 0; i<X.m; i++)
		for (j = 0; j < X.n; j++)
			X.A[i][j] = Aa[i][j] / det;
	return X;

}
Matrix Matrix::operator/(Matrix &B)
{
	Matrix b,X;
	int i, j, k;
	if (n != B.m) { cout << "��һ����������������ڵڶ���������������������޷������" << endl; exit(0); }
	X.m = m;
	X.n = B.n;
	b=B.inverse();
	for (i = 0; i<X.m; i++)
		for (j = 0; j < X.n; j++) {
			X.A[i][j] = 0;
			for (k = 0; k < n; k++) {
				X.A[i][j] += A[i][k] * b.A[k][j];
			}
		}
	return X;
}
static int sp = 0;
static int sq = 0;
Matrix val[MAXVAL];
char opr[MAXVAL];
void pushnum(Matrix f)
{
	if (sq<MAXVAL)
		val[sq++] = f;
	else
		cout << "����ջ����1" << endl;
}
void pushopr(char ch)
{
	if (sp<MAXVAL)
		opr[sp++] = ch;
	else
		cout << "����ջ����" << endl;
}
Matrix popnum()
{
	if (sq>0) {
		return val[--sq];
	}
	else {
		cout << "����ջ�ѿ�" << endl;
	}
}
Matrix topnum()
{
	if (sq>0)
		return val[sq - 1];
	else {
		cout << "����ջ�ѿ�1" << endl;
	}
}
char popopr()
{
	if (sp>0)
		return opr[--sp];
	else {
		cout << "����ջ�ѿ�" << endl;
		return 0.0;
	}
}
char topopr()
{
	if (sp>0) {
		return opr[sp - 1];
	}
	else {
		cout << "����ջ�ѿ�" << endl;
		return 0.0;
	}
}
Matrix EvaluateExpression(Matrix A[10],int k);
int main(){
	int x,k;
	k = 0;
	Matrix A[10];
	cout << "Ҫͨ���ļ����뻹��Ҫͨ���������룿�ļ�����������1��������������2���������������������0." << endl;
	while (cin >> x) {
		
		if (x == 1) {
			A[k].fileinput(); k++;
		}
		else if(x == 2) {
			A[k].input();	k++;
		}
		else if (x == 0) break;
		else {
			cout << "�������" << endl;	continue;
		}
		cout << "Ҫͨ���ļ����뻹��Ҫͨ���������룿�ļ�����������1��������������2���������������������0." << endl;
	}
	char ch; int i;
	for (i = 0,ch='A'; i < k&&ch<='Z'; i++,ch++) {
		cout << "�������" << endl;
		cout << "����" <<ch<< endl;
		A[i].show();
		cout << endl;
	}
	k = 0;
	for (; ; ) {
		cout << "�������йؾ�����������ʽ(����A,B,C,D.....�Ѿ����������)\n";
		EvaluateExpression(A,k);
		k++;
		cout << "��Ҫ�����������������Ҫ��������0" << endl;
		cin >> x;
		if (x == 0) break;
	}

	return 0;
}

char Precede(char t1, char t2)
{	//�ж�t1,t2�����ŵ����ȹ�ϵ('#'��'#'����)
	char f;
	switch (t2)
	{
	case '+':
	case '-':
		if (t1 == '(' || t1 == '#')
			f = '<';	//t1<t2
		else
			f = '>';	//t1>t2
		break;
	case '*':
	case '/':
		if (t1 == '*' || t1 == '/' || t1 == ')')
			f = '>';	//t1>t2
		else
			f = '<';	//t1<t2
		break;
	case '(':
		if (t1 == ')')
		{
			cout << "���Ų�ƥ��" << endl;
			exit(0);
		}
		else
			f = '<';	//t1<t2
		break;
	case ')':
		switch (t1)
		{
		case '(': f = '='; //t1=t2
			break;
		case '#':
			cout << "ȱ��������" << endl;
			exit(0);
		default: f = '>';	//t1>t2
		}
		break;
	case '\n':
		switch (t1)
		{
		case '#':
			f = '=';	//t1=t2
			break;
		case '(':
			cout << "ȱ��������" << endl;
			exit(0);
		default: f = '>';	//t1>t2
		}
	}
	return f;
}

bool IsOperator(char c)	//�ж�c�Ƿ�Ϊ7�������֮һ
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '#':
	case '\n':
		return true;
	default:
		return false;
	}
}
Matrix Operate(Matrix A, char oper, Matrix B)
{	//������a theta b,����������
	Matrix X;
	switch (oper)
	{
	case '+':
		X = A + B;  return X;
	case '-':
		X = A - B; return X;
	case '*':
		X = A*B; return A*B;
	default:
		break;
	}
	X = A / B;
	return A/B;
}

Matrix EvaluateExpression(Matrix A[10],int k)
{
	//���ò�����ջ�Ͳ�����ջ
	Matrix a, b, X, M;
	char x;
	char c;
	
	c = getchar();
	
	pushopr('#');

	c = getchar();
	x = topopr();
	while (c != '\n' || x != '#')
	{
		if (IsOperator(c))
		{
			switch (Precede(x, c))
			{
			case'<':
				pushopr(c);
				c = getchar();
				break;
			case'=':
				x = topopr();
				popopr();
				c = getchar();
				break;
			case'>':
				x = topopr();
				popopr();

				b = topnum();
				popnum();

				a = topnum();
				popnum();

				pushnum(Operate(a, x, b));
			}
		}
		else if (c >= 'A'&&c <= 'Z')
		{
			X = A[c - 'A'];
			pushnum(X);
			c = getchar();
		}
		else if (c == '|')
		{
			a = topnum();
			popnum();
			b = a.inverse();
			pushnum(b);
			c = getchar();
		}
		else
		{
			cout << "���ַǷ��ַ�" << endl;
			exit(0);
		}
		x = topopr();
	}
	M = topnum();
	M.show();
	popnum();
	return M;
}
