#include "Parser.h"

const int BUFFERLENGTH = 4096;

Parser::Parser()
{
	grammar_file = "D://cminus//grammar.txt";
	token_file = "D://cminus//token.txt";
}

void Parser::get_LL1_grammar()
{
}

void Parser::Parse()
{
}


void Parser::print_grammar0()
{
	std::ofstream outfile("D://cminus//grammar0.txt");
	//outfile.open("D://cminus//grammar0.txt", std::ios::out, 0);		//�ļ������ָ�򱣴�grammar0���ļ�
	
	get_grammar();
	for (auto l : grammar0)
	{
		bool first = true;
		for (auto t : l)
		{
			if (first)
			{
				outfile << t << " -> ";
				first = false;
			}
			else outfile << t << " | ";
		}
		outfile << std::endl << std::endl;
	}
	outfile.close();
}

void Parser::print_grammar1()
{
	Eliminate_left_recursion();
	std::ofstream outfile("D://cminus//grammar1.txt");

	for (auto l : grammar0)
	{
		bool first = true;
		for (auto t : l)
		{
			if (first)
			{
				outfile << t << " -> ";
				first = false;
			}
			else outfile << t << " | ";
		}
		outfile << std::endl << std::endl;
	}
	outfile.close();
}

//��ȡԭʼ�ķ������浽�ڴ���
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

//������ݹ�
void Parser::Eliminate_left_recursion()
{
	//TO DO:����grammar0�����ݹ�  
	for (auto p = grammar0.begin(); p != grammar0.end(); p++)
	{
		//չ����ǰ�ķ�
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
				std::string item(production);
				std::string tmp;					//��ȡproduction�еķ��ս��
				int subbg = 0, sublength = 0;			//��¼tmp���ֵ�λ�ñ���ǰ׺��׺
				for (char c:production)
				{
					if (c != ' ')
					{
						tmp.push_back(c);
						sublength++;
					}
					else							//��ȡ����һ�������ķ��ս��
					{
						if (Vn == tmp)				//�÷��ս����ǰ��Ŀ�ʼ����
						{
							//std::string prefix = production.substr(0,subbg);
							//std::string suffix = production.substr(subend);						
							pA = A.erase(pA);		//ɾ��ԭ����ʽ
							auto pB = B.begin(); pB++;
							for (; pB != B.end(); pB++)		//��production�滻ΪB�еĲ���ʽ
							{
								std::string newprd(item);
								item.replace(subbg, sublength, *pB);
								pA = A.insert(pA, item);		//�����滻��Ĳ���ʽ
							}
							pA = A.begin(); 
							break;
						}
						//std::cout << tmp << std::endl;
						subbg += sublength;
						subbg++;
						sublength = 0;
						tmp.clear();
					}
				}
				//���һ������ʽ
				if (Vn == tmp && pA != A.begin())				//�÷��ս����ǰ��Ŀ�ʼ����
				{
					//std::string prefix = production.substr(0,subbg);
					//std::string suffix = production.substr(subend);						
					pA = A.erase(pA);		//ɾ��ԭ����ʽ
					auto pB = B.begin(); pB++;
					for (; pB != B.end(); pB++)		//��production�滻ΪB�еĲ���ʽ
					{
						std::string newprd(item);
						item.replace(subbg, sublength, *pB);
						pA = A.insert(pA, item);		//�����滻��Ĳ���ʽ
					}
					pA = A.begin();
					continue;
				}
			}
		}
		//ȥ��ֱ����ݹ�

	}
}

std::string Parser::get_next_token()
{
	return std::string();
}
