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

//scan a number, integer or float
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
      
    
      while(std::getline(infile,line)){
       
        string::iterator current;
        current = line.begin();
        line+='\0';
        bool minus_num_flag = false;
      
        
        while(*current!='\0'){
          
          char c = *current;
        
          if(c == ' '|| c =='\t' || c =='\n' || c =='\r' ){
            current++;
            continue;
          }
          else if ((c>='a' && c<='z') || (c >='A' && c<='Z')){
            string buffer = "";
            while(true){
              if((*current >='a' && *current <='z') || (*current>='A' && *current<='Z')){
                buffer+=*current;
                current++;
              }else{
                break;
              }
            }
           
            TokenNode tmp;
            bool flag = false;
            for(int i = 0; i<=13 ; i++){
              if(tokenString[i] == buffer){
                tmp.token = i;
                tmp.value = buffer;
                flag= true;
                break;
              }
            }
            if(!flag){
              tmp.token = T_IDENTIFIER;
              tmp.value = buffer;
            }
           
            tokens.push_back(tmp);

          }else if('0'<=c && c<='9'){
            string buffer = "";
            while('0'<=*current && *current<='9' || *current =='.'){
              buffer+=*current;
              current++;
            }
            TokenNode tmp;
            if(minus_num_flag){
              buffer = "-"+buffer;
              minus_num_flag = false;
            }
            if(buffer.find('.') == string::npos){
              tmp.token = T_INT_LIT;
            }else{
              tmp.token = T_FLOAT_LIT;
            }
            tmp.value = buffer;
            
            tokens.push_back(tmp);
          }else{
            TokenNode tmp;
            string buffer = "";
            buffer +=c;
            buffer +=*(current+1);
            bool flag = false;

            int index = 18;
            while(index<=35){
              if(tokenString[index] == buffer){
                flag = true;
                current+=2;
                tmp.token = index;
                tmp.value = buffer;
                tokens.push_back(tmp);
                
                break;
              }
              if(index==19){
                index = 23;
              }else if(index == 26){
                index = 29;
              }else{
                index++;
              }
            }
            if(flag){
              continue;
            }
            buffer = "";
            if(c=='/' && *(current+1) == '/'){
              while(*(current)!='\0'){
                buffer+=*current;
                current++;
              }
              tmp.token = T_COMMENT;
              tmp.value = buffer;
            }else if(c =='-' && !(T_INT_LIT <= tokens.back().token && tokens.back().token<= T_IDENTIFIER)){
              minus_num_flag = true;
              current++;
            }else if(c=='\'' || c =='\"'){
              current++;
              while(true){
                c = *current;
                if((c=='\"' || c == '\'') &&(*(current-1)!='\\') ){
                  current++;
                  break;
                }
                buffer+=c;
                current++;
              }
              tmp.token = T_STR_LIT;
              tmp.value = buffer;
              
           
            }else{
              buffer+=c;
              for(int i = 14; i<=41; i++){
                if(tokenString[i] == buffer){
                  current++;
                  tmp.token = i;
                  tmp.value = buffer;
                  break;
                }
              }
            }
            if(!minus_num_flag){
             
              tokens.push_back(tmp);
            }
          }
   
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
