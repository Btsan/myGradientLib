#ifndef TAPE_H
#define TAPE_H

#include <vector>
#include <cmath>

#ifndef uint
#define uint unsigned int
#endif

struct Tape;
struct Grad;

struct Node 
{
	float w1, w2;
	uint a, b;
	Node(const float = 0, const uint = 0, const float = 0, const uint = 0);
};

struct Var
{
	Tape* tape;
	uint id;
	float val;
	Var(Tape* const, const uint, const float);

	void grad(Grad&);

	Var& operator=(const Var&);
	Var& operator+=(const Var&);
	Var& operator-=(const Var&);
	Var& operator*=(const Var&);
	Var& operator/=(const Var&);
	Var& operator^=(const Var&);

	Var& operator+=(const float);
	Var& operator-=(const float);
	Var& operator*=(const float);
	Var& operator/=(const float);
	Var& operator^=(const float);
};

struct Tape
{
	std::vector<Node> nodes;
	Tape();

	Var var(const float, const float = 0, const uint = 0, const float = 0, const uint = 0);
	uint push(const float = 0, const uint = 0, const float = 0, const uint = 0);
	inline Node* get(const uint id)
	{
		return &nodes[id];
	}

	inline uint size()
	{
		return nodes.size();
	}
};

struct Grad
{
	std::vector<float> d;
	inline float wrt(const Var& x)
	{
		return d[x.id];
	}
};

inline Var operator+(Var lhs, const Var& rhs){
	lhs += rhs;
	return lhs;
}
inline Var operator-(Var lhs, const Var& rhs){
	lhs -= rhs;
	return lhs;
}
inline Var operator*(Var lhs, const Var& rhs){
	lhs *= rhs;
	return lhs;
}
inline Var operator/(Var lhs, const Var& rhs){
	lhs /= rhs;
	return lhs;
}
inline Var operator^(Var lhs, const Var& rhs){
	lhs ^= rhs;
	return lhs;
}

inline Var operator+(Var lhs, const float rhs){
	lhs += rhs;
	return lhs;
}
inline Var operator-(Var lhs, const float rhs){
	lhs -= rhs;
	return lhs;
}
inline Var operator*(Var lhs, const float rhs){
	lhs *= rhs;
	return lhs;
}
inline Var operator/(Var lhs, const float rhs){
	lhs /= rhs;
	return lhs;
}
inline Var operator^(Var lhs, const float rhs){
	lhs ^= rhs;
	return lhs;
}

inline Var sin(const Var& x){
	return x.tape->var(sin(x.val), cos(x.val), x.id);
}
inline Var cos(const Var& x){
	return x.tape->var(cos(x.val), -sin(x.val), x.id);
}

inline Var exp(const Var& x){
	return x.tape->var(exp(x.val), exp(x.val), x.id);
}
inline Var log(const Var& x){
	return x.tape->var(log(x.val), 1/x.val, x.id);
}

#ifdef uint
#undef uint
#endif

#endif