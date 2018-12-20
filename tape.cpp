
#include "tape.h"

using namespace std;

#ifndef uint
#define uint unsigned int
#endif

Node::Node(const float w1, const uint a, const float w2, const uint b)
{
	this->w1 = w1;
	this->w2 = w2;
	this->a = a;
	this->b = b;
}

Var::Var(Tape* const t, const uint i, const float x)
{
	val = x;
	id = i;
	tape = t;
}

void Var::grad(Grad& grad)
{
	const uint n = tape->size();
	grad.d = vector<float>(n, 0);
	grad.d[id] = 1;

	for (int i = n-1; i >= 0; i--)
	{
		const float d = grad.d[i];
		const Node* node = tape->get(i);

		grad.d[node->a] += node->w1 * d;
		grad.d[node->b] += node->w2 * d;
	}
}

Var& Var::operator=(const Var& x)
{
	val = x.val;
	id = x.id;
	tape = x.tape;
	return *this;
}

Var& Var::operator+=(const Var& b){
	id = tape->push(1, id, 1, b.id);
	val += b.val;
	return *this;
}
Var& Var::operator-=(const Var& b){
	id = tape->push(1, id, -1, b.id);
	val -= b.val;
	return *this;
}
Var& Var::operator*=(const Var& b){
	id = tape->push(b.val, id, val, b.id);
	val *= b.val;
	return *this;
}
Var& Var::operator/=(const Var& b){
	id = tape->push(1/b.val, id, -val/(b.val * b.val), b.id);
	val /= b.val;
	return *this;
}
Var& Var::operator^=(const Var& b){
	id = tape->push(b.val * pow(val, b.val-1), id, pow(val, b.val) * log(val), b.id);
	val = pow(val, b.val);
	return *this;
}

Var& Var::operator+=(const float b){
	id = tape->push(1, id, 1, 0);
	val += b;
	return *this;
}
Var& Var::operator-=(const float b){
	id = tape->push(1, id, -1, 0);
	val -= b;
	return *this;
}
Var& Var::operator*=(const float b){
	id = tape->push(b, id, val, 0);
	val *= b;
	return *this;
}
Var& Var::operator/=(const float b){
	id = tape->push(1/b, id, -val/(b * b), 0);
	val /= b;
	return *this;
}
Var& Var::operator^=(const float b){
	id = tape->push(b * pow(val, b-1), id, pow(val, b) * log(val), 0);
	val = pow(val, b);
	return *this;
}

Tape::Tape() {
	nodes.push_back(Node());
}

Var Tape::var(const float x, const float w1, const uint a, const float w2, const uint b) {
	nodes.push_back(Node(w1, a, w2, b));
	return Var(this, nodes.size()-1, x);
}

uint Tape::push(const float w1, const uint a, const float w2, const uint b)
{
	nodes.push_back(Node(w1, a, w2, b));
	return nodes.size()-1;
}

#ifdef uint
#undef uint
#endif