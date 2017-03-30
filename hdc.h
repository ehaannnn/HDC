#include <cstdio>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

static map<pair<string,string>, pair<int,string> > symbolTable;
static map<string, int> localSize;
static map<pair<string,string>, int> arrSize;

class Program {
public:
	virtual void print(int lmargin) = 0;
	virtual void code(FILE *out) = 0;
	virtual void codeL(FILE *out) = 0;
	virtual void codeR(FILE *out) = 0;
	virtual void setScope(char* scope = NULL) = 0;
	virtual void addSymbol() = 0;
};

class SubProgram : public Program {
public:
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	SubProgram(Program *prog1, Program *prog2);
private:
	char *scope;
	Program *prog1;
	Program *prog2;
};

class Function : public Program {
public:
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	Function(Program *type, Program *id, Program *stmtList, Program *funParam);
	Function(Program *type, Program *id, Program *stmtList);
	int countNumOfParam();
private:
	char *scope;
	int numOfParam;
	Program *type;
	Program *id;
	Program *stmtList;
	Program *funParam;
};

class MainFunction : public Program {
public:
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	MainFunction(Program *stmtList);
private:
	char *scope;
	Program *stmtList;
};

class Statement : public Program {
public:
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	Statement(Program *stmt, Program *stmtList);
	Statement(Program *stmt);
private:
	char *scope;
	Program *stmt;
	Program *stmtList;
};
class IOStmt : public Program {
public:
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	IOStmt(Program *IO, char *io);
private:
	enum {INTIN,INTOUT,CHARIN,CHAROUT} tag;
	char *scope;
	Program *IO;
};

class PrintList : public Program {
public:
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	PrintList(Program *exp,Program *next=NULL);
private:
	char *scope;
	Program *exp;
	Program *next;
};
class BinExpression : public Program {
public:
	BinExpression(char *op, Program *left,Program *right);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	enum {PLUS, MINUS, MUL, DIV, REM, SHIFTL, SHIFTR, LESS,GRET, LESSEQ,GRETEQ,EQUAL,NEQUAL,LAND,LOR,BAND,BOR,XOR} tag;
	char *op;
	Program *left;
	Program *right;
};

class UnaryExpression : public Program {
public:
	UnaryExpression(char *op, Program *son);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	enum {NEG,INC,DEC} tag;
	char *scope;
	char *op;
	Program *son;
};

class AssignExpression : public Program {
public:
	AssignExpression(char *op, Program *left, Program *right);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	enum {ASSIGN,PLUSASSIGN,MINUSASSIGN,MULASSIGN,DIVASSIGN,REMASSIGN} tag;
	char *scope;
	char *op;
	Program *left;
	Program *right;
};

class IfStmt : public Program {
public:
	IfStmt(Program *exp, Program *stmt1, Program *stmt2);
	IfStmt(Program *exp, Program *stmt1);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	Program *exp;
	Program *stmt1;
	Program *stmt2;
};

class VarDecl : public Program {
public:
	VarDecl(Program *type, Program *id);
	VarDecl(Program *type, Program *id, Program *num);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	Program *type;
	Program *id;
	Program *num;
};

class FunCall : public Program {
public:
	FunCall(Program *id, Program *arglist);
	FunCall(Program *id);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	int countNumOfArg();
private:
	char *scope;
	int numOfArg;
	Program *id;
	Program *arglist;
};

class ArgList : public Program {
public:
	ArgList(Program *id, Program *next);
	ArgList(Program *id);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	int countNumOfArg();
private:
	char *scope;
	Program *var;
	Program *next;
};

class Type : public Program {
public:
	char* getType();
	Type(char *type,Program *vectorType);
	Type(char *type);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	char *type;
	Program *vectorType;
};

class Id : public Program {
public:
	Id(char *id);
	char* getId();
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	char *id;
};

class Num : public Program {
public:
	Num(int num);
	int getNum();
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	int num;
};
/*
class DotOp : public Program{
public:
	DotOp(char *op,Program *num);
	DotOp(char *op);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	char *op;
	Program *num;
};*/

class Var : public Program {
public:
	Var(Id *id, Program* exp);
	Var(Id *id, Program *exp1, Program *exp2);
	Var(Id *id, Num *num1, Num *num2, Num *num3);
	char *getId();
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	char *varId;
	Id *id;
	Program *exp;
	Num *num1;
	Num *num2;
	Num *num3;
	Program *exp1;
	Program *exp2;
};

class ForExp : public Program {
public:
	ForExp(Program *exp1,Program *exp2,Program *exp3,Program *stmtList);
	ForExp(Program *exp1,Program *var, Program *stmtList);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	Program *exp1;
	Program *exp2;
	Program *exp3;
	Program *stmtList;
	Program *var;
};

class WhileExp : public Program {
public:
	WhileExp(Program *exp,Program *stmtList);
	
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	Program *exp;
	Program *stmtList;
};
class FunParam : public Program {
public:
	FunParam(Program *param,Program *funParam = NULL);
	
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	int countNumOfParam();
private:
	char *scope;
	Program *param;
	Program *funParam;
};

class Param : public Program {
public:
	Param(Program *type,Program *id);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
	int countNumOfParam();
private:
	char *scope;
	Program *type;
	Program *id;
};
class ReturnExp : public Program {
public:
	ReturnExp();
	ReturnExp(Program *exp);
	virtual void print(int lmargin);
	virtual void setScope(char* scope = NULL);
	virtual void addSymbol();
	virtual void code(FILE *out);
	virtual void codeL(FILE *out);
	virtual void codeR(FILE *out);
private:
	char *scope;
	Program *exp;
};


void printTree(Program *root);
void indent(int n);
void addSymbol(char *name, Program *type);
void chkSymbol(Program *prog);