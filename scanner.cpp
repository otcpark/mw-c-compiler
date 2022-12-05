#include "defs.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ifstream infile;

TokenNode::TokenNode(int token, string value, int line_number, int token_end) {
  this->token = token;
  this->value = value;
  this->line_number = line_number;
  this->token_end = token_end;
}

// print a string representation of the token
void TokenNode::print() {
  if (token == T_STR_LIT)
    cout << "string -> \"" << value << "\"";
  else if (token == T_CHAR_LIT)
    cout << "character literal -> '" << value << "'";
  else if (token >= T_INT_LIT)
    cout << tokenString[token] << " -> " << value;
  else {
    if (token >= T_INT && token <= T_PRINT)
      cout << "keyword -> " << tokenString[token];
    else if (token >= T_PLUS && token <= T_SLASH_ASSIGN)
      cout << "operator -> " << tokenString[token];
    else if (token >= T_LCURLY && token <= T_SEMICOLON)
      cout << "separator -> " << tokenString[token];
  }
  cout << endl;
}

// scan a number, integer or float
string scanNumber() {
  string buffer = "";
  
  // Implement this.

  return buffer;
}

pair<vector<TokenNode>, vector<string>> scan(const string &file_name) {
  infile.open(file_name, ios::in); // attempt to open the file
  if (infile.fail()) {             // check for file status
    perror("file open failed");
    exit(EXIT_FAILURE);
  }

  vector<TokenNode> tokens = {};

  // Implement this.
  if (infile.is_open()) {

      std::string line;
      while (std::getline(infile, line))
          cout << line;




  }
  // close the file
  infile.close();

  vector<string> lines = {};
  ifstream file(file_name);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line))
      lines.push_back(line);
    file.close();
  }

  return {tokens, lines};
}
