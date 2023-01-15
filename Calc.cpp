#include<iostream>
#include<stack>
using namespace std;
class EVexp {
    char sgreater(char x,char y) {
        if ((x=='+'||x=='-')&&(y=='*'||y=='/'))
        {
            return y;
        }
        else if ((y=='+'||y=='-')&&(x=='*'||x=='/'))
            return x;
        else
            return '-1';
    }

    string transform(string exp) {
        stack <char>s;
        string str="";
        for(int i=0; i<exp.length(); i++) {
            if (isdigit(exp[i])||exp[i]=='.'||((exp[i]=='-'||exp[i]=='+')&&(i==0||!isdigit(exp[i-1])))) {
                str+=exp[i];
                if (!isdigit(exp[i+1])&&exp[i+1]!='.') {
                    str+=',';
                }
            }
            else {
                if (exp[i]=='(')
                    s.push(exp[i]);
                else if (exp[i]==')') {
                    while(s.top()!='(') {
                        str+=s.top();
                        str+=',';;
                        s.pop();
                    }
                    s.pop();
                }
                else {
                    if (s.empty())
                        s.push(exp[i]);
                    else {
                        if (sgreater(exp[i],s.top())==exp[i]) {
                            s.push(exp[i]);
                        }
                        else {
                            while(!s.empty()&&s.top()!='('&&sgreater(exp[i],s.top())!=exp[i]) {
                                str+=s.top();
                                str+=',';
                                s.pop();
                            }
                            s.push(exp[i]);
                        }
                    }
                }
            }
        }
        while (!s.empty()) {
            str+=s.top();
            s.pop();
            if (!s.empty())
                str+=',';
        }
        return str;
    }
public:
    float eval(string e) {
        string exp=transform (e);
        stack <float>s;
        float result=0;
        float n1,n2;
        float ns=0;
        bool sign=0;
        for(int i=0; i<exp.length(); i++) {
            if (isdigit(exp[i])||exp[i]=='.'||(exp[i]=='+'||exp[i]=='-')&&(isdigit(exp[i+1])||exp[i+1]=='.')) {
                if(exp[i]=='-') {
                    sign=1;
                    continue;
                }
                else if (exp[i]=='+')continue;

                int c=i;
                int dot=10;
                while (exp[c]!=',') {

                    if(exp[c]=='.') {
                        c++;
                        while(exp[c]!=',') {

                            float f=exp[c]-'0';
                            f=f/dot;
                            dot*=10;
                            ns+=f;
                            c++;

                        }

                        dot=10;
                        break;
                    }
                    ns*=10;
                    ns+=(exp[c]-'0');
                    c++;
                }

                i=c;
                if (sign) {
                    sign=0;
                    ns*=-1;
                }
                s.push(ns+'0');
                ns=0;
            }
            else {
                if (exp[i]==',')
                    continue;
                n2=s.top()-'0';
                s.pop();
                n1=s.top()-'0';
                s.pop();
                switch(exp[i]) {
                case '+':
                    n1=n1+n2;
                    break;
                case '-':
                    n1=n1-n2;
                    break;
                case '*':
                    n1=n1*n2;
                    break;
                case '/':
                    n1=n1/n2;
                    break;
                }
                s.push(n1+'0');

            }
        }
        result=s.top()-'0';
        return result;
    }
};
int main()
{
    EVexp e;
    string exp;
    cout<< "Enter An Operation: " ;
    cin>>exp;
    cout << e.eval(exp);
    return 0;
}