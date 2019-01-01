#include "SyntaxAndSementicAnalyzer.h"

vector<Token> tlist;
int itr;





vector<string> exp_ORSet = { "nl", "]", ")", ",", "in" };
vector<string> exp_ANDSet = { "Or", "nl", "]", ")", ",", "in" };
vector<string> exp_RELOPSet = { "AND", "Or", "nl", "]", ")", ",", "in" };
vector<string> exp_PMSet = { "RelOp", "AND", "Or", "nl", "]", ")", ",", "in" };
vector<string> exp_MDMSet = { "PM", "RelOp", "AND", "Or", "nl", "]", ")", ",", "in" };
vector<string> id_relSet = { "DM", "*", "PM", "RelOp", "AND", "Or", "nl", "]", ")", "=" , ",", "AsOp", "in", ":", "}" };
vector<string> id_rel2Set = { "DM", "*", "PM", "RelOp", "AND", "Or", "nl", "]", ")", "=" , ",", "AsOp", "in", ":", "}" };
vector<string> inSet = { "DM", "*", "PM", "RelOp", "AND", "Or", "nl", "]", ")", "," };
vector<string> elseSet = { "IndentOut", "def", "class", "*", "accessModifier", "for", "while", "if", "try", "del", "EOF", "nl", "static", "final", "ID", "int_const", "float_const", "string_const", "char_const", "bool_const" };
vector<string> AcOpSet = { "DM", "*", "PM", "RelOp", "AND", "Or", ")", "nl", ",",  "]", "in", "AsOp" };

SyntaxAndSementicAnalyzer::SyntaxAndSementicAnalyzer(vector<Token> tl)
{
	tlist = tl;
	itr = 0;
}

SyntaxAndSementicAnalyzer::~SyntaxAndSementicAnalyzer()
{
}

//scope=0 --> search in function table
//scope!=0 --> search in scope table

bool SyntaxAndSementicAnalyzer::start()
{
	if (tlist.at(itr).getClassPart() == "def")
	{
		itr++;
		if (function())
			if (start())
				return true;
	}
	else if (Class())
	{
		if (start())
			return true;
	}
	else if (For())
	{
		if (start())
			return true;
	}
	else if (While())
	{
		if (start())
			return true;
	}
	else if (If())
	{
		if (start())
			return true;
	}
	else if (Try())
	{
		if (start())
			return true;
	}
	else if (Del())
	{
		if (tlist.at(itr).getClassPart() == "nl")
		{
			itr++;
			if (start())
				return true;
		}
	}
	else if (initialize())
	{	
		if (tlist.at(itr).getClassPart() == "nl")
		{
			itr++;
			if (start())
				return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "EOF")
	{
		itr++;
		return true;
	}
	cout << "Syntax error at line number: " << tlist.at(itr).getLineNo();
	return false;
}
			
bool SyntaxAndSementicAnalyzer::initialize()
{
	if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		string Name = tlist.at(itr).getValuePart();
		if (id_rel_())
			return true;
	}
	else if (Const())
	{
		if (init2())
			return true;
	}
	else if (tlist.at(itr).getClassPart() == "*")
	{
		itr++;
		if (init3())
			return true;
	}
	else if (tlist.at(itr).getClassPart() == "accessModifier")
	{
		itr++;
		if (init4())
			return true;
	}
	else if (static_final())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (ID_rel())
				if (tlist.at(itr).getClassPart() == "=")
				{
					itr++;
					if (init5())
						return true;
				}
		}
	}
	else if (tlist.at(itr).getClassPart() == "this")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "AcOp")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == "ID")
			{
				itr++;
				if (ID_rel())
					if (init1())
						return true;
			}
		}
	}
	else if (tlist.at(itr).getClassPart() == "(")
	{
		itr++;
		if (exp())
			if (tlist.at(itr).getClassPart() == ")")
			{
				itr++;
				if (OE())
					return true;
			}
	}
	else if (tlist.at(itr).getClassPart() == "Not")
	{
		itr++;
		if (exp_F())
			if (OE())
				return true;
	}
	else if (list2())
		return true;
	else if (Dictionary2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::init1()
{
	if (tlist.at(itr).getClassPart() == "AsOp")
	{
		itr++;
		if(exp())
				return true;
	}
	else if (tlist.at(itr).getClassPart() == "=")
	{
		itr++;
		if (init5())
			return true;
	}
	else if (init2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::init2()
{
	if (OE())
		if (In())
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::init3()
{
	if (tlist.at(itr).getClassPart() == "accessModifier")
	{
		itr++;
		if (init4())
			return true;
	}
	else if (init4())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::init4()
{
	if (static_final())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if(ID_rel())
				if (tlist.at(itr).getClassPart() == "=")
				{
					itr++;
					if (init5())
						return true;
				}
		}
	}
	else if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		if(ID_rel())
			if (tlist.at(itr).getClassPart() == "=")
			{
				itr++;
				if (init5())
					return true;
			}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::init5()
{
	if (Const())
	{
		if (OE())
			return true;
	}
	else if (This())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (ID_rel())
				if (init6())
					return true;
		}
	}
	else if (list())
		return true;
	else if (Dictionary())
		return true;
	else if (Class_call())
		return true;
	else if (lambda())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::init6()
{
	if (tlist.at(itr).getClassPart() == "=")
	{
		itr++;
		if (init5())
			return true;
	}
	else if (init2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::id_rel_()
{
	if (id_rel1_())
		return true;
	else if (tlist.at(itr).getClassPart() == "(")
	{
		itr++;
		if (arg_list_call())
			if (tlist.at(itr).getClassPart() == ")")
			{
				itr++;
				if (AcOP())
					return true;
			}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::id_rel1_()
{
	if (tlist.at(itr).getClassPart() == "[")
	{
		itr++;
		if (exp())
			if (tlist.at(itr).getClassPart() == "]")
			{
				itr++;
				if (id_rel1_())
					return true;
			}
	}
	else if (tlist.at(itr).getClassPart() == "AcOp")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (id_rel_())
				return true;
		}
	}
	else if (init1())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::AcOP()
{
	if (tlist.at(itr).getClassPart() == "AcOp")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (id_rel_())
				return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "nl")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::AM()
{
	if (tlist.at(itr).getClassPart() == "accessModifier")
	{
		itr++;
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "static" || tlist.at(itr).getClassPart() == "final" || tlist.at(itr).getClassPart() == "ID")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::static_final()
{
	if (tlist.at(itr).getClassPart() == "static")
	{
		itr++;
		if (s_final())
			return true;
	}
	else if (tlist.at(itr).getClassPart() == "final")
	{
		itr++;
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::s_final()
{
	if (tlist.at(itr).getClassPart() == "final")
	{
		itr++;
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "ID")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::id_const()
{
	if (This())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if(ID_rel())
				return true;
		}
	}
	else if (Const())
	{
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Const()
{
	if (tlist.at(itr).getClassPart() == "int_const" || tlist.at(itr).getClassPart() == "float_const" || tlist.at(itr).getClassPart() == "string_const" || tlist.at(itr).getClassPart() == "char_const" || tlist.at(itr).getClassPart() == "bool_const")
	{
		itr++;
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Global()
{
	if (tlist.at(itr).getClassPart() == "global")
	{
		itr++;
		if (initialize())
			return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::pointer()
{
	if (tlist.at(itr).getClassPart() == "*")
	{
		itr++;
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "ID")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::OE()
{
	if (exp_MDM())
		if (exp_PM())
			if (exp_RELOP())
				if (exp_AND())
					if (exp_OR())
						return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::exp()
{
	if (expAND())
	{
		if (exp_OR())
			return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::exp_OR()
{
	if (tlist.at(itr).getClassPart() == "Or")
	{
		itr++;
		if (expAND())
			if (exp_OR())
				return true;
	}
	for (int i = 0; i < exp_ORSet.size(); i++)
		if (tlist.at(itr).getClassPart() == exp_ORSet.at(i))
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::expAND()
{

	if (expRELOP())
		if (exp_AND())
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::exp_AND()
{
	if (tlist.at(itr).getClassPart() == "And")
	{
		itr++;
		if (expRELOP())
			if (exp_AND())
				return true;
	}
	for (int i = 0; i < exp_ANDSet.size(); i++)
		if (tlist.at(itr).getClassPart() == exp_ANDSet.at(i))
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::expRELOP()
{
	if (expPM())
		if (exp_RELOP())
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::exp_RELOP()
{
	if (tlist.at(itr).getClassPart() == "RelOp")
	{
		itr++;
		if (expPM())
			if (exp_RELOP())
				return true;
	}
	for (int i = 0; i < exp_RELOPSet.size(); i++)
		if (tlist.at(itr).getClassPart() == exp_RELOPSet.at(i))
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::expPM()
{
	if (expMDM())
		if (exp_PM())
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::exp_PM()
{
	if (tlist.at(itr).getClassPart() == "PM")
	{
		itr++;
		if (expMDM())
			if (exp_PM())
				return true;
	}
	for (int i = 0; i < exp_PMSet.size(); i++)
		if (tlist.at(itr).getClassPart() == exp_PMSet.at(i))
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::expMDM()
{
	if (exp_F())
		if (exp_MDM())
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::exp_MDM()
{
	if (tlist.at(itr).getClassPart() == "DM" || tlist.at(itr).getClassPart() == "*")
	{
		itr++;
		if (exp_F())
			if (exp_MDM())
				return true;
	}
	for (int i = 0; i < exp_MDMSet.size(); i++)
		if (tlist.at(itr).getClassPart() == exp_MDMSet.at(i))
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::exp_F()
{
	if (This())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (ID_rel())
				if (In())
					return true;
		}
	}
	else if (Const())
	{
		if (In())
			return true;

	}
	else if (tlist.at(itr).getClassPart() == "(")
	{
		itr++;
		if (exp())
			if (tlist.at(itr).getClassPart() == ")")
			{
				itr++;
				return true;
			}
	}
	else if (tlist.at(itr).getClassPart() == "Not")
	{
		itr++;
		if (exp_F())
			return true;
	}
	else if (lambda())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::ID_rel()
{
	if (tlist.at(itr).getClassPart() == "[")
	{
		itr++;
		if(exp())
			if (tlist.at(itr).getClassPart() == "]")
			{
				itr++;
				if (ID_rel1())
					return true;
			}
	}
	else if (tlist.at(itr).getClassPart() == "(")
	{
		itr++;
		if (arg_list_call())
			if (tlist.at(itr).getClassPart() == ")")
			{
				itr++;
				if (ID_rel1())
					return true;
			}
	}
	else if (tlist.at(itr).getClassPart() == "AcOp")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (ID_rel())
				return true;
		}
	}
	else {
		for (int i = 0; i < id_relSet.size(); i++)
			if (tlist.at(itr).getClassPart() == id_relSet.at(i))
				return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::ID_rel1()
{
	if (tlist.at(itr).getClassPart() == "AcOp")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (ID_rel())
				return true;
		}
	}
	else if (ID_rel2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::ID_rel2()
{
	if (tlist.at(itr).getClassPart() == "[")
	{
		itr++;
		if (exp())
			if (tlist.at(itr).getClassPart() == "]")
			{
				itr++;
				if (ID_rel1())
					return true;
			}
	}
	else {
		for (int i = 0; i < id_rel2Set.size(); i++)
			if (tlist.at(itr).getClassPart() == id_rel2Set.at(i))
				return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::This()
{
	if (tlist.at(itr).getClassPart() == "this")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "AcOp")
		{
			itr++;
			return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "ID")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::In()
{
	if (tlist.at(itr).getClassPart() == "in")
	{
		itr++;
		if (In_())
			return true;
	}
	else
	{
		for (int i = 0; i < inSet.size(); i++)
			if (tlist.at(itr).getClassPart() == inSet.at(i))
				return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::In_()
{
	if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		return true;
	}
	else if (list())
	{
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::body()
{
	if (S_St())
		return true;
	else if (tlist.at(itr).getClassPart() == "nl")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "IndentInit")
		{
			itr++;
			if(M_St())
				if (tlist.at(itr).getClassPart() == "IndentOut")
				{
					itr++;
					return true;
				}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::M_St()
{
	if (S_St())
		//if (N())
			if (M_St_())
				return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::M_St_()
{
	if (M_St())
		return true;
	else if (tlist.at(itr).getClassPart() == "IndentOut")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::S_St()
{
	if (S_St1())
	{
		if (tlist.at(itr).getClassPart() == "nl")
		{
			itr++;
			return true;
		}
	}
	else if (S_St2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::S_St1()
{
	if (tlist.at(itr).getClassPart() == "break")
	{
		itr++;
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "continue")
	{
		itr++;
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "return")
	{
		itr++;
		if (sst1())
			return true;
	}
	else if (Del())
		return true;
	else if (Global())
		return true;
	else if (initialize())
		return true;
	else if (tlist.at(itr).getClassPart() == "pass")
	{
		itr++;
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::S_St2()
{
	if (For())
		return true;
	else if (While())
		return true;
	else if (If())
		return true;
	else if (Try())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::sst1()
{
	if (exp())
		return true;
	else if (list2())
		return true;
	else if (Dictionary2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::N()
{
	if (tlist.at(itr).getClassPart() == "nl")
	{
		itr++;
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "IndentOut") {
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Class()
{
	if (tlist.at(itr).getClassPart() == "class")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == "(")
			{
				itr++;
				if (inherit())
				{
					if (tlist.at(itr).getClassPart() == ")")
					{
						itr++;
						if (tlist.at(itr).getClassPart() == ":")
						{
							itr++;
							if (tlist.at(itr).getClassPart() == "nl")
							{
								itr++;
								if (tlist.at(itr).getClassPart() == "IndentInit")
								{
									itr++;
									if (class_body())
										if (N())
										{
											if (tlist.at(itr).getClassPart() == "IndentOut")
											{
												itr++;
												return true;
											}
										}

								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::inherit()
{
	if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		if (inherit_())
			return true;
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::inherit_()
{
	if (tlist.at(itr).getClassPart() == ",")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::class_body()
{
	if (class_body1())
		return true;
	else if (tlist.at(itr).getClassPart() == "pass")
	{
		itr++;
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::class_body1()
{
	if (initialize())
	{
		if (tlist.at(itr).getClassPart() == "nl")
		{
			itr++;
			if (class_body3())
				return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "def")
	{
		itr++;
		if (class_body2())
			if(class_body3())
				return true;
	}

	return false;
}

bool SyntaxAndSementicAnalyzer::class_body2()
{
	if (constructor())
	{
		return true;
	}
	else if (function())
	{
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::class_body3()
{
	if (class_body1())
		return true;
	else if (tlist.at(itr).getClassPart() == "IndentOut")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::Class_call()
{

		if (tlist.at(itr).getClassPart() == "new")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == "ID")
			{
				itr++;
				if (tlist.at(itr).getClassPart() == "(")
				{
					itr++;
					if (arg_list_call())
					{
						if (tlist.at(itr).getClassPart() == ")")
						{
							itr++;
							return true;
						}
					}
				}
			}
		}
	
	
	return false;
}

bool SyntaxAndSementicAnalyzer::constructor()
{
	if (AM())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == "(")
			{
				itr++;
				if (arg_list())
					if (tlist.at(itr).getClassPart() == ")")
					{
						itr++;
						if (tlist.at(itr).getClassPart() == ":")
						{
							itr++;
							if (body())
							{
								return true;
							}
						}
					}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::arg_list()
{
	if (data_type())
	{
		if (pointer())
		{
			if (tlist.at(itr).getClassPart() == "ID")
			{
				itr++;
				if (arg_list1())
				{
					return true;
				}
			}
		}
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::arg_list1()
{
	if (tlist.at(itr).getClassPart() == ",")
	{
		itr++;
		if (data_type())
		{
			if (pointer())
			{
				if (tlist.at(itr).getClassPart() == "ID")
				{
					itr++;
					if (arg_list1())
					{
						return true;
					}
				}
			}
		}
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::arg_list_call()
{
	if (exp())
	{
		if (arg_list_call1())
		{
			return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::arg_list_call1()
{
	if (tlist.at(itr).getClassPart() == ",")
	{
		itr++;
		if (exp())
		{
			if (arg_list_call1())
			{
				return true;
			}
		}
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::function()
{
	if (data_type())
	{
		if (AM())
		{
			if (function_())
				return true;
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::function_()
{
	if (static_final())
	{
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == "(")
			{
				itr++;
				if (arg_list())
					if (tlist.at(itr).getClassPart() == ")")
					{
						itr++;
						if (tlist.at(itr).getClassPart() == ":")
						{
							itr++;
							if (body())
								return true;
						}
					}
			}

		}
	}
	else if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (arg_list())
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					if (tlist.at(itr).getClassPart() == ":")
					{
						itr++;
						if (body())
							return true;
					}
				}
		}

	}
	return false;
}

bool SyntaxAndSementicAnalyzer::data_type()
{
	if (tlist.at(itr).getClassPart() == "DT" || tlist.at(itr).getClassPart() == "string" || tlist.at(itr).getClassPart() == "ID" || tlist.at(itr).getClassPart() == "List" || tlist.at(itr).getClassPart() == "dict")
	{
		itr++;
		return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::For()
{
	if (tlist.at(itr).getClassPart() == "for")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == "in")
			{
				itr++;
				if (For_())
				{
					if (tlist.at(itr).getClassPart() == ":")
					{
						itr++;
						if (body())
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::For_()
{
	if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		if (ID_rel())
			return true;
	}
	else if (list2())
		return true;
	else if (Dictionary2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::While()
{
	if (tlist.at(itr).getClassPart() == "while")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (exp())
			{
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					if (tlist.at(itr).getClassPart() == ":")
					{
						itr++;
						if (body())
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::If()
{
	if (tlist.at(itr).getClassPart() == "if")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (exp())
			{
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					if (tlist.at(itr).getClassPart() == ":")
					{
						itr++;
						if (body())
							if (Elif())
								return true;
					}
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Elif()
{
	if (tlist.at(itr).getClassPart() == "elif")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (exp())
			{
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					if (tlist.at(itr).getClassPart() == ":")
					{
						itr++;
						if (body())
							if (Elif())
								return true;
					}
				}
			}
		}
	}
	else if (Else())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::Else()
{
	if (tlist.at(itr).getClassPart() == "else")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == ":")
		{
			itr++;
			if (body())
				return true;
		}
	}
	for (int i = 0; i < elseSet.size(); i++)
		if (tlist.at(itr).getClassPart() == elseSet.at(i))
			return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::list()
{
	if (list2())
		return true;
	else if (tlist.at(itr).getClassPart() == "List")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (list1())
			{
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					return true;
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::list1()
{
	if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		return true;
	}
	else if (list2())
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::list2()
{
	if (tlist.at(itr).getClassPart() == "[")
	{
		itr++;
		if (list3())
		{
			if (tlist.at(itr).getClassPart() == "]")
			{
				itr++;
				return true;
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::list3()
{

	if (id_const())
	{
		if (list4())
			return true;
	}
	else if (list2())
	{
		if (list4())
			return true;
	}
	else if (Dictionary2())
	{
		if (list4())
			return true;
	}
	else if (tlist.at(itr).getClassPart() == "]")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::list4()
{
	if (tlist.at(itr).getClassPart() == ",")
	{
		itr++;
		if (list5())
		{
			return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "]")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::list5()
{
	if (id_const())
	{
		if (list4())
			return true;
	}
	else if (list2())
	{
		if (list4())
			return true;
	}
	else if (Dictionary2())
	{
		if (list4())
			return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary()
{
	if (Dictionary2())
	{
		return true;
	}
	else if (tlist.at(itr).getClassPart() == "dict")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (Dictionary1())
			{
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					return true;
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary1()
{
	if (tlist.at(itr).getClassPart() == "ID")
	{
		itr++;
		return true;
	}
	else if (Dictionary2())
	{
		return true;
	}
	else if (tlist.at(itr).getClassPart() == ")")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary2()
{
	if (tlist.at(itr).getClassPart() == "{")
	{
		itr++;
		if (Dictionary3())
		{
			if (tlist.at(itr).getClassPart() == "}")
			{
				itr++;
				return true;
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary3()
{
	if (id_const())
	{
		if (tlist.at(itr).getClassPart() == ":")
		{
			itr++;
			if (Dictionary4())
				return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "}")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary4()
{
	if (id_const())
	{
		if (Dictionary6())
		{
			return true;
		}
	}
	else if (Dictionary2())
	{
		if (Dictionary6())
		{
			return true;
		}
	}
	else if (list2())
	{
		if (Dictionary6())
			return true;
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary6()
{
	if (tlist.at(itr).getClassPart() == ",")
	{
		itr++;
		if (Dictionary7())
		{
			return true;
		}
	}
	else if (tlist.at(itr).getClassPart() == "}")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::Dictionary7()
{
	if (id_const())
	{
		if (tlist.at(itr).getClassPart() == ":")
		{
			itr++;
			if (Dictionary4())
				return true;
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Del()
{
	if (tlist.at(itr).getClassPart() == "del")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (Del_())
			{
				return true;
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Del_()
{
	if (tlist.at(itr).getClassPart() == "[")
	{
		itr++;
		if (exp())
			if (tlist.at(itr).getClassPart() == "]")
			{
				itr++;
				return true;
			}
	}
	if (tlist.at(itr).getClassPart() == "nl")
		return true;
	return false;
}

bool SyntaxAndSementicAnalyzer::Try()
{
	if (tlist.at(itr).getClassPart() == "try")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == ":")
		{
			itr++;		
			if (body())
			{
				if (Except())
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Except()
{
	if (Finally())
		return true;
	else if (tlist.at(itr).getClassPart() == "except")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "(")
		{
			itr++;
			if (Exception())
			{
				if (tlist.at(itr).getClassPart() == ")")
				{
					itr++;
					if (tlist.at(itr).getClassPart() == ":")
					{
						itr++;
						if (body())
						{
							if (Except())
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Finally()
{
	if (tlist.at(itr).getClassPart() == "finally")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == ":")
		{
			itr++;
			if (body())
			{
				return true;
			}
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::Exception()
{
	if (tlist.at(itr).getClassPart() == "exception")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			return true;
		}
	}
	return false;
}

bool SyntaxAndSementicAnalyzer::lambda()
{
	if (tlist.at(itr).getClassPart() == "lambda")
	{
		itr++;
		if (tlist.at(itr).getClassPart() == "ID")
		{
			itr++;
			if (tlist.at(itr).getClassPart() == ":")
			{
				itr++;
				if (exp())
					return true;
			}
		}
	}
	return false;
}