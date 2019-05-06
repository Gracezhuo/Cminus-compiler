//���ߣ�IuSpet
//���ã���һ���ķ�ת��ΪLL(1)�ķ��������﷨������

#ifndef Parser_h
#define Parser_h
#include"utlib.h"

//extern const int BUFFERLENGTH;

class Parser
{
public:
	Parser(const char *gf, const char *tf);
	void get_LL1_grammar();						//�õ�LL��1���ķ�
	void Parse();
	void print_grammar0();						//��ӡ��ʼ�ķ�

private:
	std::list<std::list<std::string>> grammar0;		//��ʼ�ķ�
	std::list<std::list<std::string>> grammar1;		//������ݹ����ķ�
	std::list<std::list<std::string>> grammar2;		//ȥ�������Ӻ���ķ�
	const char *grammar_file;
	const char *token_file;

	FILE* f;

	void get_grammar();								//��ȡ��ʼ�ķ�
	void Eliminate_left_recursion();				//������ݹ�
	std::string get_next_token();					//���ϻ����һ��token
};
#endif // !Parser_h
#pragma once
