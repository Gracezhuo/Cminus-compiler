#include "Parser.h"

const int BUFFERLENGTH = 4096;

//���캯��ָ���ķ��ļ���token�ļ�
Parser::Parser()
{
	grammar_file = "D://cminus//grammar.txt";
	token_file = "D://cminus//token.txt";
}

//ȥ����ݹ顢�����ӡ�����FIRST��FOLLOW�����ж�LL(1)�ķ�
void Parser::get_LL1_grammar()
{
}

//����token�������﷨��
void Parser::Parse()
{
}

//��ӡ���ļ��ж�ȡ���ķ����
void Parser::print_grammar0()
{
	std::ofstream outfile("D://cminus//grammar0.txt");
	//outfile.open("D://cminus//grammar0.txt", std::ios::out, 0);		//�ļ������ָ�򱣴�grammar0���ļ�
	
	get_grammar();
	for (auto l : grammar)
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

//��ӡȥ����ݹ����ķ����
void Parser::print_grammar1()
{
	Eliminate_left_recursion();
	std::ofstream outfile("D://cminus//grammar1.txt");

	for (auto l : grammar)
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

void Parser::print_grammar2()
{
	get_left_common_factor();
	std::ofstream outfile("D://cminus//grammar2.txt");

	for (auto l : grammar)
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

void Parser::print_FIRST()
{
}

void Parser::print_FOLLOW()
{
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
		grammar.push_back(tmp);
	}
}

//������ݹ�
void Parser::Eliminate_left_recursion()
{
	//TO DO:����grammar�����ݹ�  
	for (auto p = grammar.begin(); p != grammar.end(); p++)
	{
		std::list<std::string> &A = *p;			//�ķ�A
		//չ����ǰ�ķ�
		for (auto j = grammar.begin(); j != p ; j++)
		{
			//�滻A����ʽ�е�Vn			
			std::list<std::string> &B = *j;			//�ķ�B
			std::string &Vn = B.front();			//�ķ�B�Ŀ�ͷ
			auto pA = A.begin(); pA++;
			//auto pB = B.begin(); pB++;
			for (; pA != A.end(); pA++)				
			{
				std::string &production = *pA;		//�ķ�A�еĲ���ʽ
				std::string item(production);
				std::string tmp;					//��ȡproduction�еķ��ս��
				for (char c:production)
				{
					if (c != ' ')
					{
						tmp.push_back(c);
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
								newprd.replace(0,Vn.length(), *pB);
								A.insert(pA, newprd);		//�����滻��Ĳ���ʽ
							}
							pA = A.begin(); 
							break;
						}
						//std::cout << tmp << std::endl;
						break;
					}
				}
			}
		}
		//ȥ��ֱ����ݹ�
		do
		{
			std::list<std::string>::iterator pA = A.begin();
			auto Vn = *pA;
			pA++;
			/*
			A -> A��| ��
			vs1�����vs2���
			*/
			std::vector<std::string> vs1, vs2;
			for (; pA != A.end(); pA++)
			{
				std::string &production = *pA;
				std::string first;				//ÿ������ʽ�ĵ�һ����ĸ�жϷָ������Ǧ�
				bool flag = true;
				for (char c : production)
				{
					if (c == ' ')
					{
						if (first == Vn)		//��A��
						{
							vs1.push_back(production.substr(Vn.length() + 1));
						}
						else					//�Ǧ�
						{
							vs2.push_back(production);
						}
						flag = false;			//�Ѿ��������ǰ����ʽ
						break;
					}
					else
					{
						first.push_back(c);
					}
				}
				if (flag) vs2.push_back(production);
			}
			if (vs1.empty()) continue;			//���ǿյģ�������ݹ�
			pA = A.begin(); pA++;
			/*
			��A -> A��| �¸�Ϊ
			A -> ��A1
			A1 -> ��A1
			*/
			while (pA != A.end()) pA = A.erase(pA);		//���A�Ĳ���ʽ
			//�����ֻ��empty��ֱ�Ӹ�Ϊ A -> ��A | empty
			if (vs2[0] == "empty")
			{
				for (std::string s : vs1)
				{
					A.push_back(s + ' ' + Vn);
				}
				A.push_back("empty");
				continue;
			}
			std::string newprdt(Vn + '1');				//���Ӳ���ʽ
			//��A1
			for (std::string s : vs2)
			{
				A.push_back(s + ' ' + newprdt);
			}
			//A1 -> ��A1
			std::list<std::string> newgrammar;
			newgrammar.push_back(newprdt);				//����A1
			for (std::string s : vs1)
			{
				newgrammar.push_back(s + ' ' + newprdt);
			}
			newgrammar.push_back("empty");
			p++;
			p = grammar.insert(p, newgrammar);
		} while (false);
		
	}
}

//��ȡFIRST����
void Parser::get_FIRST()
{
}

//��ȡFOLLOW����
void Parser::get_FOLLOW()
{
}

//�ж��ǲ���LL(1)�ķ�
bool Parser::judge_LL1_grammar()
{
	return false;
}

//����Ԥ�������
void Parser::get_predict_table()
{
}

//��ȡ������
void Parser::get_left_common_factor()
{
	//���������ķ�����
	for (auto p = grammar.begin(); p != grammar.end(); p++)
	{	
		auto &A = *p;
		if (A.size() == 2) continue;	//ֻ��һ������ʽ
		auto it = A.begin(); it++;
		std::string common_factor(*it);
		//�����ӵڶ�����ʼ��ÿ������ʽ
		for (; it != A.end(); it++)
		{
			const auto &production = *it;
			if (production == common_factor) continue;
			bool flag = false;			//���޹�����
			for (int i = production.length() - 1; i >= 0; i--)
			{
				//���ո񣬱Ƚ�ǰ��Ĳ���ʽ������ȡ�Ĺ�����
				if (production[i] == ' ')
				{
					std::string prefix_production = production.substr(0, i);
					//�������ӽ�ȡΪ�͵�ǰ�Ӵ�������ͬ
					common_factor = common_factor.substr(0, i);
					//ǰ׺������ȡ�Ĺ�������ͬ���Ƚ���һ������ʽ
					if (common_factor == prefix_production)
					{
						flag = true;
						break;
					}
					else continue;
				}
			}
			//û�й�����
			if (!flag)
			{
				common_factor.clear();
				break;
			}
		}
		/*
		�й�����
		��A -> ��B | ��C ת��Ϊ
		A -> ��A_2
		A_2 -> B | C
		*/
		if (common_factor.length())
		{
			//��ȡ�����������������ʽ
			std::vector<std::string> left_factor;
			it = A.begin(); it++;
			for (; it != A.end(); it++)
			{
				if (it->length() == common_factor.length())
				{
					left_factor.push_back("empty");
				}
				else
				{
					std::string left_production = it->substr(common_factor.length() + 1);		//+1�̿ո�
					left_factor.push_back(left_production);
				}
				
			}			
			std::list<std::string> newgrammar;
			std::string Vn = *A.begin();
			std::string newVn(Vn + "_2");
			newgrammar.push_back(Vn);
			newgrammar.push_back(common_factor + ' ' + newVn);
			p = grammar.erase(p);
			//��A -> ��A_2�����ķ��б�
			grammar.insert(p, newgrammar);
			newgrammar.clear();
			newgrammar.push_back(newVn);
			for (auto factor : left_factor)
			{
				newgrammar.push_back(factor);
			}
			//��A_2 -> B | C�����ķ��б�
			p = grammar.insert(p, newgrammar);
		}
	}
}

//���ϻ�ȡ��һ��token�����﷨��
std::string Parser::get_next_token()
{
	return std::string();
}
