/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);
Statement *stringToStatement(std::string line);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    // a BASIC program
    if (line[0] >= '0' && line[0] <= '9') {
        std::string num = scanner.nextToken();
        int line_num = 0;
        for (char i: num) {
            line_num *= 10;
            line_num += i - '0';
        }

        if (!scanner.hasMoreTokens()) program.removeLine(line_num);
        else {
            program.addSourceLine(line_num, line);
            // remove num from line
            for (int i = 0; i < line.length() - num.length() - 1; ++i) {
                line[i] = line[i + num.length() + 1];
            }
            line = line.substr(0,line.length() - num.length() - 1);
            Statement *stmt = stringToStatement(line);
            program.setParsedStatement(line_num, stmt);
//            delete stmt;
        }
    }

    // an immediately executed BASIC program
    else {
        Statement *stmt = stringToStatement(line);
        try {
            stmt->execute(state, program);
            delete stmt;
        }
        catch(const ErrorException &x) {
            delete stmt;
            error(x.getMessage());
        }
    }
}



Statement *stringToStatement(std::string line) {
    Statement *stmt;
    TokenScanner scanner(line);
    std::string separator = scanner.nextToken();

    if (separator == "RUN") stmt = new Statement_RUN;
    else if (separator == "LIST") stmt  = new Statement_LIST;
    else if (separator == "CLEAR") stmt  = new Statement_CLEAR;
    else if (separator == "QUIT") stmt  = new Statement_QUIT;
    else if (separator == "HELP") stmt  = new Statement_HELP;
    else if (separator == "REM") stmt  = new Statement_REM;
    else if (separator == "END") stmt  = new Statement_END;
    else {
        // remove separator from line
        for (int i = 0;i < line.length() - separator.length() - 1;++i) {
            line[i] = line[i + separator.length() + 1];
        }
        line = line.substr(0,line.length() - separator.length() - 1);

        if (separator == "LET") stmt = new Statement_LET (line);
        else if (separator == "PRINT") stmt = new Statement_PRINT(line);
        else if (separator == "INPUT") stmt = new Statement_INPUT(line);
        else if (separator == "GOTO") stmt  = new Statement_GOTO(line);
        else if (separator == "IF") stmt  = new Statement_IF(line);
    }

    return stmt;
}

