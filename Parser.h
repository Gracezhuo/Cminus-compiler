//���ߣ�IuSpet
//���ã���һ���ķ�ת��ΪLL(1)�ķ��������﷨������

#ifndef Parser_h
#define Parser_h
#include"utlib.h"

//�﷨���Ľڵ�
struct node
{
	node *Parent;
	std::string type;
	std::string value;
	std::list<node*> sons;
};
class Parser
{
public:
	Parser();
	
	void get_LL1_grammar();						//�õ�LL��1���ķ�
	void Parse();								//������ƥ���ķ���token������		
	
private:
	std::list<std::list<std::string>> grammar;		//�ķ�	
	std::vector<std::vector<std::vector<std::string>>> final_grammar;	//������LL(1)�ķ�
	std::map<std::string, bool> can_produce_empty;
	std::map<std::string, bool> is_Vn;
	std::map<std::string, std::set<std::string>> FIRST, FOLLOW;
	//Ԥ�������,�ṹΪ		predictive_table[���ս���ţ��ս����] = ����ʽ
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> predictive_table;		
	const char *grammar_file;
	const char *token_file;
	FILE* f;
	int filepos;
	node root;										//�﷨����


	void get_grammar();								//��ȡ��ʼ�ķ�
	void Eliminate_left_recursion();				//������ݹ�
	void get_FIRST();								//��ȡFIRST����
	void get_FOLLOW();								//��ȡFOLLOW����
	bool judge_LL1_grammar();						//�ж��ǲ���LL(1)�ķ�
	bool cmp_set(const std::set<std::string> s1, const std::set<std::string> s2);	//�ж�����set�Ƿ��н���
	void get_predict_table();						//����Ԥ�������
	void get_left_common_factor();					//��ȡ������
	void get_all_Vn();								//�ҳ����з��ս��
	void reconsitution();							//������������ݽṹ������
	std::string get_next_token();					//���ϻ����һ��token
	void print_grammar0();							//��ӡ��ʼ�ķ�
	void print_grammar1();							//��ӡȥ����ݹ����ķ�
	void print_grammar2();							//��ӡ��ȡ�����Ӻ���ķ�
	void print_final_grammar();						//��ӡ�ع�����ķ�������
	std::set<std::string> cal_first(std::string Vn);//���ڵݹ����FIRST��
	void print_FIRST();								//��ӡFIRST����
	void print_FOLLOW();							//��ӡFOLLOW����
	void print_predictive_table();					//��ӡԤ�������
	void print_tree();								//��ӡ�﷨��
	void string_to_vector(std::string &s, std::vector<std::string> &v);		//��string��ʾ�Ĳ���ʽתΪvector
	void vector_to_string(std::string &s, std::vector<std::string> &v);		//��vector��ʾ�Ĳ���ʽתΪstring
	bool has_common_prefix(std::vector<std::string> &gm1, std::vector<std::string> &gm2);	//�ж���������ʽ����������
	std::set<std::string> get_left(std::vector<std::string> & tmp);		//������ˣ���first�������ڲ鿴�Ƿ���������
	void get_token_value(std::string &token, std::string &value, std::string &type);		//��ȡtoken����
	void deep_print(std::ofstream &out, int r, node *t);				//�ݹ��ӡ��
};
#endif // !Parser_h
#pragma once
