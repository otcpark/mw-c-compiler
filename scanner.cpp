#include "defs.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex> // regex library call

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

TokenNode getToken(string buffer){
  
  
  TokenNode tmp;
  if(buffer =="int"){
    tmp.token = T_INT;
    
  }else if(buffer == "float"){
    tmp.token = T_FLOAT;
   
  }else if(buffer == "char"){
    tmp.token = T_CHAR;

  }else if(buffer == "bool"){
    tmp.token = T_BOOL;
    
  }else if(buffer == "void"){
    tmp.token = T_VOID;
   
  }else if(buffer == "return"){
    tmp.token = T_RETURN;
   
  }else if(buffer == "break"){
    tmp.token = T_BREAK;
  
  }else if(buffer == "continue"){
    tmp.token = T_CONTINUE;
    
  }else if(buffer == "for"){
    tmp.token = T_FOR;
  
  }else if(buffer == "while"){
    tmp.token = T_WHILE;
   
  }else if(buffer == "if"){
    tmp.token = T_IF;
    
  }else if(buffer == "else"){
    tmp.token = T_ELSE;
    
  }else if(buffer == "printf"){
    tmp.token = T_PRINT;
 
  }else{
    if(std::regex_match(buffer,std::regex("-?[0-9]+\\.{1}[0-9]+"))){
    
      tmp.token = T_FLOAT_LIT;
     
    }
    else if(std::regex_match(buffer,std::regex("[0-9]+"))){
      
      tmp.token = T_INT_LIT;
      
    }
    else if(std::regex_match(buffer,std::regex("[\\w]+"))){
      tmp.token = T_IDENTIFIER;
     
    }
    
  }
  tmp.value = buffer;
  return tmp;

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
      
      string SourceCode;
      string line;
    
      while(getline(infile,line)){
          SourceCode+=line;
          SourceCode+='\n';
          
      }
      SourceCode+='\0';
     

      string::iterator current;
      current = SourceCode.begin();

      string buffer = "";
      while(*current!='\0'){
          char c  = *current;
         
          if(c == ' ' || c == '\t' || c =='\n' || c =='\r'){
            if(buffer != ""){
              TokenNode tmp = getToken(buffer);
              tokens.push_back(tmp);
              buffer = "";
            }
          }
          else if('0'<=c && c<='9'){
            buffer+=c;
          }
          else if(c == '\"' || c == '\'' ){
            current+=1;
            while(true){
              c = *current;
              if((c=='\"' || c == '\'') &&(*(current-1)!='\\') ){
                break;
              }
              buffer+=c;
              current+=1;
            }
            TokenNode tmp;
            tmp.token = T_STR_LIT;
            tmp.value = buffer;
            tokens.push_back(tmp);
            buffer = "";
            
          }
          else if('a'<= c && c <='z' || 'A'<=c && c<='Z'){
            buffer+=c;
          }else if(c=='.'){
            buffer+=c;
          }
          else{
            if(buffer!=""){
              TokenNode tmp = getToken(buffer);
              tokens.push_back(tmp);
              buffer = "";
            }
            TokenNode tmp;
            if(c==';'){
              buffer+=c;
              tmp.token = T_SEMICOLON;
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c=='&'){
              buffer+=c;
              if(*(current+1)=='&'){
                current+=1;
                buffer+=*current;
                tmp.token = T_AND;
              }else{
                tmp.token = T_BITW_AND;
              }
              tmp.value  = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c=='|'){
              buffer+=c;
              if(*(current+1)=='|'){
                current+=1;
                buffer+=*current;
                tmp.token = T_OR;
              }else{
                tmp.token = T_BITW_OR;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c=='>'){
              buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_GEQ;
              }else{
                tmp.token = T_GT;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c=='<'){
              buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_LEQ;
              }else{
                tmp.token = T_LT;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c=='='){
              buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_EQ;
              }else{
                tmp.token = T_ASSIGN;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c=='!'){
              buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_NEQ;
              }else{
                tmp.token = T_NEGATION;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            }else if(c == '(' || c==')' || c =='{' || c == '}' || c==','){
              buffer+=c;
              switch(c){
                case '(':
                  tmp.token = T_LPAREN;
                  break;
                case ')':
                  tmp.token = T_RPAREN;
                  break;
                case '{':
                  tmp.token = T_LCURLY;
                  break;
                case '}':
                  tmp.token = T_RCURLY;
                  break;
                case ',':
                  tmp.token = T_COMMA;
                  break;
              }
              tokens.push_back(tmp);
              buffer ="";

            }else if(c=='+'){
              buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_PLUS_ASSIGN;
              }else if(*(current+1)=='+'){
                current+=1;
                buffer+=*current;
                tmp.token = T_UNARY_PLUS;
              }else{
                tmp.token = T_PLUS;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";
            
            }else if(c=='-'){
              if(T_INT_LIT <= tokens.back().token && tokens.back().token<= T_IDENTIFIER){
                buffer+=c;
                if(*(current+1)=='='){
                  current+=1;
                  buffer+=*current;
                  tmp.token = T_MINUS_ASSIGN;
                }else if(*(current+1)=='-'){
                  current+=1;
                  buffer+=*current;
                  tmp.token = T_UNARY_MINUS;
                }else{
                  tmp.token = T_MINUS;
                }
                tmp.value = buffer;
                tokens.push_back(tmp);
                buffer = "";
              }else{
                buffer+=c;
              }

            }else if(c=='*'){
               buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_STAR_ASSIGN;
              }else{
                tmp.token = T_STAR;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";

            }else if (c== '/'){
               buffer+=c;
              if(*(current+1)=='='){
                current+=1;
                buffer+=*current;
                tmp.token = T_SLASH_ASSIGN;
              }else if(*(current+1)=='/'){
                current+=1;
                while(true){
                  c = *current;
                  if(c == '\n'){
                    break;
                  }
                  buffer+=c;
                  current+=1;
                }
                tmp.token = T_COMMENT;
                           
              }else{
                tmp.token = T_SLASH;
              }
              tmp.value = buffer;
              tokens.push_back(tmp);
              buffer = "";

            }
            
            
          }
          current+=1;
      }
     
    
  
    
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
