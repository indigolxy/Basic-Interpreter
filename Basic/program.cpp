/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.hpp"
#include "statement.hpp"



Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    // Replace this stub with your own code
    line_getter.clear();
    line_num_list.clear();
    stmt_storage.clear();
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    // Replace this stub with your own code
    //todo
}

void Program::removeSourceLine(int lineNumber) {
    // Replace this stub with your own code
    //todo
}

std::string Program::getSourceLine(int lineNumber) {
    // Replace this stub with your own code
    //todo
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
    //todo
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
    if (line_num_list.find(lineNumber) != line_num_list.end()) {
        return stmt_storage[lineNumber];
    } else return nullptr;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    // Replace this stub with your own code
    //todo
}

int Program::getNextLineNumber(int lineNumber) {
    // Replace this stub with your own code
    //todo
}

//more func to add
//todo


