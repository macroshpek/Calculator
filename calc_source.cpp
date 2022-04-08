#include <iostream>
#include<string>
#include<exception>
#include<cassert>

//precision - six numbers after comma

enum class Operations {
    NOP, // just a value
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /
    END, // /0
};

size_t checkDigit(std::string expression);
std::string SkipSpaces(std::string expression);
Operations TakeOperand(const char operand);
size_t findBrackets(std::string expression);
struct Expr;
long double CalculateExpression(Expr* expr);

struct Expr {
    long double value = 0;
    Operations op = Operations::NOP;
    Expr* lExpr;
    Expr* rExpr;

    Expr() {
        value = 0;
        op = Operations::NOP;
        lExpr = nullptr;
        rExpr = nullptr;
    }
    Expr(const std::string& str) {
        std::string expression = SkipSpaces(str);
        size_t position = 0;
        if (expression.substr(position,2) == "-(") {
            size_t temp = findBrackets(expression.substr(1));
            Expr* expr = new Expr(expression.substr(2, temp - 2));
            long double result = -1.0 * CalculateExpression(expr);
            expression.replace(0, temp + 1, std::to_string(result));
            delete expr;
            *this = Expr(expression);
            return;
        }
        else if ('0' <= expression[position] && expression[position] <= '9' || expression[position] == '-') {
            size_t digit_dimention = checkDigit(expression);
            if (digit_dimention == expression.length()) {
                this->value = stod(expression);
                this->op = Operations::NOP;
                return;
            }
            this->op = TakeOperand(expression[digit_dimention]);
            static size_t temp = 0;
            while (this->op == Operations::MUL || this->op == Operations::DIV) {
                temp = checkDigit(expression.substr(digit_dimention + 1));
                if (temp + digit_dimention == expression.length() - 1) {
                    break;
                }
                if (expression[digit_dimention + temp + 1] == '(') {
                    size_t _temp = findBrackets(expression.substr(digit_dimention + temp + 1));
                    Expr* temp_expr = new Expr(expression.substr(digit_dimention + temp + 1, _temp));
                    long double result = CalculateExpression(temp_expr);
                    expression.replace(digit_dimention + 1, _temp, std::to_string(result));
                    temp = checkDigit(expression.substr(digit_dimention + 1));
                }
                Operations temp_op = TakeOperand(expression[digit_dimention + temp + 1]);//при встрече скобки сразу вычислять значение в скобках
                if (temp_op == Operations::END) {
                    break;
                }
                else {
                    this->op = temp_op;
                }
                digit_dimention = digit_dimention + temp + 1;
            }
            lExpr = new Expr(expression.substr(0, digit_dimention));
            if (this->op == Operations::SUB) {
                rExpr = new Expr(expression.substr(digit_dimention));
                return;
            }
            rExpr = new Expr(expression.substr(digit_dimention + 1));
            return;
        }
        else if (expression[position] == '(') {
            size_t temp = findBrackets(expression);
            if (temp == expression.length()) {
                *this = Expr(expression.substr(1, temp-2));
            }
            else {
                lExpr = new Expr(expression.substr(1, temp - 2));
                this->op = TakeOperand(expression[temp]);
                rExpr = new Expr(expression.substr(temp + 1));
                return;
            }
        }
        else if (expression[position] == '+') {
            *this = Expr(expression.substr(1));
        }
        else {
            assert(false);//undefiend expression
        }
    }
};

std::string SkipSpaces(std::string expression) {
    size_t position = 0;
    std::string newExpression = "";
    while (position < expression.length()) {
        if (expression[position] == ' ') {
            position++;
            continue;
        }
        newExpression = newExpression + expression[position];
        position++;
    }
    return newExpression;
}//done!

size_t checkDigit(std::string expression) {
    size_t position = 0;
    std::string expr = "";
    if (expression[position] == '-') {
        position++;
    }
    while ('0' <= expression[position] && expression[position] <= '9') {
        expr = expr + expression[position];
        position++;
    }
    if (expression[position] == '.') {
        expr = expr + expression[position];
        position++;
    }
    while ('0' <= expression[position] && expression[position] <= '9') {
        expr = expr + expression[position];
        position++;
    }
    if (expression[position] == '.') {//работает не корректно
        throw std::exception("expression contains NAN");
    }
    return position;
}//needs rework

Operations TakeOperand(const char operand) { //done!
    switch (operand) {
        case'+':
            return Operations::ADD;
        case'-':
            return Operations::SUB;
        case'*':
            return Operations::MUL;
        case'/':
            return Operations::DIV;
        case'\0':
            return Operations::END;
            break;
        default:
            throw("undefiend operand");
            break;
    }
}

size_t findBrackets(std::string expression) {//:cc
    size_t count = 1;
    size_t position = 1;
    while (position < expression.length() && !(count == 0)) {
        if (expression[position] == '(') {
            count++;
        }
        if (expression[position] == ')') {
            count--;
        }
        position++;
    }
    if ((position == expression.length()) && count != 0) {
        assert(false);//not enough round brackets in expression
    }
    return position;
}

long double CalculateExpression(Expr* expr) {
    long double result = 0;
    switch (expr->op) {
    case Operations::NOP:
        result = expr->value;
        break;
    case Operations::ADD:
        result = CalculateExpression(expr->lExpr) + CalculateExpression(expr->rExpr);
        break;
    case Operations::SUB:
        result = CalculateExpression(expr->lExpr) + CalculateExpression(expr->rExpr);
        break;
    case Operations::MUL:
        result = CalculateExpression(expr->lExpr) * CalculateExpression(expr->rExpr);
        break;
    case Operations::DIV:
        result = CalculateExpression(expr->lExpr) / CalculateExpression(expr->rExpr);
        break;
    }
    return result;
}

long double Calculate(const std::string& expression) {
    Expr* expr = new Expr(expression); 
    const long double result = CalculateExpression(expr);
    return result;
}

//-((7 / 3) + (2 * (3 * 7))) / (9 - 8) done
//-(-2)/199 + (1*(2*(3*(4*5))))/100 +0.00001*(2*2 +4.01 - 8 -0.0*0.1)*100 done
