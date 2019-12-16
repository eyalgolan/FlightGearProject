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

    for(i=0;this->afterlerx[i]!='\0';++i)
    {
        if(this->afterlerx[i]!=' ')
            this->afterlerx[j++]=this->afterlerx[i];
    }

    this->afterlerx[j]='\0';
    replace(this->afterlerx.begin(),this->afterlerx.end(),'(',',');

    cout<<this->afterlerx<<endl;





}
}



