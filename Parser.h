#ifndef __PARSER_H__
#define __PARSER_H__

#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include <math.h>

class Token
{
public:
	double value;
	int type;
};

class Parser
{
private:
	char *infix;

	int priority(char a)
	{
		int temp;
		switch (a)
		{
		case '*': temp = 3; break;
		case '/': temp = 3; break;
		case '+': temp = 4; break;
		case '-': temp = 4; break;
		case '^': temp = 1; break;
		case '%': temp = 1; break;
		case 's': temp = 2; break;
		case 'c': temp = 2; break;
		case 'l': temp = 2; break;
		case 'b': temp = 2; break;
		case 't': temp = 2; break;
		case 'm': temp = 2; break;
		case 'h': temp = 2; break;
		case 'o': temp = 2; break;
		case 'e': temp = 2; break;
		case 'L': temp = 2; break;
		default: temp = 0;
		}
		return temp;
	}

	char isonechar(char a, char b, char c)
	{
		if (a == 's'&&b == 'i'&&c == 'n')
			return 's';
		else if (a == 'c'&&b == 'o'&&c == 's')
			return 'c';
		else if (a == 'l'&&b == 'o'&&c == 'g')
			return 'l';
		else if (a == 'c'&&b == 'o'&&c == 't')
			return 'b';
		else if (a == 't'&&b == 'a'&&c == 'n')
			return 't';
		else if (a == 's'&&b == 'e'&&c == 'c')
			return 'm';
		else if (a == 'c'&&b == 's'&&c == 'c')
			return 'h';
		else if (a == 'e'&&b == 'x'&&c == 'p')
			return 'e';
		else if (a == 'a'&&b == 'b'&&c == 's')
			return 'o';
		else if (a == 'l'&&b == 'n')
			return 'L';
		else
			return 0;
	}

	char isoperator(char c)
	{
		if (c == '+' || c == '-' || c == '/' || c == '*' ||
			c == '^' || c == '%')
			return c;
		else
			return 0;
	}

	char isbracket(char c)
	{
		if (c == '(' || c == ')')
			return c;
		else
			return 0;
	}

	bool isnumber(char c)
	{
		if (c >= '0'&& c <= '9')
			return true;
		else
			return false;
	}

	double eval(double op1, double op2, char operate)
	{
		switch (operate)
		{
		case '*': return op2 * op1;
		case '/': return op2 / op1;
		case '+': return double(op1 + op2);
		case '-': return op2 - op1;
		case '^': return pow(op1, op2);
		case '%': return remainderf(op1, op2);
		case 's': return sin(op1);
		case 'c': return cos(op1);
		case 'l': return log10(op1);
		case 'b': return (1 / tan(op1));
		case 't': return tan(op1);
		case 'm': return (1 / cos(op1));
		case 'h': return (1 / sin(op1));
		case 'o': return fabs(op1);
		case 'e': return exp(op1);
		case 'L': return log(op1);
		default: return 0;
		}
	}

	double evalPostfix(Token postfix[], int size)
	{
		std::stack<Token> s;
		Token temp;
		int i = 0;
		double val = 0;
		while (i < size)
		{
			if (postfix[i].type == 3)
			{
				val = eval(postfix[i + 1].value, 0.0, char(postfix[i].value));
				temp.value = val;
				temp.type = 1;
				s.push(temp);
				i++;
			}
			else if (postfix[i].type <= 2)			//number or expression
			{
				// we saw an operand push the digit onto stack
				s.push(postfix[i]);
			}
			else
			{
				// we saw an operator
				// pop off the top two operands from the
				// stack and evalute them using the current
				// operator

				double op1 = s.top().value;
				s.pop();
				double op2 = s.top().value;
				s.pop();
				val = eval(double(op1), double(op2), char(postfix[i].value));
				temp.value = val;
				temp.type = 1;

				// push the value obtained after evaluating onto the stack
				s.push(temp);
			}
			if (size == 1)
				val = s.top().value;
			i++;

			/*		for (std::stack<Token> dump = s; !dump.empty(); dump.pop())
			{
			if (dump.top().type == 5)
			printf("%d %c\n", dump.top().type, dump.top().value);
			else
			printf("%d %f\n", dump.top().type, dump.top().value);
			}*/
			//cout << endl;
		}
		return val;
	}

	void BreakIntoTokens(char* infix, Token token[], int &size, double x, double y, double t)
	{
		char buffer[10];
		int j, start, end;
		int c = 0;
		int value = 0;
		for (unsigned i = 0; i < strlen(infix); i++)
		{
			if (infix[i] == ' ')
				continue;
			if (isnumber(infix[i]) == true)
			{
				start = i;
				end = i;
				j = i + 1;
				while ((isnumber(infix[j]) == true) || (infix[j] == '.'))
					end = j++;
				int k = 0;
				for (j = start; j <= end; j++)						//reusing j
					buffer[k++] = infix[j];
				buffer[j - i] = 0;									//make last char null
				token[c].value = atof(buffer);
				token[c].type = 1;									//1 is for double numbers
				c++;
				i = end;
			}
			else if (infix[i] <= 'z' && infix[i] >= 'a')
			{
				if (infix[i] == 'x' || infix[i] == 'y' || infix[i] == 't')
				{
					if (infix[i] == 'x')
						token[c].value = x;
					else if (infix[i] == 'y')
						token[c].value = y;
					else
						token[c].value = t;

					token[c].type = 1;							//2 is for variable chars (x,y,t)
					c++;
				}
				else if (isonechar(infix[i], infix[i + 1], infix[i + 2]) != 0)								//note to self: replace isonechar by an appropriate name
				{
					token[c].value = double(isonechar(infix[i], infix[i + 1], infix[i + 2]));
					token[c].type = 3;
					c++;										//3 is for single argument operators (shorthands for sin, cos, etc as defined in isonechar
				}
				//what else could start with an alphabet?
			}
			else if (isbracket(infix[i]) != 0)
			{
				token[c].value = double(isbracket(infix[i]));
				token[c].type = 5;								//5 is for brackets cuz brackets be special.
				c++;
			}
			else if (isoperator(infix[i]) != 0)
			{
				token[c].value = double(isoperator(infix[i]));
				token[c].type = 4;								//4 is for double argument operators (+,-,/,^,*)
				c++;
			}


			//what else could the equation have?
		}

		//////////////////////////////////////////
		//Expression is now broken into c tokens//
		//////////////////////////////////////////

		/*printf("TOKEN VALUE\tTOKEN ASCII (if appl)\tTOKEN TYPE\n");
		for (int i = 0; i < c; i++)
		printf("%f\t\t%c\t\t%d\n", token[i].value, char(token[i].value), token[i].type);*/

		size = c;
	}

	void ConversionToPostfix(Token token[], int siz, Token output[])
	{
		std::stack<Token> operator_stack;
		int c = siz;
		int j;
		j = 0;

		for (int i = 0; i < c; i++)
		{
			//if operator
			if (char(token[i].value) == '(')
			{
				operator_stack.push(token[i]);
			}

			else if (char(token[i].value) == ')')
			{
				while (operator_stack.top().value != '(')
				{
					output[j] = operator_stack.top();
					operator_stack.pop();
					j++;
				}
				operator_stack.pop();
			}
			else if (token[i].type == 3 || token[i].type == 4)
			{
				//decide operator fate
				while (!operator_stack.empty() && operator_stack.top().value != '(' && priority(operator_stack.top().value) <= priority(token[i].value))
				{
					output[j] = operator_stack.top();
					operator_stack.pop();
					j++;
				}
				operator_stack.push(token[i]);
			}
			else
			{
				output[j] = token[i];
				j++;
			}
		}

		//pop the last remaining operators in order

		while (!operator_stack.empty())
		{
			output[j] = operator_stack.top();
			operator_stack.pop();
		}
	};

public:
	Parser()
	{
		infix = nullptr;
	};

	void CleanUp()
	{
		if (infix != nullptr)
		{
			delete infix;
			infix = nullptr;
		};
	}

	~Parser()
	{
		//CleanUp();
	};

	double Evaluate(double x, double y, double t)
	{
		Token token[256];
		int siz = 0;
		Token output[256];

		BreakIntoTokens(infix, token, siz, x, y, t);
		ConversionToPostfix(token, siz, output);

		double val = evalPostfix(output, siz);
		return val;
	}

	void SetInfix(char *FunctionString)
	{
		CleanUp();
		infix = FunctionString;
	};
};
#endif