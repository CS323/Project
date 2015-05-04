#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.cpp"

class Parser
{
public:
	static std::string s;
    std::string a = "filename.txt";
	Lexer lexer;
	Parser()
	{
		lexer.setFile(a);
		lexer.getTokLex();//get first tok/lex
	}
	void Program()
	{
		if(lexer.lexeme == "PROGRAM")
		{
			lexer.getTokLex();
            std::cout << "PROGRAM ";
            if (lexer.token == "identifier"){
                std::cout << lexer.lexeme;
                while (lexer.lexeme != ";"){
                    lexer.getTokLex();
                    std::cout << lexer.lexeme;
                }
                std::cout << std::endl;
                lexer.getTokLex();
                if (lexer.lexeme == "VAR"){
                    std::cout << lexer.lexeme;
                    std::cout << std::endl;
                    lexer.getTokLex();
                    while (lexer.lexeme != ";"){
                        if (lexer.token == "identifier"){
                            std::cout<<lexer.lexeme;
                            lexer.getTokLex();
                        } else if(lexer.lexeme == ","){
                            std::cout<<lexer.lexeme << " ";
                            lexer.getTokLex();
                        }else if (lexer.lexeme == ":"){
                            std::cout<< " " <<lexer.lexeme << " ";
                            lexer.getTokLex();
                        }else if(lexer.lexeme == "INTEGER"){
                            std:: cout <<lexer.lexeme;
                            lexer.getTokLex();
                        }
                    }
                    std::cout << lexer.lexeme;
                    lexer.getTokLex();
                        if(lexer.lexeme == "BEGIN")
                        {
                            lexer.getTokLex();
                            if(lexer.lexeme == "END")
                            {
                                
                            }
                            else{std::cout << "Expected 'END'"; exit(0);}
                        }
                }
            }else {
                std::cout << "missing program name";
            }
		}
		else{ std::cout << "Expected 'PROGRAM'"; exit(0); }
	}
    
    void pName(){
        
    }
    
    void id(){
        
    }
    
    void decList(){
        
    }
    
    void dec(){
        
    }
    
    void statList() {
        
    }
    
    void stat() {
        
    }
    
    void print() {
        
    }
    
    void output() {
        
    }
    
    void assign() {
        
    }
    
    void expr() {
        
    }
    
    void term() {
        
    }
    
    void factor() {
        
    }
    
    void number() {
        
    }
    
    void type() {
        
    }
    
    void digit() {
        
    }
    
    void letter() {
        
    }
    
    
};
