#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Lexer
{
public:
	std::ifstream fin;
	std::string lexeme;
	std::string token;
	std::vector<std::string> keywords;
	char ch;
	char *trash;

	Lexer()
	{
		ch = ' ';
		keywords.push_back("INTEGER");
		keywords.push_back("PRINT");
		keywords.push_back("PROGRAM");
		keywords.push_back("BEGIN");
		keywords.push_back("END");
		keywords.push_back("VAR");
	}
	Lexer(std::string filename)
	{
		fin.open(filename);
		ch = ' ';
		keywords.push_back("INTEGER");
		keywords.push_back("PRINT");
		keywords.push_back("PROGRAM");
		keywords.push_back("BEGIN");
		keywords.push_back("END");
		keywords.push_back("VAR");
		
	}


	void readChar()
	{
		while(ch )
		{
			std::cout << ch;
		}
	}

	void setFile(std::string s)
	{
		ch = ' ';
		fin.open(s);
	}

	void getTokLex()
	{
		lexeme = token = "";
		while(isspace(ch))
		{
			fin.get(ch);
		}
		if(isalpha(ch))
		{
			lexeme = lexeme + ch;
			fin.get(ch);
			while(isalnum(ch) || ch == '_')
			{
				lexeme = lexeme + ch;
				fin.get(ch);
			}
			fin.unget();
			fin.unget();
			fin.get(ch);
			if(!isalnum(ch))
			{
				token = "invalid identifier";
				fin.get(ch);
			}
			else
			{
				fin.get(ch);
                if(std::find(keywords.begin(),keywords.end(),lexeme) != keywords.end()){
					token = "keyword";
                } else{
                    token = "identifier";
                }
				//if lexeme in keywordlist token = keyword
				//else token = identifier
			}
		}
		else if(isdigit(ch))
		{
			while(isdigit(ch))
			{
				lexeme = lexeme + ch;
				fin.get(ch);
			}
			if (ch == '.' && isdigit(fin.peek()))
			{
				lexeme = lexeme + ch;
				fin.get(ch);
				while(isdigit(ch))
				{
					lexeme = lexeme + ch;
					fin.get(ch);
				}
				token = "real";
			}
			else token = "int";
		}
		else if(ch == '+' || ch == '-' || ch == '*' || ch == '=' || ch == ';' ||
			ch == ':' || ch == ',' || ch == '(' || ch == ')' || ch == '.' || ch == '!')
		{
			lexeme = lexeme + ch;
			token = "operator";
			fin.get(ch);
		}
		else if(ch == '<')
		{
			lexeme = lexeme + ch;
			if (fin.peek() == '-' || fin.peek() == '=' || fin.peek() == '>')
			{
				fin.get(ch);
				lexeme = lexeme + ch;
			}
			fin.get(ch);
			token = "operator";
		}
		else if(ch == '>')
		{
			lexeme = lexeme + ch;
			if (fin.peek() == '=')
			{
				fin.get(ch);
				lexeme = lexeme + ch;
			}
			fin.get(ch);
			token = "operator";
		}
		else if(ch == '/')
		{
			lexeme = lexeme + ch;
			if (fin.peek() == '/')
			{
				fin.get(ch);
				while(ch!='\n')
					fin.get(ch);
				getTokLex();
			}
			else token = "operator";
			fin.get(ch);
		}
	}
};

