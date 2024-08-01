// #include <iostream>

// class A {
//     public:
//     explicit A(int a)
//     : k (a) {}

//     virtual int getk() const { return k;}

//     int k;
// };

// class B : public virtual A {
//     public:
//     explicit B(int a, int b, int c)
//     : A(a+b), l(c) {}
//     virtual int getk() const {return k;}

//     int l;
// };

// class C : public virtual A {
//     public:
//     explicit C(int a, int b, int c)
//     : A(a), m(b+c) {}

//     virtual int getk() const { return k;}

//     int m;
// };

// class D : public B, public C {
//     public:
//     explicit D(int a, int b, int c, int d)
//     : A(a+c), B(a,b,c), C(b,c,d), n(a+b) {}

//     int getk() const {return k;}

//     int n;
// };

// int main(){
//     using namespace std;
//     int a,b,c,d;
//     std::cin >> a;
//     std::cin >> b;
//     std::cin >> c;
//     std::cin >> d;

//     A _a(a);
//     B _b(a,b,c);
//     C _c(b,c,d);
//     D _d(a,b,c,d);

//     std::cout << _d.getk() << ' ' << _c.getk() << ' ' << _b.getk() << ' ' <<
//     _a.getk() << ' ' << std::endl;
//     return 0;
// }

#include <iostream>
#include <string>

using namespace std;

class Solution{
    public:
string getRoman(int n){
    string ret_string;
    int residue = 0;
    while(n>0){
        cout << n << "------" << endl;
        if(n>=1000){
            residue = n/1000;
            n %= 1000;
            for(int i =0; i< residue; ++i) ret_string.push_back('M');
        } else if(n>=900){
            n%=900;
            ret_string.push_back('C');
            ret_string.push_back('M');
        } else if(n>=500){
            n%=500;
            ret_string.push_back('D');
        } else if(n>=400){
            n%=400;
            ret_string.push_back('C');
            ret_string.push_back('D');
        } else if(n>=100){
            residue = n/100;
            n %= 100;
            for(int i =0; i< residue; ++i) ret_string.push_back('C');
        } else if(n>=90){
            n%=90;
            ret_string.push_back('X');
            ret_string.push_back('C');
        } else if(n>=50){
            n%=50;
            ret_string.push_back('L');
        } else if(n>=40) {
            n%=40;
            ret_string.push_back('X');
            ret_string.push_back('L');
        } else if(n>=10){
            residue = n/10;
            n %= 10;
            for(int i =0; i< residue; ++i) ret_string.push_back('X');
        } else if(n>=9){
            n%=9;
            ret_string.push_back('I');
            ret_string.push_back('X');
        } else if(n>=5) {
            n%=5;
            ret_string.push_back('V');
        } else if(n>=4) {
            n%=4;
            ret_string.push_back('I');
            ret_string.push_back('V');
        } else if(n>=1){
            residue = n/1;
            n %= 1;
            for(int i =0; i< residue; ++i) ret_string.push_back('I');
        }
    }
    return ret_string;
}
};

int main(){
    int n;
    cin >> n;
    Solution s;
    cout << s.getRoman(n) << endl;
    return 0;
}