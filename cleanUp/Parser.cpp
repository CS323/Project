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
            if (pName()){
                std::cout << std::endl;
                lexer.getTokLex();
                if (lexer.lexeme == "VAR"){
                    std::cout << "VAR";
                    std::cout << std::endl;
                    if (decList()) {
                        if(lexer.lexeme == "BEGIN")
                        {
                            statList();
                            if(lexer.lexeme == "END")
                            {
                                if (lexer.lexeme == "."){
                                    std::cout << "end of program";
                                }else{
                                    std::cout<< "Missing '.'";
                                }
                                
                            }
                            else{std::cout << "Expected 'END'"; exit(0);}
                        }
                    }else{
                        std::cout << "Expected Variables";
                    }
                }
            }else {
                std::cout << "Missing program name";
            }
		}
		else{ std::cout << "Expected 'PROGRAM'"; exit(0); }
	}
    
    bool pName(){
        if (lexer.token == "identifier"){
        std::cout << lexer.lexeme;
        while (lexer.lexeme != ";"){
            lexer.getTokLex();
            std::cout << lexer.lexeme;
        }
            return true;
        }else{
            return false;
        }
    }
    
    bool decList(){
        lexer.getTokLex();
        while (lexer.lexeme != ":"){
            dec();
            lexer.getTokLex();
        }
        std::cout << " " << lexer.lexeme << " ";
        lexer.getTokLex();
        if (type()){
            return true;
        }else {
            return false;
        }
    }
    
    void dec(){
            if (lexer.token == "identifier"){
                std::cout<<lexer.lexeme;
            } else if(lexer.lexeme == ","){
                std::cout<<lexer.lexeme << " ";
            }
    }
    
    void statList() {
        while (lexer.lexeme != "END") {
            lexer.getTokLex();
            stat();
        }
    }
    
    void stat() {
        if (lexer.token == "identifier"){
            assign();
        }else if (lexer.lexeme == "PRINT"){
            print();
        }
    }
    
    void print() {
        std::cout << "PRINT";
        while(lexer.lexeme != ";"){
            output();
            lexer.getTokLex();
        }
    }
    
    void output() {
        std::cout<<lexer.lexeme;
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
    
    bool type() {
        if(lexer.lexeme == "INTEGER"){
            std:: cout <<lexer.lexeme;
            lexer.getTokLex();
            if (lexer.lexeme == ";") {
                std::cout<<lexer.lexeme;
                std::cout << std::endl;
                return true;
            }else{
                std::cout<<"Missing ';'";
                return false;
            }
        }else {
            std::cout << " missing type " << std::endl;
            return false;
        }
        
    }
    
};
