#include<iostream>
#include<string>
#include<cctype>
using namespace std;
const string sensi_word[3]={"L4","Fd","D26"};//敏感词
const string tolower_sensi_word[3]={"l4","fd","d26"};//将敏感词转换为小写形式
const char nonsense[]={'@','#','$',' ','\0'};//无用符号

//以下函数检查输入，如果输入符合要求，则将输入中的无用符号删除
bool IOcheck(string& str)
{
	bool flag=false;
	for(string::size_type ix=0;ix!=str.size();++ix)
	{
		if( !( isalnum(str[ix])||str[ix]==','||str[ix]=='.'||str[ix]=='"') )//不是字母数字，也不是标点符号
		{
			flag=false;
			for(int i=0;i<4;i++)
			{
				if(str[ix]==nonsense[i])//是无用符号
				{
					str.replace(ix,1,1,'*');//将该无用符号替换为*					
					flag=true;
					break;
				}
			}
			if(!flag) return false;
		}
		else str[ix]=tolower(str[ix]);//将大写字母变为小写字母
	}
	return true;
}

int main()
{
	string str,str1;//str1为str的副本，在str1上实现操作，然后再映射到str上
	while(true)
	{
	    cout<<"输入字符串（可输入一行任意多个字符）：\n";
		getline(cin,str);

		str1=str;//建立str的一个copy

		if( !IOcheck(str1) ) cout<<"输入不符合要求\n";
		else 
			break;
	};//判断输入，如果不符合要求则要重新输入

	//一下便是对str1的处理了
	for(int i=0;i<3;i++)//3个敏感词
	{
		string::size_type ix=0,ix_word=0,first=0,last=0,flag=0;//以下操作所需要的变量，在具体过程中介绍
		while(ix<str1.size())
		{//以下是不用情况下处理所需的操作
			if(str1[ix]==(tolower_sensi_word[i])[ix_word])//ix,ix_word分别为str1和敏感词的串下标
			{
				ix++;
				ix_word++;
			}
			else if(ix_word==0&&str1[ix]=='*')
			{
				ix++;				
			}
			else if(ix_word==1&&str1[ix]=='*')
			{
				ix++;
				flag++;//flag是一个标志变量，是为了控制first的值
			}
			else
			{
				if(str1[ix]==(tolower_sensi_word[i])[0])  ix_word=1;
				else ix_word=0;
				ix++;
			}
			if(ix_word==1)
			{
				first=ix;//first代表要删除字符串的首位置
				first--;
				first-=flag;
			}
			if(ix_word==tolower_sensi_word[i].size())
			{
				last=ix;//last指的是尾下标，与first对应
				last--;				
				str.erase(first,last-first+1);//映射对str删除操作
				str1.erase(first,last-first+1);//str1也要做相应的删除
				//以下是下一次循环的初始化过程
				ix=first;
				ix_word=0;
				first=0;
				last=0;
				flag=0;
			}
		}
	}		
			
	cout<<"过滤后:"<<str<<endl;
	return 0;
}