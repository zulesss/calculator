#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double performOperation(char op, double num1, double num2) {
    switch (op) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 != 0) 
            return num1 / num2;
        else {
            cerr << "You can`t devide by 0" << endl;
            exit(1);
        }
    default:
        cerr << "Unknown operation" << endl;
        exit(1);
    }
}

int getOperatorPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0; 
}

int main() {
    while (true) 
    {
        string expression;
        cout << "Write what do you want to calculate: ";
        getline(cin, expression);

        if (expression == "q") 
            break;

        stack<char> operators;
        stack<double> operands;
        string operand;
        bool isNegative = false;

        for (char c : expression) {
            if (c == ' ') {
                continue; 
            }

            if (c == '-' && operand.empty()) {
                isNegative = true;
                continue;
            }

            if (isOperator(c) || c == '(' || c == ')') {
                
                if (isdigit(operand[0]) || (operand.length() > 1 && operand[0] == '-' && isdigit(operand[1]))) 
                {
                    double num = stod(operand);
                    if (isNegative) 
                    {
                        num = -num; 
                        isNegative = false;
                    }
                    operands.push(num);
                }
                operand.clear();
                

                if (c == '(') 
                    operators.push(c);
                
                else if (c == ')') 
                {
                    while (!operators.empty() && operators.top() != '(') 
                    {
                        char op = operators.top();
                        operators.pop();
                        if (operands.size() < 2)
                        {
                            cerr << "Not enough operands for operation" << endl;
                            exit(1);
                        }
                        double num2 = operands.top();
                        operands.pop();
                        double num1 = operands.top();
                        operands.pop();
                        double result = performOperation(op, num1, num2);
                        operands.push(result);
                    }
                    if (operators.top() == '(')
                        operators.pop();
                    else 
                    {
                        cerr << "Brackets placed incorrectly" << endl;
                        exit(1);
                    }
                }
                else if (isOperator(c))
                {
                    while (!operators.empty() && operators.top() != '(' &&
                        getOperatorPrecedence(operators.top()) >= getOperatorPrecedence(c)) 
                    {
                        char op = operators.top();
                        operators.pop();
                        if (operands.size() < 2) {
                            cerr << "Not enough operands for operation" << endl;
                            exit(1);
                        }
                        double num2 = operands.top();
                        operands.pop();
                        double num1 = operands.top();
                        operands.pop();
                        double result = performOperation(op, num1, num2);
                        operands.push(result);
                    }
                    operators.push(c);
                }
            }
            else 
                operand += c;
        }


        if (!operand.empty()) 
        {
            double num = stod(operand);
            if (isNegative)
            {
                num = -num; 
                isNegative = false;
            }
            operands.push(num);
        }

        while (!operators.empty()) 
        {
            char op = operators.top();
            operators.pop();
            if (operands.size() < 2)
            {
                cerr << "Not enough operands for operation" << endl;
                exit(1);
            }
            double num2 = operands.top();
            operands.pop();
            double num1 = operands.top();
            operands.pop();
            double result = performOperation(op, num1, num2);
            operands.push(result);
        }

        if (operands.size() == 1) 
            cout << "Result: " << operands.top() << endl;
        else 
            cerr << "Incorrect expression" << endl;
    }

    return 0;
}