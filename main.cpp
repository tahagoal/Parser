#include <bits/stdc++.h>

using namespace std;

string oneword;
ifstream readFile;
ofstream output ("parser_output.txt");

void stmt();
void match(string);
void read_exp();
void write_exp();


void match(string s)
{
	if (oneword == s)
	{
		readFile >> oneword;
	}
	else
	{
	    output <<"Error"<<"\n";
		//cout << "Error" << endl;
		exit(1);
	}
}

void stmt_seq()
{
    stmt();
	char c = oneword[0];
	while (c == ';')
    {
        match(";");
        if(readFile.eof())
            break;
        stmt();
        c = oneword[0];
    }
	//cout << "Statement sequence found" << endl;
}


void factor()
{
	char c = oneword[0];
	switch (c){
	case 'n':
		match("number");
		break;
	case 'i':
		match("identifier");
		break;
	case '(':
		match("(");
		match("exp");
		match(")");
		break;
	}
	output <<"Factor found"<<"\n";
	//cout << "Factor found" << endl;
}

void mulop()
{
	char c = oneword[0];
	switch (c){
	case '*':
		match("*");
		break;
	case '/':
		match("/");
		break;
	}
	output <<"Mulop found"<<"\n";
	//cout << "Mulop found" << endl;
}

void addop()
{
	char c = oneword[0];
	switch (c){
	case '+':
		match("+");
		break;
	case '-':
		match("-");
		break;
	}
	output <<"addop found"<<"\n";
	//cout << "addop found" << endl;
}

void comparisonop()
{
	char c = oneword[0];
	switch (c){
	case '<':
		match("<");
		break;
	case '=':
		match("=");
		break;
	}
	output <<"Comparisonop found"<<"\n";
	//cout << "Comparisonop found" << endl;
}

void term()
{
    factor();
	char c = oneword[0];
	while (c == '*' || c == '/')
    {
        mulop();
        factor();
        c = oneword[0];
    }
    output <<"Term found"<<"\n";
	//cout << "Term found" << endl;
}

void simplexp()
{
    term();
	char c = oneword[0];
	while (c == '+' || c == '-')
    {
        addop();
        term();
        c = oneword[0];
    }
    output <<"SimpleExp found"<<"\n";
	//cout << "Simplexp found" << endl;
}

void exp()
{
    simplexp();
    if(oneword[0] == '<' || oneword[0] == '=')
    {
        comparisonop();
        simplexp();
    }
    output <<"Exp found"<<"\n";
    //cout << "Exp found" << endl;
}

void write_exp()
{
    match("write");
    exp();
    output <<"Write statement found"<<"\n";
    //cout << "Write statement found" << endl;
}

void read_exp()
{
    match("read");
    match("identifier");
    output <<"Read statement found"<<"\n";
    //cout << "Read statement found" << endl;
}

void assign_stmt()
{
    match("identifier");
    match(":=");
    exp();
    output <<"Assignment statement found"<<"\n";
    //cout << "Assignment statement found" << endl;
}

void repeat()
{
    match("repeat");
    stmt_seq();
    match("until");
    exp();
    output <<"Repeat statement found"<<"\n";
    //cout << "Repeat statement found" << endl;
}

void if_stmt()
{
    match("if");
    exp();
    match("then");
    stmt_seq();
    if(oneword == "else")
    {
        match("else");
        stmt_seq();
    }
    match("end");
    output <<"If statement found"<<"\n";
    //cout << "If statement found" << endl;
}

void stmt()
{
    if(oneword == "if")
        if_stmt();
    else if(oneword == "repeat")
        repeat();
    else if (oneword == "identifier")
        assign_stmt();
    else if (oneword == "read")
        read_exp();
    else
        write_exp();
    //cout << "Statement found" << endl;
}

void program(){

	readFile.open("C:\\Users\\ahmed\\Documents\\Code blocks\\Scanner\\scanner_output.txt");
	readFile >> oneword;
	stmt_seq();
	output <<"Program found"<<"\n";
    //cout << "Program found"<<endl;
    readFile.close();
    output.close();
}

int main()
{
	program();
    return 0;
}



