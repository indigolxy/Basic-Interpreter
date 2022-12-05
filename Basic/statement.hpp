/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <memory>
#include <sstream>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include"parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {
public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();
    Statement(std::string str) : stmt(str) {}

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state, Program &program) = 0;

protected:
    std::string stmt;
};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

// let print input run list clear help quit goto if rem end

class Statement_LET : public Statement {
public:
    Statement_LET(std::string str) : Statement(str) {}
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_PRINT : public Statement {
public:
    Statement_PRINT(std::string str) : Statement(str) {}
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_INPUT : public Statement {
public:
    Statement_INPUT(std::string str) : Statement(str) {}
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_RUN : public Statement {
public:
    Statement_RUN() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_LIST : public Statement {
public:
    Statement_LIST() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_CLEAR : public Statement {
public:
    Statement_CLEAR() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_QUIT : public Statement {
public:
    Statement_QUIT() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_HELP : public Statement {
public:
    Statement_HELP() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_GOTO : public Statement {
public:
    Statement_GOTO(std::string str) : Statement(str) {}
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_IF : public Statement {
public:
    Statement_IF(std::string str) : Statement(str) {}
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_REM : public Statement {
public:
    Statement_REM() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

class Statement_END : public Statement {
public:
    Statement_END() = default;
    virtual void execute(EvalState &state, Program &program) override;
};

#endif
