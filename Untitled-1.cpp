#include<iostream>
#include<fstream>
#include<sstream>
#include<list>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
class MGC//敏感词类
{
public:
	string w;//敏感词
	int num;//敏感词号
	int l;//utf-8码长度
	int k;//1为汉字，0为英文
}Mgc[105];//敏感词上限100个
int Mgc_sum;//敏感词总数


class HANG//文章的行类
{
public:
	string s;//行内容
	int num;//行号
	int l;//utf-8码长度
}Hang[1005];//文章上限1000行
int Hang_sum;//行总数


class ANS//答案类
{
public:
	int mgc_num;//敏感词号（从0开始记,下同）
	int hang_num;//行号
	int h, e;//可疑文本的行内范围
}Ans[3005];//答案上限3000条
int Ans_num;//答案条数


void search(MGC& M, HANG& H)//输入对应的敏感词和行，不破坏行和词本身，检测到敏感字段即存入答案类
{
	int i = 0, j = 0, head;
	if (M.k == 1)//敏感词为汉字
	{
		//连续3个字节相同，则进行匹配；若敏感词长度为n字节，则需匹配n/3次才算完成
		for (; j < H.l; j++) if (H.s[j] == M.w[i])
		{
			if (i == 0) head = j;//第一次匹配时，对文章对应位置定位
			i += 3;
			j += 2;
			if (i == M.l)//匹配完成，记录信息，从当前位置继续查找该敏感词
			{
				i = 0;
				Ans[Ans_num].mgc_num = M.num;
				Ans[Ans_num].hang_num = H.num;
				Ans[Ans_num].h = head;
				Ans[Ans_num++].e = j;
			}
		}
	}
	else//敏感词为英文
	{
		//不区分大小写，相同则匹配；若敏感单词长度为m字节，则匹配m次
		for (; j < H.l; j++) if ((H.s[j] == M.w[i]))
		{
			if (i == 0) head = j;
			i++;
			if (i == M.l)//匹配完成，记录信息，从当前位置继续查找该敏感词
			{
				i = 0;
				Ans[Ans_num].mgc_num = M.num;
				Ans[Ans_num].hang_num = H.num;
				Ans[Ans_num].h = head;
				Ans[Ans_num++].e = j;
			}
		}
	}
}


void ANS_print()//答案输出到指定路径
{
	string dz;
	cin >> dz;
	ofstream f3(dz);
	if (!f3) cout << "open error!" << endl;
	f3 << "Total: " << Ans_num << endl;
	for (int i = 0; i < Ans_num; i++)
	{
		f3 << "Line" << Ans[i].hang_num + 1 << ": " << '<' << Mgc[Ans[i].mgc_num].w << "> ";
		for (int j = Ans[i].h; j <= Ans[i].e; j++) f3.put(Hang[Ans[i].hang_num].s[j]);
		f3 << endl;
	}
	f3.close();
}


int main()
{
	system("chcp 65001");//将控制台设置为utf-8编码
	int i = 0, j = 0;
	Ans_num = 0;
	string dz;//地址：临时存放文件的路径
	string str;//临时存放读入的词或句


	//读入敏感词文件f1，并放入敏感词类的数组（Mgc[]）中
	cin >> dz;
	ifstream f1(dz);
	if (!f1) cout << "open error!" << endl;
	while (f1 >> str)//逐词读入
	{
		Mgc[i].w = str;
		Mgc[i].k = Mgc[i].w[0] > 0 ? 0 : 1;
		Mgc[i].num = i;
		Mgc[i++].l = str.length();
	}
	Mgc_sum = i;
	//for (i = 0; i < Mgc_sum; i++) cout << Mgc[i].w << "     " << Mgc[i].num << "     " << Mgc[i].k <<endl;//测试
	f1.close();


	//读入文本文件f2，并放入文章的行类的数组（Hang[]）中
	cin >> dz;
	ifstream f2(dz);
	if (!f2) cout << "open error!" << endl;
	while (getline(f2, str))//逐行读入
	{
		Hang[j].s = str;
		Hang[j].num = j;
		Hang[j++].l = str.length();
	}
	Hang_sum = j;
	//for (j = 0; j < Hang_sum; j++) cout << Hang[j].s << "     " << Hang[j].num << "     " << endl;//测试
	f2.close();


	//行-词遍历，得到结果放入答案类数组（Ans[]）中
	for (j = 0; j < Hang_sum; j++) for (i = 0; i < Mgc_sum; i++) search(Mgc[i], Hang[j]);


	//将结果输出到答案文件f3
	ANS_print();
	return 0;
}
