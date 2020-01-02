//
// Created by eyal on 15/12/19.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include "Lexer.h"
#include <algorithm>
using namespace std;
Lexer::Lexer(string filename)  {
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
        replace(this->afterlerx.begin(),this->afterlerx.end(),')',' ');

        //   for(i=0;this->afterlerx[i]!='\0';++i)
//    {
        //       if(this->afterlerx[i]!=' ')
        //           this->afterlerx[j++]=this->afterlerx[i];
        //  }

        // this->afterlerx[j]='\0';
        replace(this->afterlerx.begin(),this->afterlerx.end(),'(',',');
        size_t start_pos = 0;
        while ((start_pos = afterlerx.find("var", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "var,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("->", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",->,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find('\t', start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, "");
            start_pos += 0; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("<-", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",<-,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("<=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",<=,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(">=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",>=,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("==", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",==,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(" < ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ",<,");
            start_pos += 3; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(" > ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ",>,");
            start_pos += 3; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(" = ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ",=,");
            start_pos += 3; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",=,");
            start_pos += 3; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("<", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",<,");
            start_pos += 3; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(">", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",>,");
            start_pos += 3; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(" == ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 4, ",==,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(" != ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 4, ",!=,");
            start_pos += 4; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("\"", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, "");
            start_pos += 0; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("while ", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 6, "while,");
            start_pos += 6; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("{", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, ",{");
            start_pos += 2; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(",,", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 2, ",");
            start_pos += 1; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find('\t', start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 1, "");
            start_pos += 0; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("<,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "<=");
            start_pos += 2; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find(">,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, ">=");
            start_pos += 2; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("=,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "==");
            start_pos += 2; // Handles case where 'to' is a substring of 'from'
        }
        start_pos = 0;
        while ((start_pos = afterlerx.find("!,=", start_pos)) != string::npos)
        {
            afterlerx.replace(start_pos, 3, "!=");
            start_pos += 2; // Handles case where 'to' is a substring of 'from'
        }


        cout<<this->afterlerx<<endl;
    }

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
