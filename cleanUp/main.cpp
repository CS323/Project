//
//  main.cpp
//  cleanUp
//
//  Created by Kenneth Gunderson on 4/28/15.
//  Copyright (c) 2015 Kenneth Gunderson. All rights reserved.
//
#include "Parser.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void removeComments(list<string> &);
void removeSpaces(list<string> &);
void displayList(list<string>);
bool empty_line(const string& value){
    return (value.find_first_not_of(" ") == -1);
}

string letter = "", temp="";
list<string>lines;
int count = 0;

int main(int argc, const char * argv[]) {
    
    ifstream finalFile;
    finalFile.open("final.txt");
    while(!finalFile.eof()) {
        getline(finalFile, temp);
        lines.push_back(temp);
    }
    removeComments(lines);
    removeSpaces(lines);
    lines.remove_if(empty_line);
    displayList(lines);
    Parser myparser;
    myparser.Program();
    
    return 0;
}

void removeComments(list<string>& lines) {
    list<string>::iterator it;
    int found;
    int found1;
    bool first = false;
    bool second = false;
    string letter;
    
    for (it = lines.begin(); it != lines.end(); it++) {
        letter = *it;
        found = (int)letter.find("(*");
        if (found >= 0){
            first = true;
        }
        found1 = (int)letter.find("*)");
        if (found1 > 0){
            second = true;
        }
        if(first == true && second == false){
            if (found < 0){
                letter.erase(0, found1);
                *it=letter;
            }else{
                letter.erase(found, found1);
                *it=letter;
            }
        }else if (first == true && second == true){
            if (found <= 0){
                letter.erase(0, found1 +2);
                *it=letter;
            }else{
                letter.erase(found, found1 +2);
                *it = letter;
            }
            first = false;
            second = false;
        }
    }
}

void removeSpaces(list<string>& lines) {
    list<string>::iterator it, it2;
    string currentLine;
    list<string> list2;
    string temp, temp2;
    for (it = lines.begin(); it != lines.end(); it++) {
        currentLine = *it;
        for (int i=0; i<int(currentLine.size()); i++) {
            if(currentLine[i] != ' '){
                temp.append(1, currentLine[i]);
                if(currentLine[i] == '*'){
                    temp.append(1,' ');
                }
                if(currentLine[i+1] == '*'){
                    temp.append(1,' ');
                }
                if(currentLine[i] == '='){
                    temp.append(1,' ');
                }
                if(currentLine[i+1] == '='){
                    temp.append(1,' ');
                }
                if(currentLine[i+1]==':'){
                    temp.append(1,' ');
                }
                if(currentLine[i]==':'){
                    temp.append(1,' ');
                }
                if(currentLine[i] == ','){
                    temp.append(1,' ');
                }
                if(currentLine[i]=='+'){
                    temp.append(1,' ');
                }
                if(currentLine[i+1]=='+'){
                    temp.append(1,' ');
                }
                if(currentLine[i] == '\t'){
                    temp.clear();
                }
                if(temp == "PROGRAM") {
                    temp.append(1,' ');
                }
            } else if(currentLine[i] == ' '){
                if (currentLine[i+1] == '=' || currentLine[i+1] == '+'){
                    temp.append(1, ' ');
                }else{
                    list2.push_back(temp);
                    temp.clear();
                }
            }
        }
        if(temp.size()>0) {
            list2.push_back(temp);
        }
        temp.clear();
        for(it2 = list2.begin(); it2 != list2.end(); it2++){
            temp2.append(*it2);
        }
        *it=temp2;
        temp2.clear();
        list2.clear();
    }
}

void displayList(list<string> lines){
    list<string>::iterator it;
    ofstream myfile ("filename.txt");
    for(it = lines.begin(); it !=lines.end(); it++ ){
        cout <<*it << endl;
        if(myfile.is_open()){
            myfile << *it << endl;
        } else{
            cout << "Unable to open file";
        }
    }
    myfile.close();
}
