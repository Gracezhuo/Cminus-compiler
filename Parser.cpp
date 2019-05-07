#include "Parser.h"

const int BUFFERLENGTH = 4096;

Parser::Parser(const char * gf, const char * tf)
{
	grammar_file = gf;
	token_file = tf;
}

void Parser::get_LL1_grammar()
{
}

void Parser::Parse()
{
}

void Parser::print_grammar0()
{
	get_grammar();
	for (auto l : grammar0)
	{
		bool first = true;
		for (auto t : l)
		{
			if (first)
			{
				std::cout << t << " -> ";
				first = false;
			}
			else std::cout << t << " | ";
		}
		std::cout << std::endl << std::endl;
	}
}

void Parser::get_grammar()
{
	f = fopen(grammar_file, "r");
	char input_buffer[BUFFERLENGTH];
	while (fgets(input_buffer, BUFFERLENGTH, f))
	{
		std::list<std::string> tmp;
		int len = strlen(input_buffer);
		std::string str;
		int pos = 0;
		for (int i = 0; i < len; i++)
		{
			if (input_buffer[i] == ' ' && str.length() == 0) continue;
			else if (input_buffer[i] == '|')
			{
				while (str.back() == ' ') str.pop_back();
				tmp.push_back(str);
				str.clear();
				pos = 0;
			}
			else if (input_buffer[i] == -95)
			{
				while (str.back() == ' ') str.pop_back();
				tmp.push_back(str);
				str.clear();
				pos = 0;
				i++;
			}
			else str.push_back(input_buffer[i]);
		}
		while (str.back() == ' ' || str.back() == '\n') str.pop_back();
		tmp.push_back(str);
		grammar0.push_back(tmp);
	}
}

void Parser::Eliminate_left_recursion()
{
	//TO DO:����grammar0�����ݹ�
	for (auto p = grammar0.begin(); p != grammar0.end(); p++)
	{
		for (auto j = grammar0.begin(); j != p ; j++)
		{
			//�滻A����ʽ�е�Vn
			std::list<std::string> &A = *p;			//�ķ�A
			std::list<std::string> &B = *j;			//�ķ�B
			std::string &Vn = B.front();			//�ķ�B�Ŀ�ͷ
			auto pA = A.begin(); pA++;
			//auto pB = B.begin(); pB++;
			for (; pA != A.end(); pA++)				
			{
				std::string &production = *pA;		//�ķ�A�еĲ���ʽ
				std::string tmp;					//��ȡproduction�еķ��ս��
				int subbg = 0, subend = 0;			//��¼tmp���ֵ�λ�ñ���ǰ׺��׺
				for (char c : production)
				{
					if (c != ' ') tmp.push_back(c);
					else							//��ȡ����һ�������ķ��ս��
					{
						if (Vn == tmp)				//�÷��ս����ǰ��Ŀ�ʼ����
						{
							std::string prefix = production.substr();
							std::string suffix = production.substr();
							auto pB = B.begin(); pB++;
							for (; pB != B.end(); pB++)		//��production�滻ΪB�еĲ���ʽ
							{
								  
							}
						}
					}
				}
			}
		}
	}
}

std::string Parser::get_next_token()
{
	return std::string();
}
