#include <iostream>
#include "tape.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Tape t;

	cout << "a = 2\n";
	Var a = t.var(2);

	cout << "b = 3\n";
	Var b = t.var(3);

	cout << "c = (ab + a + sin(b))/b\n";
	Var c = (a * b + a * 1 + a * sin(b)) / b;

	cout << "c += log(a)\n";
	c += log(a);

	cout << "\ncalculating gradient of c:\n";
	Grad d;
	c.grad(d);

	cout << "a = 2, b = 3\nc = (ab + a + sin(b))/b + log(a)\ndc/da = " << d.wrt(a) << " \tcorrect answer: 1.88037...\n\n";

	cout << "e = c - a\n";
	Var e = c - a;

	cout << "\ncalculating gradient of e:\n";
	e.grad(d);

	cout << "e = c - a\ne = (ab + a + sin(b))/b + log(a) - a\ndc/da = " << d.wrt(a) << " \tcorrect answer: 0.88037..." << endl;

	return 0;
}