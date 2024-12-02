#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

const string OPERATORS = "+-*/()";
const int PRECEDENCE[] = {1, 1, 2, 2, -1, -1};
stack<char> operator_stack;
stack<double>operand_stack;

string::size_type is_operator(char ch) {
    return OPERATORS.find(ch);
}
int precedence(char op) {
        return PRECEDENCE[is_operator(op)];
}
double eval_op(char op) {
    if (operand_stack.empty())
        throw runtime_error("Syntax Error: Stack empty in eval_op.");
    double rhs = operand_stack.top();
    operand_stack.pop();
    if (operand_stack.empty())
        throw runtime_error("Syntax Error: Stack empty in eval_op.");
    double lhs = operand_stack.top();
    operand_stack.pop();
    double result = 0;
    switch (op) {
        case '+': result = lhs + rhs; break;
        case '-': result = lhs - rhs; break;
        case '*': result = lhs * rhs; break;
        case '/': result = lhs / rhs; break;
    }
    return result;
}

void process_op(char op, stringstream &postfix) {
    if (operator_stack.empty() || op=='(') {
        operator_stack.push(op);
    }
    else {
        char top_op = operator_stack.top();
        if (precedence(op) > precedence(top_op)) {
            operator_stack.push(op);
        }
        else {
            while(!operator_stack.empty() && precedence(op) <= precedence(top_op)) {
                operator_stack.pop();
                if (top_op == '(')
                    break;
                double result = eval_op(top_op);
                operand_stack.push(result);
                if (!operator_stack.empty())
                    top_op = operator_stack.top();
            }
            if (op != ')')
                operator_stack.push(op);
        }
    }
}
double convert_and_eval(string infix) {
    stringstream postfix, infixstream(infix);
    string token="";
    bool expect_operand = true;
    for(int i=0;i<infix.length();i++) {
        if (isdigit(infix[i]) || infix[i] == '.') {
            token += infix[i];
            expect_operand = false;
        }
        else if (infix[i] == ' ') {
            if (token.length() != 0) {
                operand_stack.push(stod(token));
                token = "";
            }
        }
        else if (is_operator(infix[i]) !=string::npos) {
            if(infix[i]=='-'&& expect_operand){
                token+=infix[i];
            }
            else {
                if (token.length() != 0) {
                    operand_stack.push(stod(token));
                    token = "";
                }
                process_op(infix[i], postfix);
                expect_operand = true;
            }
        }
        else
            throw runtime_error("Syntax Error: invalid character encountered.");
        if(i==infix.length()-1)
            if(token.length()!=0)
                operand_stack.push(stod(token));
    }
    while(!operator_stack.empty()) {
        char op = operator_stack.top();
        if (op == '(')
            throw runtime_error("Unmatched parenthesis.");
        double result = eval_op(op);
        operand_stack.push(result);
        operator_stack.pop();
    }
    return operand_stack.top();
}


int main() {
    string expr;
    cout << "Enter an infix expression: ";
    getline(cin, expr);
    cout << convert_and_eval(expr) << endl;
    return 0;
}
