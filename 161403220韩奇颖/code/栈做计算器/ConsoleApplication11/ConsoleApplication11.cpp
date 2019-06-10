// ConsoleApplication11.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"
#include <iostream>  
#include<math.h>
#include <string>
#include "stack.h"  
using namespace std;

//ɨ�����ֵĺ���  
bool isnumber(char x) {
	if (x >= '0' && x <= '9')
		return true;
	return false;
}

//�ж���������ȼ��ĺ���  
int priority(char x) {
	if (x == '+' || x == '-')
		return 0;
	else if (x == '*' || x == '/')
		return 1;
	else if (x == '(' || x == ')')
		return -1;
	else if (x == '#')
		return -2;
}

//����ĺ���  
int calculate(string s) {
	stack<int> number;
	stack<char> operate;
	char top;
	int a, b;

	for (unsigned int i = 0; i < s.size(); ++i) {
		if (isnumber(s[i])) {
			int Temp = 0;
			string temp;

			temp += s[i];
			while (isnumber(s[++i]))
				temp += s[i];
			for (unsigned int j = 0; j < temp.size(); ++j) {
				Temp = Temp * 10 + temp[j] - 48;
			}
			number.push(Temp);
			temp.clear();
		}//���ַ�����ת������������  
		if (!isnumber(s[i])) {
			if (operate.empty()) {
				operate.push(s[i]);
			}//��ջ��һ������'#'  
			else {
				operate.get_top(top);

				if (priority(s[i])>priority(top) || s[i] == '(') {
					operate.push(s[i]);
				}//��ջ�����ȼ��������  
				else {
					while (priority(s[i]) <= priority(top)) {
						if (top == '#'&&s[i] == '#') {
							int answer;

							operate.pop();
							number.get_top(answer);
							cout << "\n���ǣ�" << answer << endl;
							number.pop();
							return 0;
						}//�������ʵ����ȫ��ֻʣ��'#'  
						else if (top == '('&&s[i] == ')') {
							++i;
						}//��������������ʱ�����������ţ�ɾ��������  
						else {
							number.get_top(a);
							number.pop();
							number.get_top(b);
							number.pop();
						}
						if (top == '+') {
							b += a;
							number.push(b);
						}
						else if (top == '-') {
							b -= a;
							number.push(b);
						}
						else if (top == '*') {
							b *= a;
							number.push(b);
						}
						else if (top == '/') {
							b /= a;
							number.push(b);
						}
						operate.pop();
						operate.get_top(top);//ȡǰһ�������������������ɨ�����������бȽ�    
					}//�����ȼ��ߵ������ʵ�ּ���  
					operate.push(s[i]);//���ڵ�top=='#'ʱ�������һ���������ջ  
				}
			}
		}//ɨ������������ж����ȼ����Լ�����  
	}//��ѭ��  
}//���������ɨ�裬�������ַ���ת�����Լ�����  

int main() {
	string expression;
	cout << "����һ����'#'��ͷ�ͽ�β�ı��ʽ��" << endl;

	cin>>expression;
	calculate(expression);
	cin.get(), cin.get();
	system("pause");
}
