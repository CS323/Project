#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.cpp"
#include <list>

class Parser
{
public:
	static std::string s;
    std::string a = "filename.txt";
    std::list<std::string>lines;
    std::string tempString = "";
    std::string cppFile = "";
	Lexer lexer;
	Parser()
	{
		lexer.setFile(a);
		lexer.getTokLex();//get first tok/lex
        //Start making the cpp file
        lines.push_back("#include <iostream>");
        lines.push_back("using namespace std;");
	}
    
	void Program()
	{
		if(lexer.lexeme == "PROGRAM")
		{
            lines.push_back("int main(){");
			lexer.getTokLex();
            if (pName()){
                lexer.getTokLex();
                if (lexer.lexeme == "VAR"){
                    decList();
                    if (lexer.lexeme == ";"){
                        lexer.getTokLex();
                    }else{
                        std::cout << "Missing ';'";
                    }
                        if(lexer.lexeme == "BEGIN")
                        {
                            lexer.getTokLex();
                            while (lexer.lexeme != "END") {
                                statList();
                                lexer.getTokLex();
                            }
                            if(lexer.lexeme == "END")
                            {
                                lines.push_back("return 0;");
                                lexer.getTokLex();
                                if (lexer.lexeme == "."){
                                    lines.push_back("}");
                                    std::list<std::string>::iterator it;
                                    std::ofstream myfile (cppFile);
                                    for(it = lines.begin(); it !=lines.end(); it++ ){
                                        if(myfile.is_open()){
                                            myfile << *it << std::endl;
                                        } else{
                                            std::cout << "Unable to open file";
                                        }
                                    }
                                    myfile.close();
                                    
                                }else{
                                    std::cout<< "Missing '.'";
                                }
                                
                            }
                            else{std::cout << "Expected 'END'"; exit(0);}
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
            cppFile = lexer.lexeme + ".cpp";
        while (lexer.lexeme != ";"){
            lexer.getTokLex();
        }
            return true;
        }else{
            return false;
        }
    }
    
    void decList(){
        lexer.getTokLex();
        while (lexer.lexeme != ":"){
            dec();
            lexer.getTokLex();
        }
        lexer.getTokLex();
        if (type()){
            lexer.getTokLex();
        }else {
            std::cout<<"Missing Type";
        }
    }
    
    void dec(){
        if (lexer.token == "identifier"){
            tempString = tempString + lexer.lexeme;
        } else if(lexer.lexeme == ","){
            tempString = tempString + lexer.lexeme;
        }
    }
    
    void statList() {
        stat();
    }
    
    void stat() {
        if (lexer.token == "identifier"){
            assign();
        } else if (lexer.lexeme == "PRINT"){
            print();
        }
        
    }
    
    void print() {
        tempString = "";
        tempString = tempString + "cout ";
        lexer.getTokLex();
        if (lexer.lexeme == "("){
            tempString = tempString + "<< ";
            lexer.getTokLex();
            output();
        }else {
            std::cout << "Missing '('";
        }
        lexer.getTokLex();
        if (lexer.lexeme == ";"){
            tempString = tempString + lexer.lexeme;
            lines.push_back(tempString);
        }else{
            std::cout << "Missing ';'";
        }
    }
    
    void output() {
        tempString = tempString + lexer.lexeme;
        lexer.getTokLex();
        while (lexer.lexeme != ")") {
            if (lexer.lexeme == ","){
                tempString = tempString + " << ";
            }else{
                tempString = tempString + lexer.lexeme;
            }
            lexer.getTokLex();
        }
    }
    
    void assign() {
        tempString = "";
        tempString = tempString + lexer.lexeme;
        lexer.getTokLex();
        if (lexer.lexeme == "="){
            tempString = tempString + " " + lexer.lexeme + " ";
            lexer.getTokLex();
            expr();
        }else{
            std::cout << "Missing '='";
        }
    }
    
    void expr() {
        std::string temp = lexer.lexeme;
        lexer.getTokLex();
        if (lexer.lexeme == ";") {
            tempString = tempString + temp + lexer.lexeme;
            lines.push_back(tempString);
        } else if (lexer.token == "operator"){
            tempString = tempString + temp + " " + lexer.lexeme + " ";
            term();
        }
    }
    
    void term() {
        lexer.getTokLex();
        expr();
    }
    
    void factor(std::string temp) {
        if (temp == "identifier"){
            tempString = tempString + temp + lexer.lexeme;
        }else if (temp == "int"){
            tempString = tempString + temp + lexer.lexeme;
        }else if (temp == "<"){
            tempString = tempString + temp;
            expr();
        }
    }
    
    bool type() {
        if(lexer.lexeme == "INTEGER"){
            lines.push_back("int " + tempString + ";");
            return true;
        }else {
            std::cout << " missing type " << std::endl;
            return false;
        }
        
    }
    
};
