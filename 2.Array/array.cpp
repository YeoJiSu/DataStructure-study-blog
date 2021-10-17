#include <vector> 
#include <algorithm> 
#include <iostream> 
#include <stdlib.h>
#include <math.h> //Eval 함수 계산을 위해 추가 

using namespace std; 
class Polynomial; 
class Term
{
        friend Polynomial; 
        friend ostream & operator << (ostream &os,const Polynomial &p);
    private:
        float coef;
        int exp;
};
class Polynomial { 
    public:
        Polynomial();
        friend istream& operator >> (istream& is, Polynomial& p); // 첫번째 조건 , 다항식의 입력 구현 완료 
        friend ostream& operator << (ostream& os, const Polynomial& p);  // 두번째 조건 , 다항식의 출력 구현 완료 
        Polynomial Add(Polynomial b); // 세번째 조건 , add 구현 완료 
        int Substract(Polynomial a, Polynomial b); // 네번째 조건, sub 구현  완료    
        int Multiply(Polynomial a, Polynomial b); // 다섯번째 조건, multiply 구현 완료 
        // Polynomial Mult(Polynomial b)을 구현하라고 나와있긴 한데 main 함수에서 Mult()를 쓰는 건 없고, P3.Multiply(P1,P2) 입력
        float Eval(float f); // 여섯번째 조건, eval 구현 완료 
        void NewTerm(const float theCoeff, const int theExp); 
        int Display();
        int GetData();
        
        // + 연산자도 구현했습니다.
        Polynomial operator+ (const Polynomial& p) const {
            Polynomial c;
            int aPos = start, bPos = p.start;
            c.start = free;
            while ((aPos <= finish) && (bPos <= p.finish))
            {
                if (termArray[aPos].exp == p.termArray[bPos].exp)
                {
                    float t = termArray[aPos].coef + p.termArray[bPos].coef; 
                    if (t) c.NewTerm(t, termArray[aPos].exp);
                    aPos++; bPos++;
                }
                else if ((termArray[aPos].exp < p.termArray[bPos].exp)) 
                {
                    c.NewTerm(p.termArray[bPos].coef, p.termArray[bPos].exp); 
                    bPos++;
                }
                else
                {
                    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                    aPos++;
                }
            }
            for (; aPos <= finish; aPos++)
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp); 
            for (; bPos <= p.finish; bPos++)
                c.NewTerm(p.termArray[bPos].coef, p.termArray[bPos].exp); 
            c.finish = free - 1;
            return c;
        }

        // - 연산자도 구현했습니다. 
        Polynomial operator- (const Polynomial& p) const {
            Polynomial c;
            int aPos = start, bPos = p.start;
            c.start = free;
            while ((aPos <= finish) && (bPos <= p.finish))
            {
                if (termArray[aPos].exp == p.termArray[bPos].exp)
                {
                    float t = termArray[aPos].coef - p.termArray[bPos].coef; 
                    if (t) c.NewTerm(t, termArray[aPos].exp);
                    aPos++; bPos++;
                }
                else if ((termArray[aPos].exp < p.termArray[bPos].exp)) 
                {
                    c.NewTerm(-1*p.termArray[bPos].coef, p.termArray[bPos].exp); 
                    bPos++;
                }
                else
                {
                    c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                    aPos++;
                }
            }
            for (; aPos <= finish; aPos++)
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp); 
            for (; bPos <= p.finish; bPos++)
                c.NewTerm(-1*p.termArray[bPos].coef, p.termArray[bPos].exp); 
            c.finish = free - 1;
            return c;
        }

        // * 연산자도 구현했습니다. 
        Polynomial operator* (const Polynomial& p) const {
            Polynomial c;
            int aPos = start, bPos = p.start;
            c.start = free;
            for (int i=aPos;i<=finish;i++)
            {
              for (int j=bPos;j<=p.finish;j++)
              {
                float coef=termArray[i].coef * p.termArray[j].coef;
                float exp =termArray[i].exp + p.termArray[j].exp;
                if (coef) c.NewTerm(coef, exp);
              }
            } 
            c.finish = free - 1;
            return c;
        }
    // class Polynomial의 data representation은 변경하지 않았습니다. 
    private:
        static Term* termArray;
        static int capacity; 
        static int free; 
        int start, finish; 
        int terms;
}; 

//아래를 구현했음
ostream& operator << (ostream& os, const Polynomial& p){
   int aPos = p.start;
    for (; aPos <= p.finish; aPos++) {
        os << p.termArray[aPos].coef << "x^" << p.termArray[aPos].exp; 
        if ((aPos - p.finish) != 0)
            os << " + ";
    }
    os << "\n"; 
    return os;
}

istream& operator >> (istream& is, Polynomial& p){
    int i, degree;
    float coef;
    int expo;
    cout << "Enter Degree Of Polynomial:"; 
    is >> degree;
    p.start = p.free;
    for (i = degree; i > 0; i--) {
        cout << "Enter coefficient of x^" << i << ":"; 
        is >> coef;
        cout << "Enter exponent of x^" << i << ":"; 
        is >> expo;
        p.NewTerm(coef, expo);
    }
    p.finish = p.free - 1;
    p.terms = p.finish - p.start + 1; 
    return is;
}

Polynomial::Polynomial() 
{
    start = -1; 
    finish = -1; 
    terms = 0;
}
int Polynomial::Display() 
{
    int aPos = start;
    for (; aPos <= finish; aPos++) {
        cout << termArray[aPos].coef << "x^" << termArray[aPos].exp; 
        if ((aPos - finish) != 0)
            cout << " + ";
    }
    cout << "\n"; 
    return 0;
}
void Polynomial::NewTerm(const float theCoeff, const int theExp) 
{
    if (terms == capacity) 
    {
        capacity *= 2;
        Term* temp = new Term[capacity]; 
        copy(termArray, termArray + free, temp); 
        delete[] termArray;
        termArray = temp;
    }
    termArray[free].coef = theCoeff; 
    termArray[free++].exp = theExp;
}
int Polynomial::GetData() {
    int i, degree;
    float coef;
    int expo;
    cout << "Enter Degree Of Polynomial:"; 
    cin >> degree;
    start = free;
    for (i = degree; i > 0; i--) {
        cout << "Enter coefficient of x^" << i << ":"; 
        cin >> coef;
        cout << "Enter exponent of x^" << i << ":"; 
        cin >> expo;
        NewTerm(coef, expo);
    }
    finish = free - 1;
    terms = finish - start + 1; 
    return 0;
}
Polynomial Polynomial::Add(Polynomial b) {
    int aPos = start, bPos = b.start;
    start = free;
    while ((aPos <= finish) && (bPos <= b.finish))
    {
        if (termArray[aPos].exp == b.termArray[bPos].exp)
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef; 
            if (t) NewTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp)
        {
            NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp); 
            bPos++;
        }
        else
        {
            NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos <= finish; aPos++)
        NewTerm(termArray[aPos].coef, termArray[aPos].exp); 
    for (; bPos <= b.finish; bPos++)
        NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp); 
    finish = free - 1;
    return *this ;
}
int Polynomial::Substract(Polynomial a, Polynomial b){
    Polynomial c;
    int aPos = a.start, bPos = b.start;
    c.start = free;
    while ((aPos <= a.finish) && (bPos <= b.finish))
    {
        if (a.termArray[aPos].exp == b.termArray[bPos].exp)
        {
            float t = a.termArray[aPos].coef - b.termArray[bPos].coef; 
            if (t) c.NewTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if ((a.termArray[aPos].exp < b.termArray[bPos].exp)) 
        {
            c.NewTerm(-1*b.termArray[bPos].coef, b.termArray[bPos].exp); 
            bPos++;
        }
        else
        {
            c.NewTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos <= a.finish; aPos++)
        c.NewTerm(a.termArray[aPos].coef, a.termArray[aPos].exp); 
    for (; bPos <= b.finish; bPos++)
        c.NewTerm(-1*b.termArray[bPos].coef, b.termArray[bPos].exp); 
    c.finish = free - 1;
    c.Display(); 
    return 0;
}

int Polynomial::Multiply(Polynomial a, Polynomial b){
  Polynomial c;
  int aPos = a.start, bPos = b.start;
  c.start = free;
  for (int i=aPos;i<=a.finish;i++)
  {
    for (int j=bPos;j<=b.finish;j++)
    {
      float coef=a.termArray[i].coef*b.termArray[j].coef;
      float exp =a.termArray[i].exp + b.termArray[j].exp;
      if (coef) c.NewTerm(coef, exp);
    }
  } 
  c.finish = free - 1;
  c.Display(); 
  return 0;
}
float Polynomial::Eval(float f){
  float result=0;
  for (int i = start;i<=finish;i++)
  {
    result += termArray[i].coef*pow(f,termArray[i].exp);
  }
  cout<<result;
  return result;
}

int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100]; 
int Polynomial::free = 0;

int main(void) {
    int choice;
    Polynomial P1, P2, P3, P4;
    cout << "Instruction:- \nExample:-\nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x)=5x^3+0x^2+3x^1+0x^0 \n";
    cout << "Enter Polynomial1:-" << endl;
    //P1.GetData();
    cin >> P1;
    cout << "Enter Polynomial2:-" << endl; 
    //P2.GetData();
    cin >> P2;
    cout << "Enter Polynomial3:-" << endl; 
    cin >> P3;

    while (1) {
        cout << "\n****** Menu Selection ******" << endl;
        cout << "1: Addition\n2: Substraction\n3: Multiplication\n4: Eval\n0: Exit" << endl; 
        cout << "Enter your choice:";
        cin >> choice; switch (choice) { 
            case 1:
                cout << "\n--------------- Addition ---------------\n"; 
                cout << "Polynomial1:";
                //P1.Display();
                cout << P1;
                cout << "Polynomial2:"; 
                //P2.Display();
                cout << P2;
                cout << "Polynomial3:"; 
                //P3.Display();
                cout << P3;

                //P3 = P1.Add(P2); //구현 완료 
                //cout << "P1+P2= ";
                //P3.Display();
                
                P4=P1+P2+P3;
                cout << "P1+P2+P3 = ";
                cout << P4;
                cout << "---------------------------------------- \n"; 
                break;
            case 2:
                cout << "\n------------- Substraction -------------\n"; 
                cout << "Polynomial1:";
                //P1.Display();
                cout << P1;
                cout << "Polynomial2:";
                //P2.Display();
                cout << P2;
                
                cout<< "P3.Substract(P1, P2) = ";
                P3.Substract(P1, P2);
                cout<< "P1-P2 = ";
                P4 = P1 - P2; 
                cout << P4;
                cout << "---------------------------------------- \n"; break;
            case 3:
                cout << "\n----------- Multiplication -------------\n"; 
                cout << "Polynomial1:";
                //P1.Display();
                cout << P1;
                cout << "Polynomial2:"; 
                //P2.Display();
                cout << P2;
            
                cout<< "P3.Multiply(P1, P2) = ";
                P3.Multiply(P1, P2); 
                cout<<endl;

                cout<< "P1*P2 = ";
                P3=P1*P2;   
                //P3.Display(); 
                cout << P3;

                cout << "---------------------------------------- \n"; 
                break;
            case 4: 
                //P2.Eval(5); 학생 구현 실습 대상
                //cout << P4; 
                cout<<"P2(3) = ";
                P2.Eval(3);
                break;
            case 0:
                cout << "Good Bye...!!!" << endl;
                exit(0);
        }
    }
    system("pause");
    return 0;
}