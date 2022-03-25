#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

using ll = long long;
using ld = long  double;

enum token_type
{
	NUMBER,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	POWER,
	LEFT_PAREN,
	RIGHT_PAREN
};

class Token
{
public:
	token_type type;
	double value;
	Token(token_type tp,double val)
	{
		type = tp;
		value = val;
	}

	friend ostream& operator<<(ostream& Str, const Token& tk)
	{
		if(tk.type == NUMBER)
		{
			Str << "number: " << tk.value;
		}
		else if(tk.type == PLUS)
			Str << "plus";
		else if(tk.type == MINUS)
			Str << "minus";
		else if(tk.type == MULTIPLY)
			Str << "multiply";
		else if(tk.type == DIVIDE)
			Str << "divide";
		else if(tk.type == LEFT_PAREN )
			Str << "left_paren";
		else if(tk.type == RIGHT_PAREN)
			Str << "right_paren";
		return Str;
	}
};
//a node is an considered operation that has children, where its children could be other nodes, representing other 
//operations that should be executed first, or it could have a simple number value 
class node
{
public:
    virtual double execute()
    {
        return 1;
    }
    virtual double get_value() const
    {
        return 1;
    }
    virtual string to_str()
    {
        return "";
    }
};

//add operation node
class add_node : public node
{
public:
	node* first_operand;
	node* second_operand;
	add_node(node* f, node* s)
	{
		first_operand = f;
		second_operand = s;
	}
	double execute()
	{
		return first_operand->execute() + second_operand->execute();
	}
	string to_str()
	{
		return "(" + first_operand->to_str() + " + " + second_operand->to_str() + ")";
	}
};
//subtract operation node
class subtract_node : public node
{
public:
	node* first_operand;
	node* second_operand;
	subtract_node(node* f, node* s)
	{
		first_operand = f;
		second_operand = s;
	}
	double execute()
	{
		return first_operand->execute() - second_operand->execute();
	}
	string to_str()
	{
		return "(" + first_operand->to_str() + " - " + second_operand->to_str() + ")";
	}
};
//multiply operation node
class multiply_node : public node
{
public:
	node* first_operand;
	node* second_operand;
	multiply_node(node* f, node* s)
	{
		first_operand = f;
		second_operand = s;
	}
	double execute()
	{
		return first_operand->execute() * second_operand->execute();
	}
	string to_str()
	{
		return "(" + first_operand->to_str() + " * " + second_operand->to_str() + ")";
	}
};
//divide operation node
class divide_node : public node
{
public:
	node* first_operand;
	node* second_operand;
	divide_node(node* f, node* s)
	{
		first_operand = f;
		second_operand = s;
	}
	double execute()
	{
		return first_operand->execute() / second_operand->execute();
	}
	string to_str()
	{
		return "(" + first_operand->to_str() + " / " + second_operand->to_str() + ")";
	}
};
//a number node is a node with no children, it returns a number on execution, it is where the recursion stops.
class number_node : public node
{
public:
	double value;
	number_node(double val)
	{
		value = val;
	}
	double execute()
	{
		return value;
	}
	string to_str()
	{
		
		return to_string(value);
	}
};

//lexer is responsible for tokenizing the expression ie converting the string to individual tokens
class Lexer
{
public:
	size_t index;
	size_t length;
	string input;


	Lexer(string input)
	{
		this->input = input;
		index = 0;
		length = input.size();
	}

	double getnumber()
	{
		string num;
		int dot_count = 0;
		while(index < length)
		{
			if(isdigit(input[index]))
				num.push_back(input[index]);

			else if(input[index] == '.')
			{
				dot_count++;
				if(dot_count == 2)
					throw string("invalid syntax: found illegal \'.\'");
				num.push_back(input[index]);
			}
			else
				break;
			index++;
		}
		return stod(num);
	}
	vector<Token> generate_tokens()
	{
		vector<Token> tokens;
		while(index < length)
		{
			if(isspace(input[index]))
			{
				index++;
				continue;
			}
			if(input[index] == '(')
				tokens.push_back(Token(LEFT_PAREN, NAN));
			else if(input[index] == ')')
				tokens.push_back(Token(RIGHT_PAREN, NAN));
			else if(input[index] == '+')
				tokens.push_back(Token(PLUS, NAN));
			else if(input[index] == '-')
				tokens.push_back(Token(MINUS, NAN));
			else if(input[index] == '*')
				tokens.push_back(Token(MULTIPLY, NAN));
			else if(input[index] == '/')
				tokens.push_back(Token(DIVIDE, NAN));
			else if(isdigit(input[index]))
			{
				Token tk(NUMBER,getnumber());
				tokens.push_back(tk);
				index--;
			}
			else
			{
				throw string("invalid syntax: found illegal ") + "\'" + input[index] + "\'";
			}
			index++;
		}
		return tokens;
	}

};
//takes in tokens and tries to build an abstract syntax tree
class Parser
{
public:
	int token_index;
	int n_tokens;
	vector<Token> tokens;
	Parser(vector<Token> tks)
	{
		tokens = tks;
		token_index = 0;
		n_tokens = tokens.size();
	}

	void print_tokens()
	{
		cout << "[";
		for(int i = 0; i < tokens.size(); i++)
			cout << tokens[i] << ((i != tokens.size() - 1)? ", " : "");
		cout << "]\n";
	}
	node* get_factor()
	{
		if(tokens[token_index].type == NUMBER)
		{
			node * n = new number_node(tokens[token_index].value);
			token_index++;
			return n;
		}
		if(tokens[token_index].type == PLUS)
		{
			token_index++;
			node* operand = get_factor();
			node* n = new add_node(operand, new number_node(0));
			return n;
		}
		if(tokens[token_index].type == MINUS)
		{
			token_index++;
			node* operand = get_factor();
			node* n = new subtract_node(new number_node(0), operand);
			return n;
		}
		if(tokens[token_index].type == LEFT_PAREN)
		{
			token_index++;
			node * expr = get_expression();
			if(tokens[token_index].type != RIGHT_PAREN)
				throw string("invalid syntax: missing bracket \')\'");
			else
				token_index++;
			return expr;
		}
		else
			throw string("syntax error: couldn't find factor");
		return nullptr;

	}
	node* get_term()
	{
		node* res = get_factor();
		while(token_index < n_tokens)
		{
			if(tokens[token_index].type == MULTIPLY)
			{
				token_index++;
				res = new multiply_node(res, get_factor());

			}
			else if(tokens[token_index].type == DIVIDE)
			{
				token_index++;
				res = new divide_node(res,  get_factor());
			}
			else
				break;
		}
		return res;

	}
	node* get_expression()
	{
		node* res = get_term();

		while(token_index < n_tokens)
		{
			if(tokens[token_index].type == PLUS)
			{
				token_index++;
				res = new add_node(res, get_term());

			}
			else if(tokens[token_index].type == MINUS)
			{
				token_index++;
				res = new subtract_node(res, get_term());
			}
			else
				break;
		}
		return res;
	}
	node* parse()
	{
		node * expr = get_expression();
		return expr;
	}

};

//infinite loop where user inputs an expression and the program attempts to evaluate it;
int main()
{
	while(true)
	{
		string expression;
		cout << "-> ";
		getline(cin, expression);
		if(expression == "")
		{
			cout << "enter valid expression\n";
			continue;
		}
		vector<Token> tks;
		Lexer lexer(expression);
		try
		{
			tks = lexer.generate_tokens();
		}
		catch (string message)
		{
			cout << message << endl;
			continue;
		}

		Parser parser(tks);
		node* parsed_expr;
		try
		{
			parsed_expr = parser.parse();
		}
		catch(string e)
		{
			cout << e << endl;
			continue;
		}
		cout << parsed_expr->execute() << endl;
	}
}