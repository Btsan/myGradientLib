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

	cout << "c = (ab + a + sin(b)a)/b\n";
	Var c = (a * b + a * 1 + a * sin(b)) / b;

	cout << "c += log(a)\n";
	c += log(a);

	cout << "\ncalculating gradient of c:\n";
	Grad d;
	c.grad(d);

	cout << "dc/da = " << d.wrt(a) << " \tcorrect answer: 1.88037...\ndc/db = " << d.wrt(b) << " \tcorrect answer: -0.9135..." << endl;

	cout << "\ne = c - a\n";
	Var e = c - a;

	cout << "f = c + ab\n";
	Var f = c + b * a;

	cout << "\ncalculating gradient of e:\n";
	e.grad(d);

	cout << "de/da = " << d.wrt(a) << " \tcorrect answer: 0.88037...\nde/db = " << d.wrt(b) << " \tcorrect answer: -0.9135..." << endl;

	cout << "\ncalculating gradient of f:\n";
	f.grad(d);

	cout << "df/da = " << d.wrt(a) << " \tcorrect answer: 4.88037...\ndf/db = " << d.wrt(b) << " \tcorrect answer: 1.086..." << endl;

	t.clear();
	a = t.var(2);
	b = t.var(3);

	cout << "\ng = sin(a) + cos(a) + tan(a) + sec(a) + csc(a) + cot(a) + sinh(a) + cosh(a) + tanh(a) + sech(a) + csch(a) + coth(a)\n";
	Var g = sin(a) + cos(a) + tan(a) + sec(a) + csc(a) + cot(a) + sinh(a) + cosh(a) + tanh(a) + sech(a) + csch(a) + coth(a) + atan(a);

	cout << "\ncalculating gradient of g:\n";
	g.grad(d);

	cout << "dg/da = " << d.wrt(a) << " \tcorrect answer: 15.8348...\ndg/db = " << d.wrt(b) << " \tcorrect answer: 0" << endl;

	cout << "\nh = (e^log10(b))^2 + a\n";
	Var h = a + (exp(log(b, 10))^2);

	cout << "\ncalculating gradient of h:\n";
	h.grad(d);
	cout << "dh/da = " << d.wrt(a) << " \tcorrect answer: 1\ndh/db = " << d.wrt(b) << " \tcorrect answer: 0.7518..." << endl;

	cout << "\ni = sinc(a) + sigmoid(b)\n";
	Var i = sinc(a) - sigmoid(b);

	cout << "\ncalculating gradient of i:\n";
	i.grad(d);
	cout << "di/da = " << d.wrt(a) << " \tcorrect answer: -0.43539...\ndi/db = " << d.wrt(b) << " \tcorrect answer: -0.04517..." << endl;

	t.clear();
	a = t.var(0);
	b = t.var(1);

	cout << "a = 0\n";
	cout << "b = 1\n";
	cout << "m = asin(b) + acos(a) + atan(a)\n";
	Var m = asin(b) + acos(a) + atan(a);

	cout << "\ncalculating gradient of m:\n";
	m.grad(d);
	cout << "dm/da = " << d.wrt(a) << " \tcorrect answer: 0\ndm/db = " << d.wrt(b) << " \tcorrect answer: 1/0" << endl;
	
	return 0;
}