#include <iostream>
#include <stack>
#include <string>


int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> operators;
    std::string postfix;
    for (char c : infix) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            continue;
        }
        if (std::isalnum(static_cast<unsigned char>(c))) {
            postfix += c;
        }

        else if (c == '(') {
            operators.push(c);
        }

        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }

            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        }

        else {
            while (!operators.empty() && operators.top() != '(' &&
                   getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfix += operators.top();
                operators.pop();
                   }
            operators.push(c);
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int main() {
    std::string infix = "3+4*2/(1-5)";
    std::string postfix = infixToPostfix(infix);
    std::cout << postfix << std::endl;

    return 0;
}