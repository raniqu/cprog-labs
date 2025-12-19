#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <vector>


class Calculator {
private:
    std::string expression;
    double x_value = 0.0;
    bool has_x = false;

    std::string removeSpaces(const std::string& s) {
        std::string result;
        for (char c : s)
            if (!std::isspace(static_cast<unsigned char>(c)))
                result += c;
        return result;
    }

    bool isNumber(const std::string& s) {
        if (s.empty()) return false;
        bool hasDot = false;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '.') {
                if (hasDot) return false;
                hasDot = true;
            } else if (!std::isdigit(static_cast<unsigned char>(s[i]))) {
                return false;
            }
        }
        return true;
    }

    bool isFunction(const std::string& s) {
        return s == "sin" || s == "cos" || s == "tg" || s == "ctg" || s == "exp";
    }

    int precedence(const std::string& op) {
        if (op == "u-") return 3;
        if (op == "*" || op == "/") return 2;
        if (op == "+" || op == "-") return 1;
        return 0;
    }

    std::vector<std::string> tokenize(const std::string& expr) {
        std::vector<std::string> tokens;
        std::string token;

        for (size_t i = 0; i < expr.size(); ++i) {
            char c = expr[i];

            if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
                token += c;
            } else if (std::isalpha(static_cast<unsigned char>(c))) {
                token += c;
                // собираю имя функции
                while (i + 1 < expr.size() && std::isalpha(static_cast<unsigned char>(expr[i + 1]))) {
                    token += expr[++i];
                }

                tokens.push_back(token);
                token.clear();
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
                tokens.push_back(std::string(1, c));
            } else {
                throw std::invalid_argument("Invalid character: '" + std::string(1, c) + "'");
            }
        }
        if (!token.empty()) tokens.push_back(token);
        return tokens;
    }

    // алгоритм Дейкстры
    std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
        std::vector<std::string> output;
        std::stack<std::string> ops;
        bool expectOperand = true;

        for (const std::string& token : tokens) {
            if (token == "x") {
                if (!expectOperand)
                    throw std::invalid_argument("Expected operator, found 'x'");
                output.push_back(token);
                has_x = true;
                expectOperand = false;
            } else if (isNumber(token)) {
                if (!expectOperand)
                    throw std::invalid_argument("Expected operator, found number");
                output.push_back(token);
                expectOperand = false;
            } else if (isFunction(token)) {
                if (!expectOperand)
                    throw std::invalid_argument("Function cannot follow operand");
                ops.push(token);
                expectOperand = true;
            } else if (token == "(") {
                ops.push(token);
                expectOperand = true;
            } else if (token == ")") {

                while (!ops.empty() && ops.top() != "(") {
                    output.push_back(ops.top());
                    ops.pop();
                }
                if (ops.empty())
                    throw std::invalid_argument("Mismatched parentheses: extra ')'");
                ops.pop();

                if (!ops.empty() && isFunction(ops.top())) {
                    output.push_back(ops.top());
                    ops.pop();
                }
                expectOperand = false;
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (expectOperand) {

                    if (token == "-") {
                        ops.push("u-");
                        expectOperand = true;
                        continue;
                    } else {
                        throw std::invalid_argument("Unary '+' not supported: '" + token + "'");
                    }
                }

                while (!ops.empty() && ops.top() != "(" &&
                       precedence(ops.top()) >= precedence(token)) {
                    output.push_back(ops.top());
                    ops.pop();
                }
                ops.push(token);
                expectOperand = true;
            } else {
                throw std::invalid_argument("Unknown token: '" + token + "'");
            }
        }


        while (!ops.empty()) {
            if (ops.top() == "(" || ops.top() == ")")
                throw std::invalid_argument("Mismatched parentheses: missing ')'");
            output.push_back(ops.top());
            ops.pop();
        }

        return output;
    }

    // вычисляю постфиксн выражение
    double evaluatePostfix(const std::vector<std::string>& postfix) {
        std::stack<double> st;

        for (const std::string& token : postfix) {
            if (token == "x") {
                st.push(x_value);
            } else if (isNumber(token)) {
                st.push(std::stod(token));
            } else if (isFunction(token)) {
                if (st.size() < 1)
                    throw std::invalid_argument("Not enough arguments for function '" + token + "'");
                double arg = st.top(); st.pop();
                if (token == "sin") st.push(std::sin(arg));
                else if (token == "cos") st.push(std::cos(arg));
                else if (token == "tg") st.push(std::tan(arg));
                else if (token == "ctg") {
                    double t = std::tan(arg);
                    if (std::abs(t) < 1e-12)
                        throw std::invalid_argument("ctg undefined");
                    st.push(1.0 / t);
                }
                else if (token == "exp") st.push(std::exp(arg));
            } else if (token == "u-") {
                if (st.size() < 1)
                    throw std::invalid_argument("Not enough operands for unary minus");
                double a = st.top(); st.pop();
                st.push(-a);
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (st.size() < 2)
                    throw std::invalid_argument("Not enough operands for operator '" + token + "'");
                double b = st.top(); st.pop();
                double a = st.top(); st.pop();
                if (token == "+") st.push(a + b);
                else if (token == "-") st.push(a - b);
                else if (token == "*") st.push(a * b);
                else if (token == "/") {
                    if (std::abs(b) < 1e-12)
                        throw std::invalid_argument("Division by zero");
                    st.push(a / b);
                }
            } else {
                throw std::invalid_argument("Unknown token during evaluation: '" + token + "'");
            }
        }

        if (st.size() != 1)
            throw std::invalid_argument("Invalid expression");

        return st.top();
    }

public:

    double evaluate(const std::string& inputExpr) {
        expression = removeSpaces(inputExpr);
        if (expression.empty())
            throw std::invalid_argument("Empty expression");

        has_x = false;

        std::vector<std::string> tokens = tokenize(expression);

        std::vector<std::string> postfix = infixToPostfix(tokens);

        if (has_x) {
            std::cout << "Enter x = ";
            std::cin >> x_value;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid input for x");
            }
        }

        return evaluatePostfix(postfix);
    }
};

int main() {
    Calculator calc;
    std::string expr;

    std::cout << "=== Awesome Calculator present===\n";
    std::cout << "Supported operations: +, -, *, /\n";
    std::cout << "Functions: sin, cos, tg, ctg, exp\n";
    std::cout << "Type 'exit' to finally exit :)\n\n";

    while (true) {
        std::cout << "Enter expression: ";
        std::getline(std::cin, expr);

        if (expr == "exit")
            break;

        try {
            double result = calc.evaluate(expr);
            std::cout << "Result: " << result << "\n\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n\n";
        }
    }

    return 0;
}