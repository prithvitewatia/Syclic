#include "parse_eval.hpp"

std::vector<char> non_operands{'+','-','*','/','^','(',')','#',' '};
std::vector<char> operators{'+','-','*','/','^'};

static int op_precd(char op){
    if(op=='^')
        return 5;
    else if((op=='*')||(op=='/'))
        return 4;
    else if((op=='+')||(op=='-')){
        return 3;
    }
}

static inline bool is_operator(char ch){
    if(std::find(operators.begin(),operators.end(),ch)!=operators.end()){
        return true;
    }
    else{
        return false;
    }
}

static inline bool isNumerical(char ch){
    if(find(non_operands.begin(),non_operands.end(),ch)==non_operands.end())
        return true;
    else
        return false;
}

static std::string preprocess(std::string st){
    // Adding a sentinal to mark the end of string
    st+="#";
    std::string operand;
    std::string add_str;
    // Checking if symbol is unary minus
    // If yes replace it with (0-<operand>)
    for(int i=0;i<st.length();i++){
        if(st[i]=='-'){
            if(i==0 || 
                is_operator(st[i-1])||
                st[i-1]=='('){
                    int j;
                    for(j=i+1;j<st.length() && isNumerical(st[j]);j++){
                        operand.append(1,st[j]);
                    }
                if(j+1<st.length()&& st[j+1]==')')
                    add_str="(0-"+operand;
                else
                    add_str="(0-"+operand+")";
                st.erase(i,operand.length()+1);
                st.insert(0,add_str);
                add_str="";
                operand="";
            }
        }
    }
    return st;
}

std::string to_postfix(std::string infix_str){

    // preprocessing the infix string
    infix_str=preprocess(infix_str);

    std::string postfix_str="";
    std::string operand_str="";
    std::stack<char> op_stack;
    
    for(auto c:infix_str){
        // Checking if the scanned character forms
        // a part of operand
        if(isNumerical(c)){
            operand_str.append(1,c);
        }
        else{
            postfix_str+=" "+operand_str;
            operand_str="";
        }
        // if the scanned character is an operator
        if(is_operator(c)){
            if(op_stack.empty()||
               op_stack.top()=='('||
               op_precd(c)>op_precd(op_stack.top())){
                   op_stack.push(c);
            }
            else{
                while(!op_stack.empty() && op_precd(c)<=op_stack.top()){
                    char op=op_stack.top();
                    if(op=='(')
                        break;
                    else{
                        postfix_str.append(1,op);
                        op_stack.pop();
                    }   
                }
                op_stack.push(c);
            }
        }
        else if(c=='('){
            op_stack.push(c);
        }
        else if(c==')'){
            while (op_stack.top()!='(')
            {
                char op=op_stack.top();
                op_stack.pop();
                postfix_str.append(1,op);
            }
            op_stack.pop();
        }
    }
    while (!op_stack.empty())
    {
        postfix_str.append(1,op_stack.top());
        op_stack.pop();
    }
    return postfix_str;
}

static double perform_op(double op1,double op2,char oper){
    switch(oper){
        case '^':
            return std::pow(op1,op2);
            break;
        case '/':
            try
            {
                double res=op1/op2;
                return res;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        case '*':
            return op1*op2;
            break;
        case '+':
            return op1+op2;
            break;
        case '-':
            return op1-op2;
            break;
    }
}

double evaluate_postfix(std::string postfix_str){
    std::stack<double> output;
    std::string operand="";
    for(auto x:postfix_str){
        if(isNumerical(x)){
            operand.append(1,x);
        }
        else{
            if(!operand.empty()){
                double current_operand=std::stod(operand);
                output.push(current_operand);
            }
            operand="";
        }
        if(is_operator(x)){
            double operand1=output.top();
            output.pop();
            double operand2=output.top();
            output.pop();
            double res=perform_op(operand2,operand1,x);
            output.push(res);
        }
    }
    double result=output.top();
    return result;

}