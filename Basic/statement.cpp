/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

void Statement_LET::execute(EvalState &state, Program &program) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(stmt);
    Expression *compound = nullptr;
    try {
        compound = parseExp(scanner);
        compound->eval(state);
        delete compound;
    }
    catch (const ErrorException &x) {
        delete compound;
        error(x.getMessage());
    }
}

void Statement_PRINT::execute(EvalState &state, Program &program) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(stmt);

    Expression *printing = nullptr;
    try {
        printing = parseExp(scanner);
        std::cout << printing->eval(state) << std::endl;
        delete printing;
    }
    catch (const ErrorException &x) {
        delete printing;
        error(x.getMessage());
    }
}

void Statement_INPUT::execute(EvalState &state, Program &program) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(stmt);
    Expression *identifier = parseExp(scanner);

    while (true) {
        std::cout << ' ' << "?" << ' ';
        std::string input;
        getline(std::cin, input);
        bool isnegative = false;
        if (input[0] == '-') {
            input = input.substr(1);
            isnegative = true;
        }
        scanner.ignoreWhitespace();
//        scanner.scanNumbers();
        scanner.setInput(input);
        Expression *value = nullptr;
        try {
            value = parseExp(scanner);
        }
        catch (const ErrorException &x) {
            delete value;
            std::cout << "INVALID NUMBER" << std::endl;
            continue;
        }
        if (value->getType() != CONSTANT) {
            delete value;
            std::cout << "INVALID NUMBER" << std::endl;
            continue;
        }
        else {
            state.setValue(identifier->toString(),(isnegative) ? (0 - value->eval(state)) : value->eval(state));
            delete value;
            break;
        }
    }
    delete identifier;
}

void Statement_RUN::execute(EvalState &state, Program &program) {
    try {
        program.run(state);
    }
    catch (const ErrorException &x) {
        error(x.getMessage());
    }
}

void Statement_LIST::execute(EvalState &state, Program &program) {
    program.list();
}

void Statement_CLEAR::execute(EvalState &state, Program &program) {
    program.clear();
    state.Clear();
}

void Statement_QUIT::execute(EvalState &state, Program &program) {
    exit(0);
}

void Statement_HELP::execute(EvalState &state, Program &program) {
    std::cout << "Yet another basic interpreter" << std::endl;
}

void Statement_GOTO::execute(EvalState &state, Program &program) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(stmt);
    Expression *line_num = parseExp(scanner);
    program.currentline = line_num->eval(state);
    delete line_num;
}

void Statement_IF::execute(EvalState &state, Program &program) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(stmt);
    Expression *lhs = readE(scanner,1);
    std::string op = scanner.nextToken();
    Expression *rhs = readE(scanner,1);
    std::string then = scanner.nextToken();
    if (then != "THEN") error("SYNTAX ERROR");
    Expression *line_num = parseExp(scanner);

    if (op == "=") {
        if (lhs->eval(state) == rhs->eval(state)) program.currentline = line_num->eval(state);
    }
    else if (op == ">") {
        if (lhs->eval(state) > rhs->eval(state)) program.currentline = line_num->eval(state);
    }
    else if (op == "<") {
        if (lhs->eval(state) < rhs->eval(state)) program.currentline = line_num->eval(state);
    }

    delete lhs;
    delete rhs;
    delete line_num;
}

void Statement_REM::execute(EvalState &state, Program &program) {}

void Statement_END::execute(EvalState &state, Program &program) {
    program.currentline = -1;
}