#include <iostream>
#include <string>
#include <stdlib.h>
#include "CTIF_stack1.h"
#include "CTIF_stack2.h"
using namespace std;

void InPut(char*& fix, int& len)
{
	int i = 0;
	cin >> fix[i];
	while(fix[i] != '=')
	{
		i++;
		cin >> fix[i];
	}
	len = i;
}

bool IsOperator(char s)
{
	if(s == '+' || s == '-' || s == '*' || s == '/' || s == '(' || s == ')'  )
		return true;
	else 
		return false;
}

int Level(char s)
{
	if(s == '+' || s == '-')
		return 1;
	else if(s == '*' || s == '/')
		return 2;
}

bool CanPush(char s, Stack* sign)
{
	if(IsEmpty(sign))
		return true;
	else 
	{
		if(Top(sign) == '(')
			return true;
		else if(s == ')')
			return false;
		else if( Level(s) > Level(Top(sign)) )
			return true;
		else if( Level(s) <= Level(Top(sign)) )
			return false;
	}
}

void InFixToPostFix(char* inFix, int len, char** postFix, int& postLen)
{
	Stack* sign = CreatStack();
	int k = 0; //后缀表达式的索引，k和i要有所区别
	for(int i=0; i<len; )
	{
		char temp = inFix[i];
		if( IsOperator(temp))
		{
			if( temp == ')' )  //右括号是特殊情况
			{
				while(Top(sign) != '(')
				{
					*postFix[k] = Top(sign); 
					k++;
					Pop(sign);
				}
				Pop(sign); //删除sign栈顶位置的 ' ( ' ; 
				i++;
			}
			else
			{
				while( !CanPush(temp, sign) )
				{
					*postFix[k] = Top(sign); 
					k++;
					Pop(sign);
				}
				Push(temp, sign);
				i++;
			}
		}
		else
		{
			*postFix[k] = inFix[i];
			//处理不是一位数的操作数
			int m=k; //用m保存k值
			int n=1; 
			while( i+1 < len && !IsOperator(inFix[i+1]) )
			{
				postFix[m][n] = inFix[i+1];
				i++, n++;
			}
			i++;
			k++;
		}
	}
	//把sign里面还没输出的都弹出
	while(!IsEmpty(sign))
	{
		*postFix[k] = Top(sign);
		k++;
		Pop(sign);
	}
	postLen = k;
}

void CountPostFix(char** postFix, int postLen, float& out)
{
	FloatStack* operant = CreatFloatStack();
	float op1, op2, rst;
	for(int i=0; i<postLen; i++)
	{
		if( !IsOperator(postFix[i][0]) )
		{
			PushFloat(atof(postFix[i]), operant);
		}
		else
		{
			op1 = TopFloat(operant);
			PopFloat(operant);
			op2 = TopFloat(operant);
			PopFloat(operant);
			switch(*postFix[i])
			{
				case '+': rst = op2+op1; break;
				case '-': rst = op2-op1; break;
				case '*': rst = op2*op1; break;
				case '/': rst = op2/op1; break;
			}
			PushFloat(rst, operant);
		}
		//PrintFloatStack(operant);
	}
	out = TopFloat(operant);
}

int main(int argc, char const *argv[])
{
	char* inFix =  new char[50];
	char** postFix = new char*[50]; //因为不能保证每一个操作数都是一位数
	for (int i=0; i<50; i++)
	{
		postFix[i] = new char[5]; //假设最大能计算五位数的数字
	}
	int len;
	int postLen = 0;
	
	cout << "+ please input the infix with the end of '=', " << endl
			<< "+ furthermore, brackets, float and long number are all tolerable: " << endl;;
	InPut(inFix, len);
	
	InFixToPostFix(inFix, len, postFix, postLen);
	cout << "+ PostFix: ";
	for(int i=0; i<postLen; i++)
	{
		cout << postFix[i] << " ";
	}
	cout << endl;
	float out;
	CountPostFix(postFix, postLen, out);
	cout << "+ Result: " << out << endl;

	return 0;
}