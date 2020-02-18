#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
struct oneword
{
	string s;
	int num;
};
struct pinyin
{
	string p;
	oneword character[110];
};
struct word
{
	string str[15];
	int sum;
};
bool cmp(const oneword &a, const oneword &b)
{
	return a.num > b.num;
}

oneword st[50000];//�����1�ִ��ļ��е��ַ�����Ƶ����
int m;//1�ִ�����
pinyin Pinyin[500];//pinyin.txt�е�ƴ������
word total[90000];
int n1;//word.txt�����дʵĸ���
pinyin intpin[30];//ת�����û������ƴ������
word choice[1000];
int nn1;
word user[100];
int n2;


void Createandsort(char str[], pinyin &pin, int n);
void dealwithpinyin(pinyin Pinyin[]);
void builtword(pinyin Pinyin[], word total[],int &n1);
void builtuserword(pinyin Pinyin[], word user[], int &n2);
void Pin(char line[], int &n, pinyin intpin[]);
void dealwithword(word total[], int &nn1, int n, int nn);
void show(int &nn1, int &n);
int main()
{	
	cout << "��ʼ\n���ڴ������ƴ���ʹʻ��ļ������Ե�ʮ����..." << endl;
	dealwithpinyin(Pinyin);
	builtword(Pinyin, total,n1);
	char c;
	char line[50];
	int n;
	int y;
	int z;
	for (;;) {
		z = 0;
		n = 0;
		cout << "�����·�����ƴ��(����س�������:\n";
		for (; ;) {
	
			c = getchar();
			if (c == '\n') break;
			else if (c > 'z' || c < 'a') {
				 z = 1; 
			}
			else   line[n++] = c;
		}
		if (z == 1) {
			cout << "������ַǷ��ַ������������룡" << endl;
			line[0] = '\0';
			fflush(stdin);
			continue;
		}
		line[n] = '\0';

		cout << line << endl;
		Pin(line, n, intpin);
		for (int i = 0; i < n; i++) {
			cout << intpin[i].p << '\t';
		}
		cout << endl;

		show(nn1, n);
		cout << "Ҫ�������������Ҫ��������1������������������" << endl;
		cin >> y;
		if (y == 1)
			;
		else {
			cout << "���������ллʹ��!" << endl; break;
		}
		cin.ignore(1, EOF);
	}
	return 0;
}

void Createandsort(char str[], pinyin &pin, int n)
{
	int i, j, k;
	for (i = 0, j = 0; i < n; j++) {
		pin.character[j].s = str[i++];
		pin.character[j].s += str[i++];
		pin.character[j].num = 0;
		for (k = 0; k < m; k++) {
			if (st[k].s == pin.character[j].s) { pin.character[j].num = st[k].num; break; }
		}
	}
	pin.character[j].s = "0";
	sort(pin.character, pin.character + j, cmp);

}
void dealwithpinyin(pinyin Pinyin[])
{
	m = 0;
	ifstream in("1�ִ�.txt");
	if (!in)
	{
		cout << "���ļ�ʧ��" << endl;
	}
	oneword  t;
	while (in >> t.s) {
		in >> t.num;
		st[m++] = t;
	}
	char str[2000];
	char c;
	int  n, k, s;
	ifstream infile("pinyin.txt");
	if (!infile)
	{
		cout << "���ļ�ʧ��" << endl;
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
				else if (c >= 0 && c <= 127) { if (c>='a'&&c<='z')Pinyin[k].p += c;  continue; }

				else  str[n++] = c;
			}
		}
		str[n] = '\0';
		Createandsort(str, Pinyin[k], n);
		k++;
		if (s == 1) break;
	}
}
void builtword(pinyin Pinyin[], word total[],int &n1)
{
	ifstream in("word.txt");
	if (!in)
	{
		cout << "���ļ�ʧ��" << endl;
	}
	word t;
	char s[40];
	int i, j, k, l;
	n1 = 0;
	string temp;
	in >> s;//����T����
	while (in >> s) {
		j = 0; l = 0;
		for (i = 0; s[i]; i = i + 2) {
			temp = s[i]; temp += s[i + 1];
			t.str[j] = temp;  j++;
		}
		t.sum = j;
		total[n1++] = t;
	}
}
void builtuserword(pinyin Pinyin[], word user[], int &n2)
{
	ifstream in("userwords.txt");
	if (!in)
	{
		cout << "���ļ�ʧ��" << endl;
	}
	word t;
	char s[40];
	int i, j, k, l;
	n2 = 0;
	string temp;
	in >> s;//����"�û��ʵ�"
	while (in >> s) {
		j = 0; l = 0;
		for (i = 0; s[i]; i = i + 2) {
			temp = s[i]; temp += s[i + 1];
			t.str[j] = temp;  j++;
		}
		t.sum = j;
		user[n2++] = t;
	}
}
void Pin(char line[], int &n, pinyin intpin[])
{
	int i, j, s;
	string pin[30];
	for (i = 0, j = 0, s = 0; line[i] != '\0'; ) {
		if (s == 0)pin[j] = line[i];
		s = 0;
		if (line[i] == 'a' || line[i] == 'e' || line[i] == 'o') {//�����һ���ַ�����ĸ
			if (!((line[i] == 'a' &&line[i + 1] == 'i') || (line[i] == 'a' &&line[i + 1] == 'o') || (line[i] == 'a' &&line[i + 1] == 'n')
				|| (line[i] == 'e'&&line[i + 1] == 'i') || (line[i] == 'e'&&line[i + 1] == 'n') || (line[i] == 'e'&&line[i + 1] == 'r')
				|| (line[i] == 'o' &&line[i + 1] == 'u') || (line[i] == 'o' &&line[i + 1] == 'n'))) {

				j++; i++;
			}
			else if (!(line[i + 1] == 'n'&&line[i + 2] == 'g')) {
				if ((line[i] == 'a' || line[i] == 'e') && (line[i + 1] == 'n' || line[i + 1] == 'r') && ((line[i + 2] == 'i') || (line[i + 2] == 'u') || (line[i + 2] == 'v') || (line[i + 2] == 'e'&&line[i + 3] == 'n'&&line[i + 4] == 'g') || (line[i + 2] == 'o'&&line[i + 3] == 'n')) || (line[i] == 'a'&&line[i + 1] == 'o'&&line[i + 2] == 'u')) {
					j++; i++;
				}
				else {
					i++; pin[j] += line[i]; j++; i++; //�������
				}
			}
			else {
				if (line[i] == 'a' && (line[i + 3] == 'u' || (line[i + 3] == 'e'&&line[i + 4] == 'n'&&line[i + 5] == 'g') || (line[i + 3] == 'o'&&line[i + 4] == 'n'))) {
					i++; pin[j] += line[i]; j++; i++;
				}
				else {
					i++; pin[j] += line[i];  i++; pin[j] += line[i]; j++; i++;
				}
			}
		}


		else if (line[i] == 't'&& line[i + 1] == 'x') {
			pin[j] = "txushan";//���������϶����ԣ�������޸�
			j++; i = i + 7;
		}

		else if (line[i] == '\'') {
			i++;
		}

		else {//�����һ������ĸ
			if (line[i + 1] == 'v') {
				i++; pin[j] += line[i]; j++; i++;
			}
			else if (line[i + 1] == 'h' && (line[i] == 's' || line[i] == 'z' || line[i] == 'c')) {
				 pin[j] += line[i + 1]; s = 1; i++;
			}
			else if (!((line[i + 1] == 'a'&&line[i + 2] == 'i') || (line[i + 1] == 'a'&&line[i + 2] == 'o') || (line[i + 1] == 'a'&&line[i + 2] == 'n')
				|| (line[i + 1] == 'e'&&line[i + 2] == 'i') || (line[i + 1] == 'e'&&line[i + 2] == 'n')
				|| (line[i + 1] == 'o'&&line[i + 2] == 'u') || (line[i + 1] == 'o'&&line[i + 2] == 'n')
				|| (line[i + 1] == 'i'&&line[i + 2] == 'a') || (line[i + 1] == 'i'&&line[i + 2] == 'e') || (line[i + 1] == 'i'&&line[i + 2] == 'o') || (line[i + 1] == 'i'&&line[i + 2] == 'u') || (line[i + 1] == 'i'&&line[i + 2] == 'n')
				|| (line[i + 1] == 'u'&&line[i + 2] == 'a') || (line[i + 1] == 'u'&&line[i + 2] == 'e') || (line[i + 1] == 'u'&&line[i + 2] == 'o') || (line[i + 1] == 'u'&&line[i + 2] == 'i') || (line[i + 1] == 'u'&&line[i + 2] == 'n')
				)) {

				i++; pin[j] += line[i]; j++; i++;
			}
			else if (!((line[i + 1] == 'a'&&line[i + 2] == 'n'&&line[i + 3] == 'g') || (line[i + 1] == 'e'&&line[i + 2] == 'n'&&line[i + 3] == 'g') || (line[i + 1] == 'o'&&line[i + 2] == 'n'&&line[i + 3] == 'g')
				|| (line[i + 1] == 'i'&&line[i + 2] == 'a'&&line[i + 3] == 'o') || (line[i + 1] == 'i'&&line[i + 2] == 'a'&&line[i + 3] == 'n') || (line[i + 1] == 'i'&&line[i + 2] == 'o'&&line[i + 3] == 'n') || (line[i + 1] == 'i'&&line[i + 2] == 'n'&&line[i + 3] == 'g')
				|| (line[i + 1] == 'u'&&line[i + 2] == 'a'&&line[i + 3] == 'i') || (line[i + 1] == 'u'&&line[i + 2] == 'a'&&line[i + 3] == 'n')
				)) {
				if (((line[i + 1] == 'a' || line[i + 1] == 'e') && (line[i + 2] == 'n' || line[i + 2] == 'r') && ((line[i + 3] == 'i') || (line[i + 3] == 'u') || (line[i + 3] == 'v') || (line[i + 3] == 'e'&&line[i + 4] == 'n'&&line[i + 5] == 'g') || (line[i + 3] == 'o'&&line[i + 4] == 'n')))
					|| (line[i + 1] == 'a'&&line[i + 2] == 'o'&&line[i + 3] == 'u')
					|| ((line[i + 1] == 'u' || line[i + 1] == 'i') && line[i + 2] == 'e' && (line[i + 3] == 'n' || line[i + 3] == 'r') && ((line[i + 4] != 'a'&&line[i + 4] != 'e'&&line[i + 4] != 'i'&&line[i + 4] != 'o'&&line[i + 4] != 'u'&&line[i + 4] != 'v')))
					|| ((line[i + 1] == 'i' || line[i + 1] == 'u') && line[i + 2] == 'e'&&line[i + 3] == 'i')
					|| (line[i + 1] == 'i'&&line[i + 2] == 'a'&&line[i + 3] == 'i')
					/*������ȷ*/ || ((line[i + 1] == 'i' || line[i + 1] == 'u') && line[i + 2] == 'n' && (line[i + 3] == 'i' || line[i + 3] == 'u' || line[i + 3] == 'v' || (line[i + 3] == 'e'&&line[i + 4] == 'n'&&line[i + 5] == 'g') || (line[i + 3] == 'o'&&line[i + 4] == 'n')))
					|| (line[i + 1] == 'u'&&line[i + 2] == 'a'&&line[i + 3] == 'o'&&line[i + 4] != 'u')
					) {
					i++; pin[j] += line[i]; j++; i++;
				}
				else {
					i++; pin[j] += line[i]; i++; pin[j] += line[i]; j++; i++;
				}
			}
			else if (line[i + 4] != 'g'||(line[i+3]=='g'&&line[i+4]=='g')) {
				if ((line[i + 1] == 'e' || line[i + 1] == 'a' || line[i + 1] == 'i') && line[i + 2] == 'n'&&line[i + 3] == 'g' && (line[i + 4] == 'u' || (line[i + 4] == 'e'&&line[i + 5] == 'n'&&line[i + 6] == 'g') || (line[i + 4] == 'o'&&line[i + 5] == 'n'))
					|| (line[i + 1] == 'i'&&line[i + 2] == 'a'&&line[i + 3] == 'o'&&line[i + 4] == 'u')
					|| ((line[i + 1] == 'i' || line[i + 1] == 'u') && line[i + 2] == 'a'&&line[i + 3] == 'n' && (line[i + 4] == 'u' || line[i + 4] == 'v' || line[i + 4] == 'i' || (line[i + 4] == 'e'&&line[i + 5] == 'n'&&line[i + 6] == 'g') || (line[i + 4] == 'o'&&line[i + 5] == 'n')))
					) {
					i++; pin[j] += line[i]; i++; pin[j] += line[i]; j++; i++;
				}
				else {
					i++; pin[j] += line[i];  i++; pin[j] += line[i]; i++; pin[j] += line[i]; j++; i++;
				}
			}
			else {
				if ((line[i + 1] == 'i' || line[i + 1] == 'u') && line[i + 2] == 'a' && (line[i + 5] == 'u' || (line[i + 5] == 'e'&&line[i + 6] == 'n'&&line[i + 7] == 'g') || (line[i + 5] == 'o'&&line[i + 6] == 'n'))) {
					i++; pin[j] += line[i];  i++; pin[j] += line[i]; i++; pin[j] += line[i]; j++; i++;
				}
				else {
					i++; pin[j] += line[i];  i++; pin[j] += line[i];   i++; pin[j] += line[i]; i++; pin[j] += line[i]; j++; i++;
				}
			}
		}
	}
	for (i = 0; i < j; i++) {
		intpin[i].p = pin[i];
	}
	cout << "�зֺ��ƴ����" << j << "��" << "��" << endl;

	n = j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 403; j++)
			if (Pinyin[j].p == intpin[i].p||intpin[i].p=="T����") {
				intpin[i] = Pinyin[j]; break;
			}
		if (j == 403)cout << "��Ǹ��û���ҵ���Ӧ��ƴ��" << endl;
	}
}
void dealwithword(word total[], int &nn1, int n, int nn)
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < total[i].sum&&j<nn; j++) {
			for (k = 0; intpin[j].character[k].s != "0"; k++)
				if (total[i].str[j] == intpin[j].character[k].s) break;
			if (intpin[j].character[k].s == "0")  break;
			else if (j == total[i].sum - 1 && total[i].sum != 1) //�����
				choice[nn1++] = total[i];
		}
}
void show(int &nn1, int &n)
{
	int i, j, x, k, t;
	t = 0;
	string s;
	string temp;
	fstream file;
	file.open("userwords.txt", ios::in);
	if (!file) {
		cout << "Ŀǰû�дʵ�" << endl;
	}
	else {
		t = 1;
		cout << "�Ѿ��дʵ��ˣ�" << endl;
		builtuserword(Pinyin, user, n2);
	}
	ofstream out;
	out.open("userwords.txt");
	out << "�û��ʵ�" << endl;
	if (t == 1) {
		for (i = 0; i < n2; i++) {
			for (j = 0; j < user[i].sum; j++)
				out << user[i].str[j];
			out << endl;
		}
	}
	for (; ;) {
		nn1 = 0;
		cout << "��ѡ�����У�" << endl;
		if (intpin[0].p == "txushan") {
			for (i = 0; i < n - 1; i++)
				intpin[i] = intpin[i + 1];
			n = n - 1;
			cout << 1 << "T����" << endl;
			s += "T����";
			if (n == 0) {
				cout << "���ս��" << endl;
				cout << s << endl;
				break;
			}
			else continue;
		}
		dealwithword(total, nn1, n1, n);
		if (t == 1) 	dealwithword(user, nn1, n2, n);

		for (i = nn1 - 1; i >= 0; i--) {
			cout << nn1 - i;
			for (j = 0; j < choice[i].sum; j++)
				cout << choice[i].str[j];
			cout << '\t';
		}
		for (i = nn1; intpin[0].character[i - nn1].s != "0"; i++)
			cout << 1 + i << intpin[0].character[i - nn1].s << '\t';
		cout << endl;
		cout << "������Ҫѡ��Ĵʵ����" << endl;
		cin >> x;
		if (x <= nn1) {
			for (j = 0; j < choice[nn1 - x].sum; j++)
				s += choice[nn1 - x].str[j];
			k = choice[nn1 - x].sum;
		}
		else {
			s += intpin[0].character[x - nn1 - 1].s;
			k = 1;
		}
		for (i = 0; i < n - k; i++)
			intpin[i] = intpin[i + k];
		n = n - k;
		if (n == 0) {
			cout << "���ս��:" << endl;
			cout << s << endl;
			for (i = 0; i < nn1; i++) {
				for (j = 0; j < choice[i].sum; j++)
					temp += choice[i].str[j];
				if (temp == s)  break;
			}
			if (i == nn1) out << s << endl;
			break;
		}
	}
}
