#include <iostream>
using namespace std;

struct B{ };  //可类比为 InputIterator
struct D1 : public B { };//可类比为 ForwardIterator
struct D2 : public D1 { }; //可类比为 BidirectionalIterator

template<class T>
void func(T& p, B)
{
	cout << "B version" << endl;
}


template<class T>
void func(T& p, D2)
{
	cout << "D2 version" << endl;
}


int main()
{
	int* p;
	func(p, B());       //参数完全吻合，输出 “B Version”  
	func(p, D1());      //参数未能完全吻合，因继承关系而自动传递调用，输出“B Version”
	func(p, D2());      //参数完全吻合，输出 “D2 Version” 
	 
	return 0;
}