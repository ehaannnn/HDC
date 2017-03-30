Name : YI Hangyul, Lee Dong Ki
Student ID : 201124506, 201224494

Description

이 프로그램은 HDC언어를 기반으로 하는 AST 생성 프로그램이다.
HDC작성시 주의해야 할 것은 다음과 같다.

모든 문장의 끝엔 ;을 붙인다.
ex) if ( expression ) { ... };
변수이름은 최대 7자리 까지 가능하다.

How to Build

1. flex hdc.l
2. bison -dy hdc.y
3. g++ lex.yy.c y.tab.c hdc.cpp

How to Use

a < Progx.txt

where x is 1 or 2 or 3 or 4
(ex: a < Prog0.txt)