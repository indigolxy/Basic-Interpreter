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
    TokenScanner scanner(stmt);
    Expression *compound = nullptr;
    try {
        compound = parseExp(scanner);
        compound->eval(state);
        delete compound;
    }
    catch (const ErrorException &x) {
        delete compound;
        error("SYNTAX ERROR");
    }
}

void Statement_PRINT::execute(EvalState &state, Program &program) {
    TokenScanner scanner(stmt);
    Expression *printing = parseExp(scanner);
    std::cout << printing->eval(state);
    delete printing;
}

void Statement_INPUT::execute(EvalState &state, Program &program) {
    TokenScanner scanner(stmt);
    Expression *identifier = parseExp(scanner);
    std::cout << "?" << std::endl;
    Expression *value = parseExp(scanner);
    state.setValue(identifier->toString(),value->eval(state));
    delete identifier;
    delete value;
}

void Statement_RUN::execute(EvalState &state, Program &program) {
    program.run(state);
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
    TokenScanner scanner(stmt);
    Expression *line_num = parseExp(scanner);
    program.currentline = line_num->eval(state) - 1;
    delete line_num;
}

void Statement_IF::execute(EvalState &state, Program &program) {
    TokenScanner scanner(stmt);
    Expression *lhs = parseExp(scanner);
    std::string op = scanner.nextToken();
    Expression *rhs = parseExp(scanner);
    std::string then = scanner.nextToken();
    if (then != "THEN") error("SYNTAX ERROR");
    Expression *line_num = parseExp(scanner);

    if (op == "=") {
        if (lhs->eval(state) == rhs->eval(state)) program.currentline = line_num->eval(state) - 1;
    }
    else if (op == ">") {
        if (lhs->eval(state) > rhs->eval(state)) program.currentline = line_num->eval(state) - 1;
    }
    else if (op == "<") {
        if (lhs->eval(state) < rhs->eval(state)) program.currentline = line_num->eval(state) - 1;
    }

    delete lhs;
    delete rhs;
    delete line_num;
}

void Statement_REM::execute(EvalState &state, Program &program) {}

void Statement_END::execute(EvalState &state, Program &program) {
    program.currentline = -1;
}