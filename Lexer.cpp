//
// Created by eyal on 15/12/19.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include "Lexer.h"
#include <algorithm>
using namespace std;
/**
 The lexer get filaname that represent new programing language ,
 we want to The role of the lexer is to separate the text file into commas
 and insert a locator that the parser can know and separate in future
 commands and parameters.
 */
Lexer::Lexer(char *filename)  {
    ifstream file;
    file.open(filename); //object of fstream class
    string line;
    char* dammy;
//opening file "sample.txt" in out(write) mode
    if (file.is_open()){
        while (getline(file,line)){
            this->afterlerx+=line;
            this->afterlerx+=",";
        }
        int i;
        int j=0;
        // relace all ')' chars to space
        replace(this->afterlerx.begin(),this->afterlerx.end(),')',' ');
        // relace all ')' chars to
        replace(this->afterlerx.begin(),this->afterlerx.end(),'(',',');
        size_t start_pos = 0;
        // add a comma in relevant place
        while ((start_pos = afterlerx.find("var", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "var,");
            start_pos += 4;
        }
        // add a comma in relevant place
        start_pos = 0;
        while ((start_pos = afterlerx.find("->", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",->,");
            start_pos += 4;
        }
        // remove tabs
        start_pos = 0;
        while ((start_pos = afterlerx.find('\t', start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, "");
            start_pos += 0;
        }
        start_pos = 0;
        // add a comma in relevant place
        while ((start_pos = afterlerx.find("<-", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",<-,");
            start_pos += 4;
        }
        // add a comma in relevant place
        start_pos = 0;
        while ((start_pos = afterlerx.find("<=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",<=,");
            start_pos += 4;
        }
        // add a comma in relevant place
        start_pos = 0;
        while ((start_pos = afterlerx.find(">=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",>=,");
            start_pos += 4;
        }
        // add a comma in relevant place
        start_pos = 0;
        while ((start_pos = afterlerx.find("==", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",==,");
            start_pos += 4;
        }
        // add a comma in relevant place
        start_pos = 0;
        while ((start_pos = afterlerx.find(" < ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ",<,");
            start_pos += 3;
        }
        // add a comma in relevant place
        start_pos = 0;
        while ((start_pos = afterlerx.find(" > ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ",>,");
            start_pos += 3;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find(" = ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ",=,");
            start_pos += 3;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",=,");
            start_pos += 3;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("<", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",<,");
            start_pos += 3;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find(">", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",>,");
            start_pos += 3;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find(" == ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 4, ",==,");
            start_pos += 4;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find(" != ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 4, ",!=,");
            start_pos += 4;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("\"", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, "");
            start_pos += 0;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("while ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 6, "while,");
            start_pos += 6;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("while", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 5, "while,");
            start_pos += 6;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("if", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, "if,");
            start_pos += 3;
        }
        start_pos = 0;        // add a comma in relevant place

        while ((start_pos = afterlerx.find("if ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "if,");
            start_pos += 3;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find("{", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",{");
            start_pos += 2;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find(",,", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",");
            start_pos += 1;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find('\t', start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, "");
            start_pos += 0;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find("<,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "<=");
            start_pos += 2;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find(">,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ">=");
            start_pos += 2;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find("=,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "==");
            start_pos += 2;
        }
        start_pos = 0; // add a comma in relevant place
        while ((start_pos = afterlerx.find("!,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "!=");
            start_pos += 2;
        }


        cout<<this->afterlerx<<endl;
    }
   // push all the string with the comma token yo the vector
    char *ve;
    char *cop;
    ve= new char[this->afterlerx.size()+1];
    strcpy(ve,this->afterlerx.c_str());
    cop=strtok(ve,",");
    while (cop){
        this->vect.push_back(cop);
        cop=strtok(NULL,",");
    }


}
vector<string> Lexer::getvecor() {
    return this->vect;
}
