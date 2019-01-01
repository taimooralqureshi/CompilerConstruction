#pragma once
#ifndef SYNTAXANDSEMENTICANALYZER_H
#define SYNTAXANDSEMENTICANALYZER_H
#include "Token.h"
#include <vector>
using namespace std;


class SyntaxAndSementicAnalyzer {
public:
	SyntaxAndSementicAnalyzer(vector<Token> tl);
	~SyntaxAndSementicAnalyzer();

	
	//start
	bool start();
	
	//initialization
	bool initialize();
	bool init1();
	bool init2();
	bool init3();
	bool init4();
	bool init5();
	bool init6();
	bool id_rel_();
	bool id_rel1_();
	bool AcOP();
	bool AM();
	bool static_final();
	bool s_final();
	bool id_const();
	bool Const();
	bool Global();
	bool pointer();

	//Expression
	bool OE();
	bool exp();
	bool exp_OR();
	bool expAND();
	bool exp_AND();
	bool expRELOP();
	bool exp_RELOP();
	bool expPM();
	bool exp_PM();
	bool expMDM();
	bool exp_MDM();
	bool exp_F();
	bool ID_rel();
	bool ID_rel1();
	bool ID_rel2();
	bool This();
	bool In();
	bool In_();

	//body
	bool body();
	bool M_St();
	bool M_St_();
	bool S_St();
	bool S_St1();
	bool S_St2();
	bool sst1();
	bool N();

	//class
	bool Class();
	bool inherit();
	bool inherit_();
	bool class_body();
	bool class_body1();
	bool class_body2();
	bool class_body3();

	//class call
	bool Class_call();

	//constructor
	bool constructor();
	bool arg_list();
	bool arg_list1();
	bool arg_list_call();
	bool arg_list_call1();

	//function
	bool function();
	bool function_();
	bool data_type();

	//loops
	bool For();
	bool For_();
	bool While();

	//if_elif_else
	bool If();
	bool Elif();
	bool Else();

	//list
	bool list();
	bool list1();
	bool list2();
	bool list3();
	bool list4();
	bool list5();

	//dictionary
	bool Dictionary();
	bool Dictionary1();
	bool Dictionary2();
	bool Dictionary3();
	bool Dictionary4();
	bool Dictionary6();
	bool Dictionary7();
	
	//del
	bool Del();
	bool Del_();

	//try_Except_finally
	bool Try();
	bool Except();
	bool Finally();
	bool Exception();
	
	//lambda
	bool lambda();


private:
	vector<Token> tlist;
	int itr;
};


#endif // !SYNTAXANDSEMENTICANALYZER_H

