
#include "tape.h"

using namespace std;

#ifndef uint
#define uint unsigned int

Node::Node(const float w1, const uint a, const float w2, const uint b) {
	this->w1 = w1;
	this->w2 = w2;
	this->a = a;
	this->b = b;
}


Var::Var(Tape* const t, const uint i, const float x) {
	val = x;
	id = i;
	tape = t;
}

void Var::grad(Grad& g) {
	const uint n = tape->size();
	g.d.clear();
	g.d.resize(n, 0);
	g.d[id] = 1;

	for (int i = id; i >= 0; i--)
	{
		const float d = g.d[i];
		
		if (d != 0)
		{
			const Node* node = tape->get(i);
			g.d.at(node->a) += node->w1 * d;
			g.d.at(node->b) += node->w2 * d;
		}
	}
}

Grad Var::grad() {
	Grad g;

	g.d = vector<float>(tape->size(), 0);
	float part = g.d[id] = 1;

	for (int i = id; i >= 0; i--) {
		part = g.d[i];
		
		if (part != 0) {
			const Node* node = tape->get(i);

			g.d[node->a] += node->w1 * part;
			g.d[node->b] += node->w2 * part;
		}
	}

	return g;
}

Var& Var::operator=(const Var& x) {
	val = x.val;
	id = x.id;
	tape = x.tape;
	return *this;
}

Var& Var::operator+=(const Var& b) {
	id = tape->push(1, id, 1, b.id);
	val += b.val;
	return *this;
}
Var& Var::operator-=(const Var& b) {
	id = tape->push(1, id, -1, b.id);
	val -= b.val;
	return *this;
}
Var& Var::operator*=(const Var& b) {
	id = tape->push(b.val, id, val, b.id);
	val *= b.val;
	return *this;
}
Var& Var::operator/=(const Var& b) {
	id = tape->push(1/b.val, id, -val/(b.val * b.val), b.id);
	val /= b.val;
	return *this;
}
Var& Var::operator^=(const Var& b) {
	id = tape->push(b.val * pow(val, b.val-1), id, pow(val, b.val) * log(val), b.id);
	val = pow(val, b.val);
	return *this;
}

Var& Var::operator+=(const float b) {
	id = tape->push(1, id, 1, 0); // dz/da, dz/db
	val += b;
	return *this;
}
Var& Var::operator-=(const float b) {
	id = tape->push(1, id, -1, 0);
	val -= b;
	return *this;
}
Var& Var::operator*=(const float b) {
	id = tape->push(b, id, val, 0);
	val *= b;
	return *this;
}
Var& Var::operator/=(const float b) {
	id = tape->push(1/b, id, -val/(b * b), 0);
	val /= b;
	return *this;
}
Var& Var::operator^=(const float b) {
	id = tape->push(b * pow(val, b-1), id, pow(val, b) * log(val), 0);
	val = pow(val, b);
	return *this;
}

Tape::Tape() {
	nodes.reserve(128);
	nodes.push_back(Node()); // I don't know why this needs to be here to work
}

Var Tape::var(const float x, const float w1, const uint a, const float w2, const uint b) {
	nodes.push_back(Node(w1, a, w2, b));
	return Var(this, nodes.size()-1, x);
}

uint Tape::push(const float da, const uint a, const float db, const uint b) {
	nodes.push_back(Node(da, a, db, b));
	return nodes.size()-1;
}

#undef uint
#endif