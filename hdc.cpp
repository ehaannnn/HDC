#include "hdc.h"
const int INDENT_LEVEL = 4;
int forCount = 0;
int ifCount = 0;
int whileCount = 0;

SubProgram::SubProgram(Program *prog1, Program *prog2) {
	this->prog1 = prog1;
	this->prog2 = prog2;
}
void SubProgram::setScope(char *scope) {
	this->scope = strdup(scope);
	this->prog1->setScope(scope);
	this->prog2->setScope(scope);
}

void SubProgram::print(int lmargin) {
	this->prog1->print(lmargin+INDENT_LEVEL);
	this->prog2->print(lmargin+INDENT_LEVEL);
}
void SubProgram::addSymbol() {
	this->prog1->addSymbol();
	this->prog2->addSymbol();
}
void SubProgram::code(FILE *out) {
	prog1->code(out);
	prog2->code(out);
}
void SubProgram::codeL(FILE *out) {
	;
}
void SubProgram::codeR(FILE *out) {
	;
}

Function::Function(Program *type, Program *id, Program *stmtList, Program *funParam) {
	this->type = type;
	this->id = id;
	this->stmtList = stmtList;
	this->funParam = funParam;
}
Function::Function(Program *type, Program *id, Program *stmtList) {
	this->type = type;
	this->id = id;
	this->stmtList = stmtList;
	this->funParam = NULL;
}
void Function::setScope(char *scope) {
	this->scope = strdup(((Id*)id)->getId());
	this->type->setScope(this->scope);
	this->id->setScope(this->scope);
	if (funParam!=NULL) this->funParam->setScope(this->scope);
	this->stmtList->setScope(this->scope);
}
void Function::print(int lmargin) {
	printf("%s function\n",((Id*)id)->getId());
	this->type->print(lmargin+INDENT_LEVEL);
	this->id->print(lmargin+INDENT_LEVEL);
	if (funParam!=NULL) this->funParam->print(lmargin+INDENT_LEVEL);
	this->stmtList->print(lmargin+INDENT_LEVEL);
}
void Function::addSymbol() {
	this->type->addSymbol();
	this->id->addSymbol();
	if (funParam!=NULL) this->funParam->addSymbol();
	this->stmtList->addSymbol();	
}

void Function::code(FILE *out) {
	//numOfParam = countNumOfParam();
	char* n = ((Id*)id)->getId();
	fprintf(out,"%s: ssp %d\n",scope,localSize[n]+2);
	stmtList->code(out);
}

void Function::codeL(FILE *out) {
	;
}
void Function::codeR(FILE *out) {
	;
}
int Function::countNumOfParam() {
	int count = 0;
	if (funParam!=NULL) {
		count = ((FunParam*)funParam)->countNumOfParam();
	}
	else {
		count = 0;
	}
	return count;
}
MainFunction::MainFunction(Program *stmtList) {
	this->stmtList = stmtList;
}
void MainFunction::setScope(char *scope) {
	this->scope = strdup("main");
	this->stmtList->setScope(this->scope);
}
void MainFunction::print(int lmargin) {
	printf("main function\n");
	this->stmtList->print(lmargin+INDENT_LEVEL);
}
void MainFunction::addSymbol() {
	this->stmtList->addSymbol();
}
void MainFunction::code(FILE *out) {
	fprintf(out,"main: ssp %d\n",localSize["main"]);
	stmtList->code(out);
}

void MainFunction::codeL(FILE *out) {
	;
}
void MainFunction::codeR(FILE *out) {
	;
}

Statement::Statement(Program *stmt) {
	this->stmt = stmt;
	this->stmtList = NULL;
}
Statement::Statement(Program *stmt, Program *stmtList) {
	this->stmt = stmt;
	this->stmtList = stmtList;
}
void Statement::setScope(char *scope) {
	this->scope = strdup(scope);
	stmt->setScope(this->scope);;
	if (stmtList!=NULL) stmtList->setScope(this->scope);;
}
void Statement::print(int lmargin) {
	indent(lmargin);
	printf("statement\n");
	stmt->print(lmargin+INDENT_LEVEL);
	if (stmtList!=NULL) stmtList->print(lmargin);
}
void Statement::addSymbol() {
	stmt->addSymbol();
	if (stmtList!=NULL) stmtList->addSymbol();
}
void Statement::code(FILE *out) {
	stmt->code(out);
	if (stmtList!=NULL) stmtList->code(out);
}

void Statement::codeL(FILE *out) {
	;
}
void Statement::codeR(FILE *out) {
	;
}


IOStmt::IOStmt(Program *IO,char *io) {
	this->IO = IO;
	if (!strcmp(io,"INTIN")) tag = INTIN;
	else if (!strcmp(io,"INTOUT")) tag = INTOUT;
	else if (!strcmp(io,"CHARIN")) tag = CHARIN;
	else if (!strcmp(io,"CHAROUT")) tag = CHAROUT;
}

void IOStmt::setScope(char *scope) {
	this->scope = strdup(scope);
	IO->setScope(this->scope);
}
void IOStmt::print(int lmargin) {
	indent(lmargin);
	printf("IOStmt\n");
	IO->print(lmargin+INDENT_LEVEL);
}
void IOStmt::addSymbol() {
	IO->addSymbol();
}
void IOStmt::code(FILE *out) {
	switch (tag) {
	case INTIN: {
			char *n = strdup(((Var*)IO)->getId());
			fprintf(out,"lda %d\n",symbolTable[{n,scope}].first+1);
			fprintf(out,"in\n");
			fprintf(out,"sto\n");
			break;
		}
	case INTOUT:
		IO->code(out);
		break;
	case CHARIN:
		break;
	case CHAROUT:
		break;
	}
}

void IOStmt::codeL(FILE *out) {
	;
}
void IOStmt::codeR(FILE *out) {
	;
}

PrintList::PrintList(Program *exp,Program *next) {
	this->exp = exp;
	if (next!=NULL) this->next = next;
	else this->next = NULL;
}

void PrintList::setScope(char *scope) {
	this->scope = strdup(scope);
	exp->setScope(this->scope);
	if (next!=NULL) next->setScope(this->scope);
}

void PrintList::print(int lmargin) {
	indent(lmargin);
	printf("PrintList\n");
	exp->print(lmargin+INDENT_LEVEL);
	if (next!=NULL) next->print(lmargin+INDENT_LEVEL);
}
void PrintList::addSymbol() {
	exp->addSymbol();
	if (next!=NULL) next->addSymbol();
}
void PrintList::code(FILE *out) {
	exp->codeR(out);
	fprintf(out,"out\n");
	fprintf(out,"\\n\n");
	fprintf(out,"outc\n");
	if (next!=NULL) {
		next->code(out);
		//fprintf(out,"out\n");
	}
}

void PrintList::codeL(FILE *out) {
	;
}
void PrintList::codeR(FILE *out) {
	;
}



BinExpression::BinExpression(char *op, Program *left,Program *right) {
	this->op = strdup(op);
	this->left = left;
	this->right = right;
	if (!strcmp(op,"+")) {
		this->tag = PLUS;
	}
	else if (!strcmp(op,"-")) {
		this->tag = MINUS;
	}
	else if (!strcmp(op,"*")) {
		this->tag = MUL;	
	}
	else if (!strcmp(op,"/")) {
		this->tag = DIV;	
	}
	else if (!strcmp(op,"%")) {
		this->tag = REM;	
	}
	else if (!strcmp(op,"<<")) {
		this->tag = SHIFTL;	
	}
	else if (!strcmp(op,">>")) {
		this->tag = SHIFTR;	
	}
	else if (!strcmp(op,"<")) {
		this->tag = LESS;	
	}
	else if (!strcmp(op,">")) {
		this->tag = GRET;	
	}
	else if (!strcmp(op,"<=")) {
		this->tag = LESSEQ;	
	}
	else if (!strcmp(op,">=")) {
		this->tag = GRETEQ;	
	}
	else if (!strcmp(op,"==")) {
		this->tag = EQUAL;	
	}
	else if (!strcmp(op,"!=")) {
		this->tag = NEQUAL;	
	}
	else if (!strcmp(op,"&&")) {
		this->tag = LAND;
	}
	else if (!strcmp(op,"||")) {
		this->tag = LOR;	
	}
	else if (!strcmp(op,"&")) {
		this->tag = BAND;
	}
	else if (!strcmp(op,"|")) {
		this->tag = BOR;	
	}
	else if (!strcmp(op,"^")) {
		this->tag = XOR;
	}
}

void BinExpression::setScope(char *scope) {
	this->scope = strdup(scope);
	this->left->setScope(this->scope);
	this->right->setScope(this->scope);
}

void BinExpression::print(int lmargin) {
	indent(lmargin);
	printf("Op(%s)\n",this->op);
	this->left->print(lmargin+INDENT_LEVEL);
	this->right->print(lmargin+INDENT_LEVEL);
}
void BinExpression::addSymbol() {
	this->left->addSymbol();
	this->right->addSymbol();
}

void BinExpression::code(FILE *out) {
	this->left->codeR(out);
	this->right->codeR(out);
	switch (tag) {
	case PLUS:
		fprintf(out,"add\n");
		break;
	case MINUS:
		fprintf(out,"sub\n");
		break;
	case MUL:
		fprintf(out,"mul\n");
		break;
	case DIV:
		fprintf(out,"div\n");
		break;
	case REM:
		this->left->codeR(out);
		this->right->codeR(out);
		fprintf(out,"div\n");
		fprintf(out,"mul\n");
		fprintf(out,"sub\n");
		break;
	case SHIFTL:
		fprintf(out,"\n");
		break;
	case SHIFTR:
		fprintf(out,"\n");
		break;
	case LESS:
		fprintf(out,"les\n");
		break;
	case GRET:
		fprintf(out,"grt\n");
		break;
	case LESSEQ:
		fprintf(out,"leq\n");
		break;
	case GRETEQ:
		fprintf(out,"geq\n");
		break;
	case EQUAL:
		fprintf(out,"equ\n");
		break;
	case NEQUAL:
		fprintf(out,"neq\n");
		break;
	case LAND:
		fprintf(out,"and\n");
		break;
	case LOR:
		fprintf(out,"or\n");
		break;
	case BAND:

		break;
	case BOR:
		break;
	case XOR:
		break;
	}

}

void BinExpression::codeL(FILE *out) {
	;
}

void BinExpression::codeR(FILE *out) {
	this->left->codeR(out);
	this->right->codeR(out);
	switch (tag) {
	case PLUS:
		fprintf(out,"add\n");
		break;
	case MINUS:
		fprintf(out,"sub\n");
		break;
	case MUL:
		fprintf(out,"mul\n");
		break;
	case DIV:
		fprintf(out,"div\n");
		break;
	case REM:
		this->left->codeR(out);
		this->right->codeR(out);
		fprintf(out,"div\n");
		fprintf(out,"mul\n");
		fprintf(out,"sub\n");
		break;
	case SHIFTL:
		fprintf(out,"\n");
		break;
	case SHIFTR:
		fprintf(out,"\n");
		break;
	case LESS:
		fprintf(out,"les\n");
		break;
	case GRET:
		fprintf(out,"grt\n");
		break;
	case LESSEQ:
		fprintf(out,"leq\n");
		break;
	case GRETEQ:
		fprintf(out,"geq\n");
		break;
	case EQUAL:
		fprintf(out,"equ\n");
		break;
	case NEQUAL:
		fprintf(out,"neq\n");
		break;
	}
}

UnaryExpression::UnaryExpression(char *op, Program *son) {
	this->op = strdup(op);
	this->son = son;
	if (!strcmp(op,"-")) {
		this->tag = NEG;
	}
	else if (!strcmp(op,"++")) {
		this->tag = INC;
	}
	else if (!strcmp(op,"--")) {
		this->tag = DEC;	
	}
}
void UnaryExpression::setScope(char *scope) {
	this->scope = strdup(scope);
	this->son->setScope(this->scope);
}
void UnaryExpression::print(int lmargin) {
	indent(lmargin);
	printf("Op(%s)\n",this->op);
	this->son->print(lmargin+INDENT_LEVEL);
}
void UnaryExpression::addSymbol() {
	this->son->addSymbol();
}
void UnaryExpression::code(FILE *out) {	
	switch (tag) {
	case NEG:
		son->codeR(out);
		fprintf(out,"neg\n");
		break;
	case INC:
		son->codeL(out);
		son->codeR(out);
		fprintf(out,"ldc 1\n");
		fprintf(out,"add\n");
		fprintf(out,"sto\n");
		break;
	case DEC:
		son->codeL(out);
		son->codeR(out);
		fprintf(out,"ldc 1\n");
		fprintf(out,"sub\n");
		fprintf(out,"sto\n");
		break;
	}
}

void UnaryExpression::codeL(FILE *out) {
	;
}
void UnaryExpression::codeR(FILE *out) {	
	switch (tag) {
	case NEG:
		son->codeR(out);
		fprintf(out,"neg\n");
		break;
	case INC:
		son->codeL(out);
		son->codeR(out);
		fprintf(out,"ldc 1\n");
		fprintf(out,"add\n");
		fprintf(out,"sto\n");
		break;
	case DEC:
		son->codeL(out);
		son->codeR(out);
		fprintf(out,"ldc 1\n");
		fprintf(out,"sub\n");
		fprintf(out,"sto\n");
		break;
	}
}

AssignExpression::AssignExpression(char *op, Program *left, Program *right) {
	this->op = strdup(op);
	this->left = left;
	this->right = right;
	if (!strcmp(op,"=")) {
		this->tag = ASSIGN;
	}
	else if (!strcmp(op,"+=")) {
		this->tag = PLUSASSIGN;
	}
	else if (!strcmp(op,"-=")) {
		this->tag = MINUSASSIGN;	
	}
	else if (!strcmp(op,"*=")) {
		this->tag = MULASSIGN;	
	}
	else if (!strcmp(op,"/=")) {
		this->tag = DIVASSIGN;	
	}
	else if (!strcmp(op,"%=")) {
		this->tag = REMASSIGN;	
	}

}
void AssignExpression::setScope(char *scope) {
	this->scope = strdup(scope);
	this->left->setScope(this->scope);
	this->right->setScope(this->scope);
}
void AssignExpression::print(int lmargin) {
	indent(lmargin);
	printf("Op(%s)\n",this->op);
	this->left->print(lmargin+INDENT_LEVEL);
	this->right->print(lmargin+INDENT_LEVEL);
}
void AssignExpression::addSymbol() {
	this->left->addSymbol();
	this->right->addSymbol();
}
void AssignExpression::code(FILE *out) {
	left->codeL(out);
	switch (tag) {
	case ASSIGN:
		right->codeR(out);
		fprintf(out,"sto\n");
		break;
	case PLUSASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "add\n");
		fprintf(out,"sto\n");
		break;
	case MINUSASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "sub\n");
		fprintf(out,"sto\n");
		break;
	case MULASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "mul\n");
		fprintf(out,"sto\n");
		break;
	case DIVASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "div\n");
		fprintf(out,"sto\n");
		break;
	case REMASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out,"div\n");
		fprintf(out,"mul\n");
		fprintf(out,"sub\n");
		fprintf(out,"sto\n");
		break;
	}
	
}

void AssignExpression::codeL(FILE *out) {
	;
}
void AssignExpression::codeR(FILE *out) {
	left->codeL(out);
	char *n = ((Id*)left)->getId();
	switch (tag) {
	case ASSIGN:
		right->codeR(out);
		fprintf(out,"sto\n");
		fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+1);
		break;
	case PLUSASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "add\n");
		fprintf(out,"sto\n");
		fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+1);
		break;
	case MINUSASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "sub\n");
		fprintf(out,"sto\n");
		fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+1);
		break;
	case MULASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "mul\n");
		fprintf(out,"sto\n");
		fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+1);
		break;
	case DIVASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out, "div\n");
		fprintf(out,"sto\n");
		fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+1);
		break;
	case REMASSIGN:
		left->codeR(out);
		right->codeR(out);
		fprintf(out,"div\n");
		fprintf(out,"mul\n");
		fprintf(out,"sub\n");
		fprintf(out,"sto\n");
		fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+1);
		break;
	}
}

IfStmt::IfStmt(Program *exp, Program *stmt1, Program *stmt2) {
	this->exp = exp;
	this->stmt1 = stmt1;
	this->stmt2 = stmt2;
}

IfStmt::IfStmt(Program *exp, Program *stmt1) {
	this->exp = exp;
	this->stmt1 = stmt1;
	this->stmt2 = NULL;
}
void IfStmt::setScope(char *scope) {
	this->scope = strdup(scope);
	this->exp->setScope(this->scope);
	this->stmt1->setScope(this->scope);
	if (this->stmt2!=NULL) this->stmt2->setScope(this->scope);
}
void IfStmt::print(int lmargin) {
	this->exp->print(lmargin+INDENT_LEVEL);
	this->stmt1->print(lmargin+INDENT_LEVEL);
	if (this->stmt2!=NULL) this->stmt2->print(lmargin+INDENT_LEVEL);
}
void IfStmt::addSymbol() {
	this->exp->addSymbol();
	this->stmt1->addSymbol();
	if (this->stmt2!=NULL) this->stmt2->addSymbol();
}
void IfStmt::code(FILE *out) {
	if (stmt2==NULL) {
		exp->codeR(out);
		fprintf(out,"fjp if%d\n",ifCount);
		stmt1->code(out);
		fprintf(out, "if%d: ",ifCount);
		ifCount++;
	}
	else {
		exp->codeR(out);
		fprintf(out,"fjp if%d\n",ifCount);
		stmt1->code(out);
		fprintf(out, "ujp if%d\n",ifCount);
		fprintf(out,"if%d: ",ifCount);
		stmt2->code(out);
		fprintf(out,"if%d: ",ifCount);
	}
}

void IfStmt::codeL(FILE *out) {
	;
}
void IfStmt::codeR(FILE *out) {
	;
}

VarDecl::VarDecl(Program *type, Program *id) {
	this->type = type;
	this->id = id;
	this->num = NULL;
}
VarDecl::VarDecl(Program *type, Program *id, Program *num) {
	this->type = type;
	this->id = id;
	this->num = num;
}

void VarDecl::setScope(char *scope) {
	this->scope = strdup(scope);
	this->type->setScope(this->scope);
	this->id->setScope(this->scope);
	if (num!=NULL) this->num->setScope(this->scope);
}
void VarDecl::print(int lmargin) {
	indent(lmargin);
	printf("variable declaration\n");
	this->type->print(lmargin+INDENT_LEVEL);
	this->id->print(lmargin+INDENT_LEVEL);
	if (num!=NULL) this->num->print(lmargin+INDENT_LEVEL);
}

void VarDecl::addSymbol() {
	char *t = ((Type*)type)->getType();
	char *n = ((Id*)id)->getId();
	if (symbolTable.find({n,scope})!=symbolTable.end()) {
		printf("error! %s is already use\n",n);
		exit(-1);
	}
	if (strcmp(scope,"main") && localSize[scope]==0) localSize[scope] = 2;
	
	if (num!=NULL) {
		int number = ((Num*)num)->getNum();
		symbolTable[{n,scope}] = make_pair(localSize[scope],t);
		arrSize[{n,scope}] = number;
		localSize[scope] += number;
	}
	else {
		symbolTable[{n,scope}] = make_pair(localSize[scope]++,t);
		arrSize[{n,scope}] = 1;
	}
}

void VarDecl::code(FILE *out) {
	;
}

void VarDecl::codeL(FILE *out) {
	char *t = ((Type*)type)->getType();
	char *n = ((Id*)id)->getId();
	fprintf(out,"lda %d\n",symbolTable[{n,scope}].first+1);
}
void VarDecl::codeR(FILE *out) {
	;
}

FunCall::FunCall(Program *id, Program *arglist) {
	this->id = id;
	this->arglist = arglist;
}
FunCall::FunCall(Program *id) {
	this->id = id;
	this->arglist = NULL;
}
void FunCall::setScope(char *scope) {
	this->scope = strdup(scope);
	this->id->setScope(this->scope);
	if (this->arglist!=NULL) this->arglist->setScope(this->scope);
}
void FunCall::print(int lmargin) {
	this->id->print(lmargin+INDENT_LEVEL);
	if (this->arglist!=NULL) this->arglist->print(lmargin+INDENT_LEVEL);
}
void FunCall::addSymbol() {
	this->id->addSymbol();
	if (this->arglist!=NULL) this->arglist->addSymbol();
}
void FunCall::code(FILE *out) {
	fprintf(out,"mst\n");
	numOfArg = countNumOfArg();
	char *n = ((Id*)id)->getId();
	if (this->arglist!=NULL) {
		arglist->codeR(out);
		fprintf(out,"cup %d %s\n",numOfArg,n);
	}
	else {
		fprintf(out,"cup 0 %s\n",n);
	}
}

void FunCall::codeL(FILE *out) {
	;
}
void FunCall::codeR(FILE *out) {
	fprintf(out,"mst\n");
	numOfArg = countNumOfArg();
	char *n = ((Id*)id)->getId();
	if (this->arglist!=NULL) {
		arglist->codeR(out);
		fprintf(out,"cup %d %s\n",numOfArg,n);
	}
	else {
		fprintf(out,"cup 0 %s\n",n);
	}
}

int FunCall::countNumOfArg() {
	int count = 0;
	if (this->arglist!=NULL) {
		count = ((ArgList*)arglist)->countNumOfArg();
	}
	else {
		count = 0;
	}
	return count;
}

ArgList::ArgList(Program *var, Program *next) {
	this->var = var;
	this->next = next;
}
ArgList::ArgList(Program *var) {
	this->var = var;
	this->next = NULL;
}
void ArgList::setScope(char *scope) {
	this->scope = strdup(scope);
	this->var->setScope(this->scope);
	if (this->next!=NULL) this->next->setScope(this->scope);
}
void ArgList::print(int lmargin) {
	this->var->print(lmargin+INDENT_LEVEL);
	if (this->next!=NULL) this->next->print(lmargin+INDENT_LEVEL);
}
void ArgList::addSymbol() {
	this->scope = strdup(scope);
	this->var->addSymbol();
	if (this->next!=NULL) this->next->addSymbol();
}
void ArgList::code(FILE *out) {
	;
}

void ArgList::codeL(FILE *out) {
	;
}
void ArgList::codeR(FILE *out) {
	var->codeR(out);
	if (next!=NULL) {
		next->codeR(out);
	}
}

int ArgList::countNumOfArg() {
	int count = 1;
	if (next!=NULL) {
		count += ((ArgList*)next)->countNumOfArg();
	}
	return count;
}



Type::Type(char *type, Program *vectorType) {
	this->type = strdup(type);
	this->vectorType = vectorType;
}

Type::Type(char *type) {
	this->type = strdup(type);
	this->vectorType = NULL;
}
void Type::setScope(char *scope) {
	this->scope = strdup(scope);
	if (vectorType!=NULL) this->vectorType->setScope(this->scope);
}
void Type::print(int lmargin) {
	indent(lmargin);
	printf("type(%s)\n",type);
	if (vectorType!=NULL) this->vectorType->print(lmargin+INDENT_LEVEL);
}
void Type::addSymbol() {
	if (vectorType!=NULL) this->vectorType->addSymbol();
}
void Type::code(FILE *out) {
	;
}

void Type::codeL(FILE *out) {
	;
}
void Type::codeR(FILE *out) {
	;
}

char* Type::getType() {
	return type;
}
Id::Id(char *id) {
	this->id = strdup(id);
}
void Id::setScope(char *scope) {
	this->scope = strdup(scope);
}
void Id::print(int lmargin) {
	indent(lmargin);
	printf("Id(%s)\n",this->id);
}
void Id::addSymbol() {
	;
}
void Id::code(FILE *out) {
	;
}
void Id::codeL(FILE *out) {
	fprintf(out,"lda %d\n",symbolTable[{id,scope}].first+1);
}
void Id::codeR(FILE *out) {
	fprintf(out,"lod %d\n",symbolTable[{id,scope}].first+1);
}
char* Id::getId() {
	return id;
}

Num::Num(int num) {
	this->num = num;
}
void Num::setScope(char *scope) {
	this->scope = strdup(scope);
}
void Num::print(int lmargin) {
	indent(lmargin);
	printf("INT(%d)\n",this->num);
}
void Num::addSymbol() {
	;
}
void Num::code(FILE *out) {
	;
}

void Num::codeL(FILE *out) {
	;
}
void Num::codeR(FILE *out) {
	fprintf(out,"ldc %d\n",num);
}
int Num::getNum() {
	return num;
}

Var::Var(Id *id, Program* exp) {
	this->id = id;
	this->varId = strdup(id->getId());
	this->exp = exp;
	this->num1 = NULL;
	this->num2 = NULL;
	this->num3 = NULL;
	this->exp1 = NULL;
	this->exp2 = NULL;
}

Var::Var(Id *id, Program *exp1, Program *exp2) {
	this->id = id;
	this->varId = strdup(id->getId());
	this->exp = NULL;
	this->num1 = NULL;
	this->num2 = NULL;
	this->num3 = NULL;
	this->exp1 = exp1;
	this->exp2 = exp2;
}

Var::Var(Id *id, Num *num1, Num *num2, Num *num3) {
	this->id = id;
	this->varId = strdup(id->getId());
	this->exp = NULL;
	this->num1 = num1;
	this->num2 = num2;
	this->num3 = num3;
	this->exp1 = NULL;
	this->exp2 = NULL;
}
void Var::setScope(char *scope) {
	this->scope = strdup(scope);
	if (id!=NULL) id->setScope(this->scope);
	
	if (exp !=NULL) exp->setScope(this->scope);
	if (num1 !=NULL) num1->setScope(this->scope);
	if (num2 !=NULL) num2->setScope(this->scope);
	if (num3 !=NULL) num3->setScope(this->scope);
	if (exp1 !=NULL) exp1->setScope(this->scope);
	if (exp2 !=NULL) exp2->setScope(this->scope);
}
void Var::print(int lmargin) {
	if (id!=NULL) id->print(lmargin+INDENT_LEVEL);

	if (exp !=NULL) exp->print(lmargin+INDENT_LEVEL);
	if (num1 !=NULL) num1->print(lmargin+INDENT_LEVEL);
	if (num2 !=NULL) num2->print(lmargin+INDENT_LEVEL);
	if (num3 !=NULL) num3->print(lmargin+INDENT_LEVEL);
	if (exp1 !=NULL) exp1->print(lmargin+INDENT_LEVEL);
	if (exp2 !=NULL) exp2->print(lmargin+INDENT_LEVEL);
}

void Var::addSymbol() {
	if (id!=NULL) id->addSymbol();
	if (exp !=NULL) exp->addSymbol();
	if (num1 !=NULL) num1->addSymbol();
	if (num2 !=NULL) num2->addSymbol();
	if (num3 !=NULL) num3->addSymbol();
	if (exp1 !=NULL) exp1->addSymbol();
	if (exp2 !=NULL) exp2->addSymbol();
}
void Var::code(FILE *out) {
	;
}

void Var::codeL(FILE *out) {
	if (exp!=NULL) {	//ID [var or num];
		id->codeL(out);
		exp->codeR(out);
		fprintf(out,"add\n");
	}
	else if (exp1!=NULL) {

	}
}
void Var::codeR(FILE *out) {
	if (exp!=NULL) {	//ID [var or num];
		id->codeL(out);
		exp->codeR(out);
		fprintf(out,"add\n");
		fprintf(out,"ind\n");
	}
	else if (id!=NULL) id->codeL(out);
}

char* Var::getId() {
	return varId;
}

ForExp::ForExp(Program *exp1,Program *exp2,Program *exp3,Program *stmtList) {
	this->exp1 = exp1;
	this->exp2 = exp2;
	this->exp3 = exp3;
	this->stmtList = stmtList;
	this->var = NULL;
}
ForExp::ForExp(Program *exp1,Program *var, Program *stmtList) {
	this->exp1 = exp1;
	this->exp2 = NULL;
	this->exp3 = NULL;
	this->stmtList = stmtList;
	this->var = var;
}
void ForExp::setScope(char *scope) {
	this->scope = strdup(scope);
	if (exp1 !=NULL) exp1->setScope(this->scope);
	if (exp2 != NULL) exp2->setScope(this->scope);
	if (exp3 !=NULL) exp3->setScope(this->scope);
	if (var !=NULL) var->setScope(this->scope);
	if (stmtList !=NULL) stmtList->setScope(this->scope);
}
void ForExp::print(int lmargin) {
	if (exp1 !=NULL) exp1->print(lmargin+INDENT_LEVEL);
	if (exp2 != NULL) exp2->print(lmargin+INDENT_LEVEL);
	if (exp3 !=NULL) exp3->print(lmargin+INDENT_LEVEL);
	if (var !=NULL) var->print(lmargin+INDENT_LEVEL);
	if (stmtList !=NULL) stmtList->print(lmargin+INDENT_LEVEL);
}
void ForExp::addSymbol() {
	if (exp1 !=NULL) exp1->addSymbol();
	if (exp2 != NULL) exp2->addSymbol();
	if (exp3 !=NULL) exp3->addSymbol();
	if (var !=NULL) var->addSymbol();
	if (stmtList !=NULL) stmtList->addSymbol();
}

void ForExp::code(FILE *out) {
	if (var==NULL) {	//
		exp1->code(out);
		fprintf(out,"for%d: ",forCount);
		exp2->codeR(out);
		fprintf(out,"fjp for%d\n",forCount+1);
		stmtList->code(out);
		exp3->codeR(out);
		fprintf(out,"ujp for%d\n",forCount);
		fprintf(out,"for%d: ",forCount+1);
		forCount += 2;
	}
	else {	//for in loop
		char *n = strdup(((Var*)var)->getId());
		int limit = arrSize[{n,scope}];

		for (int i = 0; i < limit; ++i) {
			exp1->codeL(out);
			fprintf(out,"lod %d\n",symbolTable[{n,scope}].first+i+1);
			fprintf(out,"sto\n");
			stmtList->code(out);
		}
	}
}

void ForExp::codeL(FILE *out) {
	;
}
void ForExp::codeR(FILE *out) {
	;
}
WhileExp::WhileExp(Program *exp,Program *stmtList) {
	this->exp = exp;
	this->stmtList = stmtList;
}
void WhileExp::setScope(char *scope) {
	this->scope = strdup(scope);
	exp->setScope(this->scope);
	stmtList->setScope(this->scope);
}
void WhileExp::print(int lmargin) {
	exp->print(lmargin+INDENT_LEVEL);
	stmtList->print(lmargin+INDENT_LEVEL);
}
void WhileExp::addSymbol() {
	exp->addSymbol();
	stmtList->addSymbol();
}
void WhileExp::code(FILE *out) {
	fprintf(out,"while%d: ",whileCount);
	exp->codeR(out);
	fprintf(out, "fjp while%d\n",whileCount+1);
	stmtList->code(out);
	fprintf(out,"ujp while%d\n",whileCount);
	fprintf(out, "while%d: ", whileCount+1);
	whileCount+=1;
}

void WhileExp::codeL(FILE *out) {
	;
}
void WhileExp::codeR(FILE *out) {
	;
}
FunParam::FunParam(Program *param,Program *funParam) {
	this->param = param;
	this->funParam = NULL;
	if (funParam!=NULL) this->funParam = funParam;
}
void FunParam::setScope(char *scope) {
	this->scope = strdup(scope);
	param->setScope(this->scope);
	if (funParam!=NULL) funParam->setScope(this->scope);
}
void FunParam::print(int lmargin) {
	indent(lmargin);
	printf("paramList\n");
	param->print(lmargin+INDENT_LEVEL);
	if (funParam!=NULL) funParam->print(lmargin+INDENT_LEVEL);
}
void FunParam::addSymbol() {
	param->addSymbol();
	if (funParam!=NULL) funParam->addSymbol();
}
void FunParam::code(FILE *out) {
	;
}

void FunParam::codeL(FILE *out) {
	;
}
void FunParam::codeR(FILE *out) {
	;
}
int FunParam::countNumOfParam() {
	int count = 1;
	if (funParam!=NULL) {
		count += ((FunParam*)funParam)->countNumOfParam();
	}
	return count;
}
Param::Param(Program *type,Program *id) {
	this->type = type;
	this->id = id;
}
void Param::setScope(char *scope) {
	this->scope = strdup(scope);
	type->setScope(this->scope);
	id->setScope(this->scope);
}

void Param::print(int lmargin) {
	indent(lmargin);
	printf("param\n");
	type->print(lmargin+INDENT_LEVEL);
	id->print(lmargin+INDENT_LEVEL);
}

void Param::addSymbol() {
	char *t = ((Type*)type)->getType();
	char *n = ((Id*)id)->getId();
	if (symbolTable.find({n,scope})!=symbolTable.end()) {
		printf("error! %s is already use\n",n);
		exit(-1);
	}
	if (strcmp(scope,"main") && localSize[scope]==0) localSize[scope] = 2;
	symbolTable[{n,scope}] = make_pair(localSize[scope]++,t);
}

void Param::code(FILE *out) {
	;
}

void Param::codeL(FILE *out) {
	;
}
void Param::codeR(FILE *out) {
	;
}
/*
DotOp::DotOp(char *op,Program *num) {
	this->op = strdup(op);
	this->num = num;
}
DotOp::DotOp(char *op) {
	this->op = strdup(op);
	this->num = NULL;
}
void DotOp::setScope(char *scope) {
	this->scope = strdup(scope);
	if (num!=NULL) num->setScope(this->scope);
}
void DotOp::print(int lmargin) {
	indent(lmargin);
	printf("dotOp(%s)\n",op);
	if (num!=NULL) num->print(lmargin+INDENT_LEVEL);
}

void DotOp::addSymbol() {
	;
}
void DotOp::code(FILE *out) {
	;
}

void DotOp::codeL(FILE *out) {
	;
}
void DotOp::codeR(FILE *out) {
	;
}
*/

ReturnExp::ReturnExp() {
	this->exp = NULL;
}
ReturnExp::ReturnExp(Program *exp) {
	this->exp =exp;
}
void ReturnExp::setScope(char *scope) {
	this->scope = strdup(scope);
	if (exp!=NULL) exp->setScope(this->scope);
}
void ReturnExp::print(int lmargin) {
	indent(lmargin);
	printf("return statement\n");
	if (exp!=NULL) exp->print(lmargin+INDENT_LEVEL);
}
void ReturnExp::addSymbol() {
	;
}
void ReturnExp::code(FILE *out) {
	if (strcmp(scope,"main")) {
		exp->codeR(out);
		fprintf(out,"str 0\n");
		fprintf(out,"retf\n");
	}
}

void ReturnExp::codeL(FILE *out) {
	;
}
void ReturnExp::codeR(FILE *out) {
	;
}
void printTree(Program *root)
{
    if (root == NULL) {
    	printf("NULL\n");
    	return;
    }
    root->print(0);
}

void indent(int n)
{
    if (n > 0) {
        printf(" ");
        indent(--n);
    }
}

