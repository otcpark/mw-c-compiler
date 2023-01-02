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
// string scanNumber() {
//   string buffer = "";
  
//   // Implement this.

//   return buffer;
// }

int scanNumber(string buffer){
  if (buffer.find('.')==string::npos){
    
    return T_INT_LIT;
  }else{
   
    return T_FLOAT_LIT;
  }
}
int scanIndentifierAndKeyword(string buffer){
  for(int i = 0; i<=13; i++){
    if(buffer==tokenString[i]){
      return i;
    }
  }
  return T_IDENTIFIER;
}

int scanOperatorAndPunc(string buffer){
  int token = 0;
  for(int i = 14; i<=46;i++){
    if(buffer==tokenString[i]){
      token  = i;
      break;
    }
  }
  return token;
}

TokenNode getToken(string buffer){

  TokenNode tmp;
  tmp.value = buffer;
 


  if(std::regex_match(buffer, std::regex("[-]?[0-9]+[.]?[0-9]*"))){
  
    tmp.token = scanNumber(buffer);
  }else if(std::regex_match(buffer, std::regex("[\\w]+"))){
    tmp.token = scanIndentifierAndKeyword(buffer);
  }else{
    tmp.token = scanOperatorAndPunc(buffer);
  }
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
      std::string line;
    
      while(std::getline(infile,line)){
        string buffer = "";
        string::iterator current;
        current = line.begin();
        line+='\0';
      
        while(*current!='\0'){
          char c = *current;
          if(c == ' '|| c =='\t' || c =='\n' || c =='\r' ){
            if(buffer!=""){
              tokens.push_back(getToken(buffer));
              buffer = "";
            }
          }else if(c=='{' || c == '}' || c == '(' || c==')' || c == ';' || c==','){
            if(buffer!=""){
              tokens.push_back(getToken(buffer));
              buffer = "";
            }
            buffer+=c;
            tokens.push_back(getToken(buffer));
            buffer = "";
          } else if(c == '\"' || c == '\'' ){
            if(buffer!=""){
              tokens.push_back(getToken(buffer));
              buffer = "";
            }
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
          
          }else{
            if(buffer!="" &&(c=='+' || c== '-'||c=='*' || c == '/')){
              tokens.push_back(getToken(buffer));
              buffer = "";
            }
            char nc = *(current+1);
            switch(c){
              case '+':
                if(nc=='+' || nc == '='){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                
                break;
              case '-':
                if(T_INT_LIT <= tokens.back().token && tokens.back().token<= T_IDENTIFIER){
                  if(nc=='-' || nc == '='){
                    buffer+=c;
                    buffer+=nc;
                  }else{
                    buffer+=c;
                  }
                  tokens.push_back(getToken(buffer));
                  buffer = "";
                }else{
                  buffer+=c;
                }
                break;
              case '*':
                if(nc == '='){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              case '/':
                if(nc =='/'){
                  buffer+=c;
                  buffer+=nc;
                  current+=2;
                  while(*current!='\0'){
                    buffer+=*current;
                    current+=1;
                  }
                  TokenNode tmp;
                  tmp.token = T_COMMENT;
                  tmp.value = buffer;
                  tokens.push_back(tmp);
                
                  buffer = "";
                }else{
                  if(nc=='='){
                    buffer+=c;
                    buffer+=nc;
                  }else{
                    buffer+=c;
                  }
                  tokens.push_back(getToken(buffer));
                  buffer = "";
                }
                break;
              case '|':
                if(nc=='|'){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              case '&':
                if(nc=='&'){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              case '!':
                if(nc=='='){
                  buffer+=c;
                  buffer+=nc;

                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              case '=':
                if(nc=='='){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              case '<':
                if(nc=='='){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              case '>':
                if(nc=='='){
                  buffer+=c;
                  buffer+=nc;
                }else{
                  buffer+=c;
                }
                tokens.push_back(getToken(buffer));
                buffer = "";
                break;
              default:
                buffer+=c;
                break;
                
            }
          }
          current+=1;
        }
        if(buffer!=""){
          tokens.push_back(getToken(buffer));
          
        }
        
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
