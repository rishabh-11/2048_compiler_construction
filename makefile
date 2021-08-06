-output: assignment.tab.cpp lex.yy.cpp assignment.h assignment.cpp
	g++ assignment.cpp assignment.tab.cpp lex.yy.cpp -o output

-lex.yy.cpp: assignment.tab.hpp
	flex -olex.yy.cpp assignment.lpp

-assignment.tab.hpp: assignment.ypp
	bison -d assignment.ypp

-assignment.tab.cpp: assignment.ypp
	bison -d assignment.ypp
