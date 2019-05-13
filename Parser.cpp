#include "Parser.h"
#include<assert.h>
const int BUFFERLENGTH = 4096;

//���캯��ָ���ķ��ļ���token�ļ�
Parser::Parser()
{
	grammar_file = "D://cminus//grammar.txt";
	token_file = "D://cminus//token.txt";
}

void Parser::get_LL1_grammar()
{
	get_grammar();
	Eliminate_left_recursion();
	get_left_common_factor();
	get_all_Vn();
	mark_empty();
	reconsitution();
	get_FIRST();
	get_FOLLOW();
	if (!judge_LL1_grammar())
	{
		std::cout << "����LL(1)�ķ�" << std::endl;
		system("pause");
	}
	else
	{
		std::cout << "��LL(1)�ķ�" << std::endl;
		system("pause");
	}
}

//����token�������﷨��
void Parser::Parse()
{
}

void Parser::test_print()
{
	print_grammar0();
	print_grammar1();
	print_grammar2();
	print_empty();
	print_final_grammar();
	print_FIRST();
	print_FOLLOW();
}

//��ӡ���ļ��ж�ȡ���ķ�
void Parser::print_grammar0()
{
	std::ofstream outfile("D://cminus//grammar0.txt");
	for (const auto &l : grammar)
	{
		bool first = true;
		for (const auto &t : l)
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

//��ӡȥ����ݹ����ķ�
void Parser::print_grammar1()
{
	std::ofstream outfile("D://cminus//grammar1.txt");
	for (const auto &l : grammar)
	{
		bool first = true;
		for (const auto &t : l)
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

//��ӡ��ȡ�����Ӻ���ķ�
void Parser::print_grammar2()
{
	std::ofstream outfile("D://cminus//grammar2.txt");

	for (const auto &l : grammar)
	{
		bool first = true;
		for (const auto &t : l)
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

void Parser::print_final_grammar()
{
	std::ofstream outfile("D://cminus//ll(1)grammar.txt");
	for (auto &gm : final_grammar)
	{
		outfile << gm[0][0] << " -> ";
		for (int i = 1; i < gm.size(); i++)
		{
			for (int j = 0; j < gm[i].size(); j++)
			{
				outfile << gm[i][j] << " ";
			}
			outfile << "| ";
		}
		outfile << std::endl << std::endl;
	}
	outfile.close();
}

//��ӡ�ܲ���empty���ķ�
void Parser::print_empty()
{
	std::ofstream outfile("D://cminus//empty.txt");
	for (const auto &gm : grammar)
	{
		const std::string &Vn = *gm.begin();
		if (can_produce_empty[Vn]) outfile << Vn << std::endl;
		else continue;
	}
	outfile.close();
}

//��ӡ�����ķ���FIRST����
void Parser::print_FIRST()
{
	std::ofstream outfile("D://cminus//FIRST.txt");
	for (const auto &gm : final_grammar)
	{
		outfile << gm[0][0] << " : { ";
		for (const auto &str : FIRST[gm[0][0]])
		{
			outfile << str << "| ";
		}
		outfile << "}"<<std::endl << std::endl;
	}
	outfile.close();
}

void Parser::print_FOLLOW()
{
	std::ofstream outfile("D://cminus//FOLLOW.txt");
	for (const auto &gm : final_grammar)
	{
		const auto &Vn = gm[0][0];
		outfile << Vn << " :{ ";
		for (auto &str : FOLLOW[Vn])
		{
			outfile << str << " | ";
		}
		outfile << "}" << std::endl << std::endl;
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
			std::string newprdt(Vn + "_1");				//���Ӳ���ʽ
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
	for (auto &gm : final_grammar)
	{
		std::string &Vn = gm[0][0];
		if (FIRST[Vn].empty())
		{
			FIRST[Vn] = cal_first(Vn);
		}
	}
}

//�ݹ���㵱ǰ���ս����fist����
std::set<std::string> Parser::cal_first(std::string Vn)
{
	std::set<std::string> res;
	for (auto &gm : final_grammar)
	{
		if (gm[0][0] == Vn)
		{
			//ÿ������ʽ��FIRST����
			for (int j = 1; j < gm.size(); j++)
			{
				auto &pro = gm[j];
				//��ÿ������ʽ�ĵ�һ�����ս����ʼ����FISRST�����������empty���ټ�����һ���������һ��Ҳ��empty����empty����FIRST����
				for (int i = 0; i < pro.size(); i++)
				{
					//�ж��ǲ��Ƿ��ս��
					if (is_Vn[pro[i]])
					{
						FIRST[pro[i]] = cal_first(pro[i]);
						res.insert(FIRST[pro[i]].begin(), FIRST[pro[i]].end());
						if (FIRST[pro[i]].find("empty") != FIRST[pro[i]].end())
						{
							if (i == pro.size() - 1)
							{
								res.insert("empty");
								break;
							}
							else continue;
						}
						else break;
					}
					else
					{
						if (pro[i] != "empty")
						{
							res.insert(pro[i]);
						}
						//����ʽֻ��һ��empty�����
						else if (i == 0)
						{
							res.insert("empty");
						}
						break;
					}
				}
			}
			break;
		}
	}
	return res;
}

//��ȡFOLLOW����
void Parser::get_FOLLOW()
{
	FOLLOW[final_grammar[0][0][0]].insert("$");
	int t = final_grammar.size();
	while (t--)
	{
		for (auto &gm : final_grammar)
		{
			/*
			����ÿ���ķ����򣬲���Ѱ��A -> ��B�½ṹ��
			��FIRST(��)�г�empty������з��ż���FOLLOW(B)
			*/
			auto p = gm.begin(); p++;
			for (; p != gm.end(); p++)
			{
				auto &pro = *p;
				/*
				��Ǹ÷��ź���Ĳ����ܷ����empty
				�Ӷ��ж��Ƿ�Ӧ�ù��򣺶���A -> ��B��
				��FOLLOW(A)�еķ��ż���FOLLOW(B)��
				flagΪtrueʱ��Ӧ�ã�falseʱ�ǲ�Ӧ��
				*/
				bool flag = true;
				//�Ӻ���ǰ�ж�ÿ���ķ������ܲ���emptyʱ��flag��Ϊfalse
				for (int i = pro.size() - 1; i >= 0; i--)
				{
					//�ж��Ƿ��Ƿ��ս��
					if (is_Vn[pro[i]])
					{
						//����벿��first����follow
						for (int j = i + 1; j < pro.size(); j++)
						{
							if (is_Vn[pro[j]])
							{
								FOLLOW[pro[i]].insert(FIRST[pro[j]].begin(), FIRST[pro[j]].end());
								if (FIRST[pro[j]].find("empty") == FIRST[pro[j]].end()) break;
							}
							else
							{
								FOLLOW[pro[i]].insert(pro[j]);
								break;
							}
						}
						if (flag)
						{
							//��Ϊgm[0][0]��follow���Ͽ��ܲ�ȫ������Ҫ�������øú�����ȫ��������
							FOLLOW[pro[i]].insert(FOLLOW[gm[0][0]].begin(), FOLLOW[gm[0][0]].end());
							if (FIRST[pro[i]].find("empty") == FIRST[pro[i]].end()) flag = false;
						}
					}
				}
			}
		}
	}
	//FOLLOW����û��empty
	for (auto &gm : final_grammar)
	{
		auto &Vn = gm[0][0];
		auto p = FOLLOW[Vn].find("empty");
		if (p != FOLLOW[Vn].end()) FOLLOW[Vn].erase(p);
	}
}

//�ж��ǲ���LL(1)�ķ�
bool Parser::judge_LL1_grammar()
{
	bool res = true;
	for (auto &gm : final_grammar)
	{
		auto &Vn = gm[0][0];
		bool flag = false;
		//first(Vn)����empty����Ҫ�Ƚ�follow(Vn)��first(A)��A��first����û��empty�Ĳ���ʽ
		if (FIRST[Vn].find("empty") != FIRST[Vn].end())
		{
			flag = true;
		}
		for (int i = 1; i < gm.size(); i++)
		{
			std::set<std::string> s1;
			for (auto &v : gm[i])
			{
				if (is_Vn[v])
				{
					s1.insert(FIRST[v].begin(), FIRST[v].end());
					if (FIRST[v].find("empty") == FIRST[v].end()) break;
				}
				else
				{
					s1.insert(v);
					break;
				}
			}
			if (flag && s1.find("empty") != s1.end()) res &= cmp_set(s1, FOLLOW[Vn]);
			for (int j = i + 1; j < gm.size(); j++)
			{
				std::set<std::string> s2;
				for (auto &v : gm[j])
				{
					if (is_Vn[v])
					{
						s2.insert(FIRST[v].begin(), FIRST[v].end());
						if (FIRST[v].find("empty") == FIRST[v].end()) break;
					}
					else
					{
						s2.insert(v);
						break;
					}
				}
				res &= cmp_set(s1, s2);
			}
		}
	}
	return res;
}

bool Parser::cmp_set(const std::set<std::string> s1, const std::set<std::string> s2)
{
	int l1 = s1.size();
	int l2 = s2.size();
	std::set<std::string> s;
	s.insert(s1.begin(), s1.end());
	s.insert(s2.begin(), s2.end());
	int l = s.size();
	if (l1 + l2 != l) {
		std::cout << "error" << std::endl;
	}
	return (l1 + l2) == l;
}

//����Ԥ�������
void Parser::get_predict_table()
{
}

//��ȡ������
void Parser::get_left_common_factor()
{
	
}

//������з��ս�����ս��
void Parser::get_all_Vn()
{
	//��map�м��������ս������ս��
	for (auto gm : grammar)
	{
		for (auto V : gm)
		{
			is_Vn[V] = false;
		}
	}
	//�����ս�����Ϊtrue
	for (auto gm : grammar)
	{
		is_Vn[*gm.begin()] = true;
	}
}

//����ܲ���empty���ķ�
void Parser::mark_empty()
{
	for (auto &gm : grammar)
	{
		auto it = gm.begin();
		auto &Vn = *it;
		it++;
		can_produce_empty[Vn] = false;
		for (; it != gm.end(); it++)
		{
			if (*it == "empty")
			{
				can_produce_empty[Vn] = true;
				break;
			}
		}
	}
}

//�ķ����ٸı䣬�������ݽṹ���������ʹ��
void Parser::reconsitution()
{
	std::vector<std::vector<std::string>> tmp;
	for (auto &gm : grammar)
	{
		tmp.clear();
		std::vector<std::string> vs;
		for (auto &pro : gm)
		{
			vs.clear();
			std::string sub;
			for (auto &c : pro)
			{
				if (c == ' ')
				{
					vs.push_back(sub);
					sub.clear();
				}
				else
				{
					sub.push_back(c);
				}
			}
			vs.push_back(sub);
			tmp.push_back(vs);
		}
		final_grammar.push_back(tmp);
	}
	//grammar.clear();
}


//���ϻ�ȡ��һ��token�����﷨��
std::string Parser::get_next_token()
{
	return std::string();
}
