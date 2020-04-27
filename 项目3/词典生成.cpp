#include<iostream>
#include<fstream>
#include<string>
#include<time.h> 
using namespace std;
struct Word
{
	string s;
	int num;
};
Word one[1500];
Word two[2000];
Word three[1000];
Word four[1000];
void input(const char s[], Word word[],  const int k)
{
	Word t;
	int n=0;
	ifstream infile(s);
	if (!infile) {
		cerr << "´ò¿ªÎÄ¼þ" << s << "Ê§°Ü" << endl; exit(0);
	}
	while (infile >> t.s) {
		infile >> t.num;
		if (t.num < k) break;
		else word[n++] = t;
	}
	word[n].s = "0";
}
int main()
{
	clock_t start = clock();	
	int i,j,k1,k2,k3,k4;
	k1 = k2 = k3 = k4 = 0;

	char s1[] = "D:\\1×Ö´®.txt";
	char s2[] = "D:\\2×Ö´®.txt";
	char s3[] = "D:\\3×Ö´®.txt";
	char s4[] = "D:\\4×Ö´®.txt";
	input(s1, one, 18000);
	input(s2, two,5000 );
	input(s3, three, 400);
	input(s4, four, 120);
	ofstream out;
	out.open("D:\\´ÊµäÎÄ¼þ.txt");
	for (j = 0; ; ) {
		for (i = j; i < j + 25 && k1 == 0; i++) {
			if (one[i].s == "0") { k1 = 1; break; }
			out << one[i].s << endl;
		}
		for (i = j; i < j + 25 && k2 == 0; i++) {
			if (two[i].s == "0") { k2 = 1; break; }
			out << two[i].s << endl;
		}
		for (i = j; i < j + 25 && k3 == 0; i++) {
			if (three[i].s == "0") { k3 = 1; break; }
			out << three[i].s << endl;
		}
		for (i = j; i < j + 25 && k4 == 0; i++) {
			if (four[i].s == "0") { k4 = 1; break; }
			out << four[i].s << endl;
		}
		if (k1==1&&k2==1&&k3==1&&k4==1) {
				  break;
		}
		j = j + 25;
	}
	out.close();
	clock_t ends = clock();
	cout << "Running Time : " << (double)(ends - start) / CLOCKS_PER_SEC << endl;
	cout << "³ÌÐò½áÊø" << endl;
	return 0;
}

