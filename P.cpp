#include<iostream>
#include<string>
#include<cctype>
using namespace std;
const string sensi_word[3]={"L4","Fd","D26"};//���д�
const string tolower_sensi_word[3]={"l4","fd","d26"};//�����д�ת��ΪСд��ʽ
const char nonsense[]={'@','#','$',' ','\0'};//���÷���

//���º���������룬����������Ҫ���������е����÷���ɾ��
bool IOcheck(string& str)
{
	bool flag=false;
	for(string::size_type ix=0;ix!=str.size();++ix)
	{
		if( !( isalnum(str[ix])||str[ix]==','||str[ix]=='.'||str[ix]=='"') )//������ĸ���֣�Ҳ���Ǳ�����
		{
			flag=false;
			for(int i=0;i<4;i++)
			{
				if(str[ix]==nonsense[i])//�����÷���
				{
					str.replace(ix,1,1,'*');//�������÷����滻Ϊ*					
					flag=true;
					break;
				}
			}
			if(!flag) return false;
		}
		else str[ix]=tolower(str[ix]);//����д��ĸ��ΪСд��ĸ
	}
	return true;
}

int main()
{
	string str,str1;//str1Ϊstr�ĸ�������str1��ʵ�ֲ�����Ȼ����ӳ�䵽str��
	while(true)
	{
	    cout<<"�����ַ�����������һ���������ַ�����\n";
		getline(cin,str);

		str1=str;//����str��һ��copy

		if( !IOcheck(str1) ) cout<<"���벻����Ҫ��\n";
		else 
			break;
	};//�ж����룬���������Ҫ����Ҫ��������

	//һ�±��Ƕ�str1�Ĵ�����
	for(int i=0;i<3;i++)//3�����д�
	{
		string::size_type ix=0,ix_word=0,first=0,last=0,flag=0;//���²�������Ҫ�ı������ھ�������н���
		while(ix<str1.size())
		{//�����ǲ�������´�������Ĳ���
			if(str1[ix]==(tolower_sensi_word[i])[ix_word])//ix,ix_word�ֱ�Ϊstr1�����дʵĴ��±�
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
				flag++;//flag��һ����־��������Ϊ�˿���first��ֵ
			}
			else
			{
				if(str1[ix]==(tolower_sensi_word[i])[0])  ix_word=1;
				else ix_word=0;
				ix++;
			}
			if(ix_word==1)
			{
				first=ix;//first����Ҫɾ���ַ�������λ��
				first--;
				first-=flag;
			}
			if(ix_word==tolower_sensi_word[i].size())
			{
				last=ix;//lastָ����β�±꣬��first��Ӧ
				last--;				
				str.erase(first,last-first+1);//ӳ���strɾ������
				str1.erase(first,last-first+1);//str1ҲҪ����Ӧ��ɾ��
				//��������һ��ѭ���ĳ�ʼ������
				ix=first;
				ix_word=0;
				first=0;
				last=0;
				flag=0;
			}
		}
	}		
			
	cout<<"���˺�:"<<str<<endl;
	return 0;
}