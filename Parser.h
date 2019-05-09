//���ߣ�IuSpet
//���ã���һ���ķ�ת��ΪLL(1)�ķ��������﷨������

#ifndef Parser_h
#define Parser_h
#include"utlib.h"

//extern const int BUFFERLENGTH;

class Parser
{
public:
	Parser();
	void get_LL1_grammar();						//�õ�LL��1���ķ�
	void Parse();
	void print_grammar0();						//��ӡ��ʼ�ķ�
	void print_grammar1();
	void print_grammar2();						//��ӡ��ȡ�����Ӻ���ķ�
	void print_FIRST();
	void print_FOLLOW();

private:
	std::list<std::list<std::string>> grammar;		//�ķ�
	const char *grammar_file;
	const char *token_file;

	FILE* f;

	void get_grammar();								//��ȡ��ʼ�ķ�
	void Eliminate_left_recursion();				//������ݹ�
	void get_FIRST();								//��ȡFIRST����
	void get_FOLLOW();								//��ȡFOLLOW����
	bool judge_LL1_grammar();						//�ж��ǲ���LL(1)�ķ�
	void get_predict_table();						//����Ԥ�������
	void get_left_common_factor();					//��ȡ������
	std::string get_next_token();					//���ϻ����һ��token
};
#endif // !Parser_h
#pragma once
