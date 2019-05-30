//���ߣ�IuSpet
//���ã���c-Դ����ת��Ϊtoken���

#include "scanner.h"


void Scanner::GetToken()
{
	char ch;
	constexpr int TOKENLENGTH = 256;
	char token[TOKENLENGTH];
	memset(token, 0, TOKENLENGTH);
	int tokenpos = 0;
	std::ofstream outfile("D://cminus//token.txt");
	while ((ch = GetNext()) != EOF)
	{
		//todo: ��ʶ�����ؼ��֣����ͣ��������������ע�ͣ�������ַ�����dfa
		while (state != 100)
			switch (state)
			{
			case 0:									//��ʼ״̬
				if (ch == '+') state = 1;
				else if (ch == '-') state = 2;
				else if (ch == '*') state = 3;
				else if (ch == '/') state = 4;
				else if (ch == '<') state = 5;
				else if (ch == '>') state = 6;
				else if (ch == '=') state = 7;
				else if (ch == ';') state = 8;
				else if (ch == '!') state = 9;
				else if (ch == '[') state = 10;
				else if (ch == ']') state = 11;
				else if (ch == '(') state = 12;
				else if (ch == ')') state = 13;
				else if (ch == '{') state = 14;
				else if (ch == '}') state = 15;
				else if (ch == '"') state = 16;
				else if (ch == ',')state = 17;
				else if (IsLetter(ch)) state = 18;
				else if (IsNum(ch)) state = 19;
				else if (ch == ' ' || ch == '\t' || ch == '\n') state = 100;
				else state = 99;			//�쳣
				break;
			case 1:									//ƥ�䵽 +
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsNum(ch)) state = 19;
				else
				{
					Back();
					syn = 8;
					state = 100;
				}				
				break;
			case 2:									//ƥ�䵽 -
				token[tokenpos++] = ch;
				syn = 9;
				state = 100;
				break;
			case 3:									//ƥ�䵽 *
				token[tokenpos++] = ch;
				syn = 10;
				state = 100;
				break;
			case 4:									//ƥ�䵽 /
				token[tokenpos++] = ch;
				ch = GetNext();
				if (ch == '/') state = 20;
				else if (ch == '*') state = 21;
				else
				{
					Back();
					state = 100;
					syn = 11;
				}
				break;
			case 20:								//ƥ�䵽 //
				while ((ch = GetNext()) != '\n');
				syn = 31;
				state = 100;
				break;
			case 21:								// ƥ�䵽 /*
				ch = GetNext();
				if (ch == '*') state = 22;
				else state = 21;
				break;
			case 22:								//ƥ�䵽 /**
				ch = GetNext();
				if (ch == '*') state = 22;
				else if (ch == '/')state = 23;
				else state = 21;
				break;
			case 23:								//ƥ�䵽 /**/
				state = 100;
				syn = 32;
				break;
			case 5:									//ƥ�䵽 <
				token[tokenpos++] = ch;
				ch = GetNext();
				if (ch == '=') state = 24;
				else
				{
					Back();;
					state = 100;
					syn = 12;
				}
				break;
			case 24:								//ƥ�䵽 <=
				token[tokenpos++] = ch;
				state = 100;
				syn = 23;
				break;
			case 6:									//ƥ�䵽 >
				token[tokenpos++] = ch;
				ch = GetNext();
				if (ch == '=') state = 25;
				else
				{
					Back();
					state = 100;
					syn = 13;
				}
				break;
			case 25:								//ƥ�䵽 >=
				token[tokenpos++] = ch;
				state = 100;
				syn = 24;
				break;
			case 7:									//ƥ�䵽 =
				token[tokenpos++] = ch;
				ch = GetNext();
				if (ch == '=') state = 26;
				else
				{
					Back();
					state = 100;
					syn = 14;
				}
				break;
			case 26:								//ƥ�䵽 ==
				token[tokenpos++] = ch;
				state = 100;
				syn = 25;
				break;
			case 8:									//ƥ�䵽 ��
				token[tokenpos++] = ch;
				state = 100;
				syn = 15;
				break;
			case 9:									//ƥ�䵽 !
				token[tokenpos++] = ch;
				ch = GetNext();
				if (ch == '=') state = 27;
				else state = 99;
				break;
			case 27:								//ƥ�䵽 !=
				token[tokenpos++] = ch;
				state = 100;
				syn = 26;
				break;
			case 10:									//ƥ�䵽 [
				token[tokenpos++] = ch;
				state = 100;
				syn = 17;
				break;
			case 11:									//ƥ�䵽 ]
				token[tokenpos++] = ch;
				state = 100;
				syn = 18;
				break;
			case 12:									//ƥ�䵽 (
				token[tokenpos++] = ch;
				state = 100;
				syn = 19;
				break;
			case 13:									//ƥ�䵽 )
				token[tokenpos++] = ch;
				state = 100;
				syn = 20;
				break;
			case 14:									//ƥ�䵽 {
				token[tokenpos++] = ch;
				state = 100;
				syn = 21;
				break;
			case 15:									//ƥ�䵽 }
				token[tokenpos++] = ch;
				state = 100;
				syn = 22;
				break;
			case 16:									//ƥ�䵽 "����
				token[tokenpos++] = ch;
				ch = GetNext();
				if (ch == '"') state = 28;
				else state = 16;
				break;
			case 28:									//ƥ�䵽 "����"
				token[tokenpos++] = ch;
				state = 100;
				syn = 30;
				break;
			case 17:									//ƥ�䵽 ,
				token[tokenpos++] = ch;
				state = 100;
				syn = 16;
				break;
			case 18:									//ƥ�䵽��ĸ
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsLetter(ch) || IsNum(ch)) state = 18;	//��ǰ��һλ�������ֻ���ĸ
				else
				{
					Back();
					state = 29;							//��ǰ��һλ�����ڱ�ʶ��
				}
				break;
			case 29:									//�ж�ƥ�䵽�ı�ʶ���ǲ��ǹؼ���
				if (strcmp(token, "if") == 0)
				{
					state = 100;
					syn = 0;
				}
				else if (strcmp(token, "else") == 0)
				{
					state = 100;
					syn = 1;
				}
				else if (strcmp(token, "int") == 0)
				{
					state = 100;
					syn = 2;
				}
				else if (strcmp(token, "double") == 0)
				{
					state = 100;
					syn = 3;
				}
				else if (strcmp(token, "return") == 0)
				{
					state = 100;
					syn = 4;
				}
				else if (strcmp(token, "void") == 0)
				{
					state = 100;
					syn = 5;
				}
				else if (strcmp(token, "while") == 0)
				{
					state = 100;
					syn = 6;
				}
				else if (strcmp(token, "char") == 0)
				{
					state = 100;
					syn = 7;
				}
				else
				{
					state = 100;
					syn = 27;
				}
				break;
			case 19:									//ƥ�䵽��������
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsNum(ch)) state = 19;				//��һλ��������
				else if (ch == '.') state = 30;			//��һλ��.
				else
				{
					Back();
					state = 100;
					syn = 28;
				}
				break;
			case 30:									//ƥ�䵽 digit D* .
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsNum(ch)) state = 30;
				else if (ch == 'e') state = 31;
				else
				{
					Back();
					state = 100;
					syn = 29;
				}
				break;
			case 31:									//ƥ�䵽 digit D* . D* e
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsNum(ch)) state = 32;
				else if (ch == '-')state = 33;
				else
				{
					Back();
					state = 99;
				}
				break;
			case 32:									//ƥ�䵽 digit D* . D* e
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsNum(ch)) state = 32;
				else
				{
					Back();
					state = 100;
					syn = 29;
				}
				break;
			case 33:									//ƥ�䵽 digit D* . D* e -
				token[tokenpos++] = ch;
				ch = GetNext();
				if (IsNum(ch)) state = 32;
				else
				{
					Back();
					state = 99;
				}
				break;
			case 99:									//ƥ���г���
				std::cout << std::endl;
				std::cout << "error" << std::endl;
				std::cout << (int)ch << " " << ch << std::endl;
				ch = GetNext();
				while (ch != ' '&&ch != '\t'&&ch != '\n'&&ch != ';') ch = GetNext();
				Back();
				state = 100;
				syn = -1;
			}
		if (state == 100 && syn != -1)					//����״̬
		{
			switch (syn)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				outfile << "<" << "RESERVED WORD," << token << ">" << std::endl;
				//outfile << "<" << token << ">" << std::endl;
				break;
			case 27:
				outfile << "<" << "ID," << token << ">" << std::endl;
				break;
			case 28:
				outfile << "<" << "NUM," << token << ">" << std::endl;
				break;
			case 29:
				outfile << "<" << "DOUBLE," << token << ">" << std::endl;
				break;
			case 30:
				outfile << "<" << "STRING," << token << ">" << std::endl;
				break;
			case 31:
			case 32:
				break;
			default:
				outfile << "<" << "SYMBOL," << token << ">" << std::endl;
				//outfile << "<" << token << ">" << std::endl;
			}
			memset(token, 0, TOKENLENGTH);
			tokenpos = 0;
			state = 0;
			syn = -1;
		}
		if (state = 100) state = 0;
	}
	outfile.close();
}

bool Scanner::IsNum(const char c)
{
	return (c >= '0' && c <= '9');
}

bool Scanner::IsLetter(const char c)
{
	return c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z';
}

/*char Scanner::GetNext()
{
	if (buffer[pos] == 0)
	{
		if (fgets(buffer, BUFFERLENGTH, source) != NULL);
		else return EOF;
		pos = 0;
	}
	return buffer[pos++];
}*/
char Scanner::GetNext()
{
	std::ifstream infile(sourcename);
	infile.seekg(filepos, std::ios::beg);
	if (pos < buffer.length())
	{
		return buffer[pos++];
	}
	else
	{
		if (std::getline(infile, buffer))
		{
			buffer.push_back('\n');
		}
		else
		{
			return EOF;
		}
		filepos += buffer.length() + 2;
		pos = 0;
		return buffer[pos++];
	}
	infile.close();
}

void Scanner::Back()
{
	pos -= 1;
}
