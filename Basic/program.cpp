/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() : currentline(0) {}

Program::~Program() {
    for (int iter : program_set) {
        delete program_map[iter];
    }
}

void Program::clear() {
    for (int iter : program_set) {
        delete program_map[iter];
    }
    program_map.clear();
    program_set.clear();
    sourceline_map.clear();
    currentline = 0;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if (program_set.count(lineNumber) == 0) program_set.insert(lineNumber);
    else delete program_map[lineNumber];
    program_map[lineNumber] = stmt;
}


Statement *Program::getParsedStatement(int lineNumber) {
    return program_map[lineNumber];
}


int Program::getFirstLineNumber() {
    return *(program_set.begin());
}

int Program::getNextLineNumber(int lineNumber) {
    auto iter = program_set.upper_bound(lineNumber);
    if (iter != program_set.end()) return *(program_set.upper_bound(lineNumber));
    else return -1;
}

void Program::run(EvalState &State) {
    currentline = getFirstLineNumber();
    while (true) {
        int preline = currentline;
        program_map[currentline]->execute(State,*this);
        if (currentline == -1) break; // END
        else if (currentline != preline) { // goto or if-then
            if (program_set.find(currentline) != program_set.end()) continue;
            else error("LINE NUMBER ERROR");
        }
        else currentline = getNextLineNumber(currentline);
        if (currentline == -1) break; // last line
    }
}

void Program::list() {
    for (int iter : program_set) {
        std::cout << sourceline_map[iter] << std::endl;
    }
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    sourceline_map[lineNumber] = line;
}

void Program::removeLine(int lineNumber) {
    sourceline_map.erase(lineNumber);
    delete program_map[lineNumber];
    program_map.erase(lineNumber);
    program_set.erase(lineNumber);
}

std::string Program::getSourceLine(int lineNumber) {
    return sourceline_map[lineNumber];
}