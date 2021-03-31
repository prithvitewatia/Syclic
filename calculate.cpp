#include "parse_eval.hpp"

void help(){
    std::string help_msg=
    "Help of utility calculate\n"
    "This is a small command line calculator.\n"
    "Operations supported\n"
    "+: addition\n"
    "-: subtraction\n"
    "*: multiplication\n"
    "/: division\n"
    "^^: exponentiation\n"
    "Example:calculate 32.79+64.21+(3-1)^^5";
}

int main(int argc,char* argv[]){
    if(argc==1){
        std::cout<<"Nothing to calculate. Exiting!!!";
        exit(-1);
    }
    std::string infix_str(argv[1]);
    int arg_n=2;
    // Ignoring whitespaces 
    while(arg_n<argc){
        std::string s(argv[arg_n]);
        infix_str+=s;
        arg_n++;
    }
    std::string postfix_str=to_postfix(infix_str);
    // std::cout<<"postfix_str="<<postfix_str<<"\n";
    double result=evaluate_postfix(postfix_str);
    std::cout<<result;
    return 0;
}