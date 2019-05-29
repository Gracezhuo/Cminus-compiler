//���ߣ�IuSpet
//���ã���c-Դ����ת��Ϊtoken���

#ifndef Scanner_h
#define Scanner_h
#include"utlib.h"

class Scanner
{
private:
	char buffer[4096];		//����Դ����Ļ�����
	int pos;						//������λ��
	FILE* source;
	int syn;						//token���
	int state;						//DFA�е�״̬
	//int tsss;
	const int BUFFERLENGTH = 4096;
public:
	Scanner(const char* s)
	{
		if (source = fopen(s, "r"));
		else exit(1);
		pos = 0;
		syn = -1;
		state = 0;
		fgets(buffer, BUFFERLENGTH, source);
		
	}
	void GetToken();				//��DFA��ת�ƣ�ʶ��token
	bool IsNum(const char c);
	bool IsLetter(const char c);
	char GetNext();					//��ȡ��һ���ַ�
	void Back();					//��ǰ��������
};


#endif // !Scaner_h
#pragma once
