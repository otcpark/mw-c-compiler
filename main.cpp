#include "decl.hpp"
#include "defs.hpp"
#include <iostream>

using namespace std;

// use different file paths based on the platform i.e. Windows or Linux
// #if defined(WIN32) || defined(_WIN32) ||                                       \
//     defined(__WIN32) && !defined(__CYGWIN__)
// string test_file_path = "..\\tests\\test10.c";
// #else
// string test_file_path = "tests/test10.c";
// #endif


string test_file_path = "./tests/test10.c"; // edited line

int main(int argc, char **argv) {
  if (argc ==
      2) // file called using a command line argument i.e. ./main tests/test08.c
    test_file_path = argv[1];

  cout<<test_file_path<<endl;
  
  cout << "Scanning..." << endl;
  
  auto [tokens, lines] = scan(test_file_path); // scan for all tokens
  for (auto t : tokens)
      
      t.print();  // print the tokens

 
  //cout << "\nParsing..." << endl;
  //shared_ptr<ASTNode> root = parse(tokens, lines);

  //cout << "\nGenerating intermediate code..." << endl;
  //genIntermediateCode(root);

  return 0;
}
