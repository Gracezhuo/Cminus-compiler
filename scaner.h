//���ߣ�IuSpet
//���ã���c-Դ����ת��Ϊtoken���
#ifndef Scaner_h
#define Scaner_h
#endif // !Scaner_h
#include"utlib.h"
#pragma once



class Scaner
{
private:
	char buffer[BUFFERLENGTH];		//����Դ����Ļ�����
	int pos;						//������λ��
	FILE* source;	
	int syn;						//token���
	int state;
	int tsss;
public:
	Scaner(const char* s)
	{
		if (source = fopen(s, "r"));
		else exit(1);
		pos = 0;
		syn = -1;
		state = 0;
		fgets(buffer, BUFFERLENGTH, source);
	}
	void GetToken();
	bool IsNum(const char c);
	bool IsLetter(const char c);
	char GetNext();					//��ȡ��һ���ַ�
	void Back();					//��ǰ��������
};