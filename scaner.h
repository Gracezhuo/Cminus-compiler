//���ߣ�IuSpet
//���ã���c-Դ����ת��Ϊtoken���
#ifndef Scaner_h
#define Scaner_h
#include"utlib.h"

//extern const int BUFFERLENGTH;

class Scaner
{
private:
	char buffer[4096];		//����Դ����Ļ�����
	int pos;						//������λ��
	FILE* source;
	int syn;						//token���
	int state;
	int tsss;
	const int BUFFERLENGTH = 4096;
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


#endif // !Scaner_h
#pragma once
