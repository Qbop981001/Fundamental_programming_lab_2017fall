#include <iostream>
#include<fstream>
#include <cstdlib>    
#include <map>    
#include <vector>    
#include <string>    
#include <algorithm>
#include<time.h>
#define MAXLINE 2800000
using namespace std;
string line[MAXLINE];
map<string, int> tMap;
vector<pair<string, int>> tVector;
pair<map<string, int>::iterator, bool> ret;
int cmp(const pair<string, int>& x, const pair<string, int>& y)
{
	return x.second > y.second;
}
void word(string line[], int n)
{

	int i, j, k; string word, temp;

	for (i = 0; i<n; i++) {
		for (j = 0; line[i][j]; j++)
			;
		k = j;
		for (j = 0; j<k - 7; ) {
			temp = line[i][j];
			temp += line[i][j + 1];
			temp += line[i][j + 2];
			temp += line[i][j + 3];
			temp += line[i][j + 4];
			temp += line[i][j + 5];
			temp += line[i][j + 6];
			temp += line[i][j + 7];
			if (('0' - temp[0]) <= 128 && ('0' - temp[2]) <= 128 && ('0' - temp[4]) <= 128 && ('0' - temp[6]) <= 128) {

				word = temp;
				ret = tMap.insert(make_pair(word, 1));
				if (!ret.second)
					++ret.first->second;
			}
			j = j + 8;
		}
	}

}
void sortMapByValue(map<string, int>& tMap, vector<pair<string, int> >& tVector)
{
	for (map<string, int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));

	sort(tVector.begin(), tVector.end(), cmp);
}
int main()
{
	clock_t start = clock();
	char str[2000];
	char c;
	char test[1];
	test[0] = '\0';
	int  n, k, s;
	ifstream infile("中文文本2.txt");
	if (!infile)
	{
		cout << "打开文件失败" << endl;
	}
	k = 0;
	for (; ; ) {
		s = 0;
		n = 0;
		for (; ; ) {
			if (infile.eof()) { s = 1; break; }
			else {
				infile.get(c);

				if (c == '\n')  break;
				else if (c >= 0 && c <= 127) continue;

				else  str[n++] = c;
			}
		}

		str[n] = '\0';
		if (strcmp(str, test) == 0)
			;
		else
		{
			int len;
			len = strlen(str);

			line[k] = str;
			k++;
		}
		if (k == MAXLINE - 1) { cout << "超出数组范围" << endl; break; }
		if (s == 1) break;
	}
	line[k] = test;
	cout << k << endl;//输入文本文件中的数据

	word(line, k);

	sortMapByValue(tMap, tVector);
	ofstream out;
	out.open("D:\\4字串.txt");
	for (int i = 0; i<tVector.size(); i++)
		out << tVector[i].first << '\t' << tVector[i].second << endl;
	clock_t ends = clock();
	cout << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC << endl;
	cout << "程序结束" << endl;
	system("pause");
	return 0;
}
