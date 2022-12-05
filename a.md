tokenScanner:
setInput  hasMoreTokens & nextToken（获取下一个指令）
ignoreWhitespace  :  nextToken doesn't return whitespace
scanNumbers  :  nextToken returns the longest substring that can be interpreted as a real number
if not number, if word character return word
else return operator character
scanStrings : nextToken returns a single token consisting of all characters through the matching quotation mark.
The quotation marks are returned as part of the scanned token so that clients can differentiate strings from other token types.
addWordCharacters
addOperator
getTokenType
getStringValue

evalstate: 
存变量的
setValue 定义变量
getValue
bool isDefined
void Clear();
std::map<std::string, int> symbolTable;

error:
error(std::string message) : throw ErrorException(message);

program : todo
保存每一行和行号(string or statement)
addSourceLine
removeSourceLine
std::string getSourceLine(int lineNumber)
void setParsedStatement(int lineNumber, Statement *stmt);
Statement *getParsedStatement(int lineNumber);
int getFirstLineNumber();
int getNextLineNumber(int lineNumber);

statement : 
执行指令
完成 statment.hpp中的类的设计和实现，在 Basic.cpp 中通过调用 statment 及其子类的 execute 函数实现。
statement 中写每一种指令的派生类 以及它们的execute函数 (传入一个string 不包括指令本身)
let print input clear run list quit help

exp : 
存三种expression:identifier, int const, CompoundExp -- two expressions combined by an operator（实现多态：用一个基类的指针）
切片时：存在exp类中 
接下来对很多exp进行处理，对identifier: 到evalstate中获取值或赋值

parser : todo
operator 优先级 not operator : 0 
= : 1
+- : 2
*/ : 3
Expression *readE(TokenScanner &scanner, int prec = 0);The prec argument is optional and defaults to 0, which means that the function reads the entire expression.
Expression *readT(TokenScanner &scanner);
Expression *parseExp(TokenScanner &scanner);





basic main
如果是program：丢入program中不执行 （把数字去掉
不是program：调用execute
注意error

program
list(): lists the steps in the program in numerical sequence.
program实现：一个map存行号和statement
执行：map按行号排序，按行号顺序执行，依次调用statement 的execute函数 
run ： 执行行号最小的一行
rem：加入program（要list 但execute为空）

statement : rem if goto 
