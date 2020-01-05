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
 The lexer gets a filename. The script in the file is written in a new
 programing language that we need to interpret.
 The role of the lexer is to seperate the code by commas and build then into a
 vector.
 */
Lexer::Lexer(char *filename) {
  ifstream file;
  file.open(filename); //object of fstream class
  string line;
  char *dammy;
//opening file "sample.txt" in out(write) mode
  if (file.is_open()) {
    while (getline(file, line)) {
      this->afterlerx += line;
      this->afterlerx += ",";
    }
    int i;
    int j = 0;
    size_t start_pos = 0;
    // add a comma in relevant place
    while ((start_pos = afterlerx.find("openDataServer", start_pos))
        != string::npos) {
      afterlerx.replace(start_pos, 14, "openDataServer,");
      start_pos += 15;
    }
    start_pos = 0;
    // add a comma in relevant place
    while ((start_pos = afterlerx.find("connectControlClient", start_pos))
        != string::npos) {
      afterlerx.replace(start_pos, 20, "connectControlClient,");
      start_pos += 21;
    }
    start_pos = 0;

    while ((start_pos = afterlerx.find("var", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, "var,");
      start_pos += 4;
    }
    start_pos = 0;
    while ((start_pos = afterlerx.find("Sleep", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 5, "Sleep,");
      start_pos += 6;
    }

    start_pos = 0;

    while ((start_pos = afterlerx.find("sim(", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 4, "sim,");
      start_pos += 4;
    }
    start_pos = 0;

    while ((start_pos = afterlerx.find("Print", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 5, "Print,");
      start_pos += 6;
    }
    // add a comma in relevant place
    start_pos = 0;

    while ((start_pos = afterlerx.find("->", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",->,");
      start_pos += 4;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("!=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",!=,");
      start_pos += 4;
    }
    // remove tabs
    start_pos = 0;
    while ((start_pos = afterlerx.find('\t', start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 1, "");
      start_pos += 0;
    }
    start_pos = 0;
    // add a comma in relevant place
    while ((start_pos = afterlerx.find("<-", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",<-,");
      start_pos += 4;
    }
    // add a comma in relevant place
    start_pos = 0;
    while ((start_pos = afterlerx.find("<=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",<=,");
      start_pos += 4;
    }
    // add a comma in relevant place
    start_pos = 0;
    while ((start_pos = afterlerx.find(">=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",>=,");
      start_pos += 4;
    }
    // add a comma in relevant place
    start_pos = 0;
    while ((start_pos = afterlerx.find("==", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",==,");
      start_pos += 4;
    }
    // add a comma in relevant place
    start_pos = 0;
    while ((start_pos = afterlerx.find(" < ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, ",<,");
      start_pos += 3;
    }
    // add a comma in relevant place
    start_pos = 0;
    while ((start_pos = afterlerx.find(" > ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, ",>,");
      start_pos += 3;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find(" = ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, ",=,");
      start_pos += 3;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 1, ",=,");
      start_pos += 3;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("<", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 1, ",<,");
      start_pos += 3;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find(">", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 1, ",>,");
      start_pos += 3;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find(" == ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 4, ",==,");
      start_pos += 4;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("!=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",!=,");
      start_pos += 4;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find(" != ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 4, ",!=,");
      start_pos += 4;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("while ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 6, "while,");
      start_pos += 6;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("while", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 5, "while,");
      start_pos += 6;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("if", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, "if,");
      start_pos += 3;
    }
    start_pos = 0;        // add a comma in relevant place

    while ((start_pos = afterlerx.find("if ", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, "if,");
      start_pos += 3;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find("{", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 1, ",{");
      start_pos += 2;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find(",,", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 2, ",");
      start_pos += 1;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find('\t', start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 1, "");
      start_pos += 0;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find("<,=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, "<=");
      start_pos += 2;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find(">,=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, ">=");
      start_pos += 2;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find("=,=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, "==");
      start_pos += 2;
    }
    start_pos = 0; // add a comma in relevant place
    while ((start_pos = afterlerx.find("!,=", start_pos)) != string::npos) {
      afterlerx.replace(start_pos, 3, "!=");
      start_pos += 2;
    }

  }
  // push all the string with the comma token yo the vector
  char *ve;
  char *cop;
  string after = "";
  ve = new char[this->afterlerx.size() + 1];
  strcpy(ve, this->afterlerx.c_str());
  cop = strtok(ve, ",");
  while (cop) {
    this->vect.push_back(cop);
    cop = strtok(NULL, ",");
  }
  file.close();
}
vector<string> Lexer::getvecor() {
  return this->vect;
}