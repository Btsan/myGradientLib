#ifndef TAPE_H
#define TAPE_H

#include <vector>
#include <cmath>

#ifndef uint
#define uint unsigned int

struct Tape;
struct Grad;

struct Node
{
	float w1, w2;
	uint a, b;
	Node(const float = 0, const uint = 0, const float = 0, const uint = 0);

	inline void set(const float w1, const float w2)
	{
		this->w1 = w1;
		this->w2 = w2;
	}
};

struct Var
{
	Tape* tape;
	uint id;
	float val;
	Var(Tape* const, const uint = 0, const float = 0);

	void grad(Grad&);
	Grad grad();

	Var& operator=(const Var&);
	Var& operator+=(const Var&);
	Var& operator-=(const Var&);
	Var& operator*=(const Var&);
	Var& operator/=(const Var&);
	Var& operator^=(const Var&);

	Var& operator=(const float);
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

	inline Node* get(const uint id) {return &nodes[id];}
	inline uint size() {return nodes.size();}
	inline void clear() {nodes.resize(1);} // I don't know why, but this doesn't work correctly without an initial dummy node
};

struct Grad
{
	std::vector<float> d;

	inline float wrt(const Var& x) {return (x.id < d.size())? d[x.id] : 0;}
};

inline Var operator+(Var lhs, const Var& rhs)
{
	lhs += rhs;
	return lhs;
}
inline Var operator-(Var lhs, const Var& rhs)
{
	lhs -= rhs;
	return lhs;
}
inline Var operator*(Var lhs, const Var& rhs)
{
	lhs *= rhs;
	return lhs;
}
inline Var operator/(Var lhs, const Var& rhs)
{
	lhs /= rhs;
	return lhs;
}
inline Var operator^(Var lhs, const Var& rhs)
{
	lhs ^= rhs;
	return lhs;
}

inline Var operator+(Var lhs, const float rhs)
{
	lhs += rhs;
	return lhs;
}
inline Var operator-(Var lhs, const float rhs)
{
	lhs -= rhs;
	return lhs;
}
inline Var operator*(Var lhs, const float rhs)
{
	lhs *= rhs;
	return lhs;
}
inline Var operator/(Var lhs, const float rhs)
{
	lhs /= rhs;
	return lhs;
}
inline Var operator^(Var lhs, const float rhs)
{
	lhs ^= rhs;
	return lhs;
}

inline Var sin(const Var& x)
{
	return x.tape->var(sin(x.val), cos(x.val), x.id);
}
inline Var cos(const Var& x)
{
	return x.tape->var(cos(x.val), -sin(x.val), x.id);
}
inline Var tan(const Var& x)
{
	return x.tape->var(tan(x.val), 1/pow(cos(x.val), 2), x.id);
}
inline Var sec(const Var& x)
{
	return x.tape->var(1/cos(x.val), tan(x.val)/cos(x.val), x.id);
}
inline Var csc(const Var& x)
{
	return x.tape->var(1/sin(x.val), -1/(sin(x.val) * tan(x.val)), x.id);
}
inline Var cot(const Var& x)
{
	return x.tape->var(1/tan(x.val), -1/pow(sin(x.val), 2), x.id);
}
inline Var asin(const Var& x)
{
	return x.tape->var(asin(x.val), 1/sqrt(1 - x.val * x.val), x.id);
}
inline Var acos(const Var& x)
{
	return x.tape->var(acos(x.val), -1/sqrt(1 - x.val * x.val), x.id);
}
inline Var atan(const Var& x)
{
	return x.tape->var(atan(x.val), 1/(1 + x.val * x.val), x.id);
}
inline Var sinh(const Var& x)
{
	const float ex = exp(x.val);
	const float y = (ex - 1/ex)/2;
	return x.tape->var(y, y + 2/ex, x.id);
}
inline Var cosh(const Var& x)
{
	const float ex = exp(x.val);
	const float y = (ex + 1/ex)/2;
	return x.tape->var(y, y - 2/ex, x.id);
}
inline Var tanh(const Var& x)
{
	const float ex = exp(x.val);
	const float y = (ex - 1/ex)/(ex + 1/ex);
	return x.tape->var(y, 1 - y * y, x.id);
}
inline Var sech(const Var& x)
{
	const float ex = exp(x.val);
	const float y = 2/(ex + 1/ex);
	return x.tape->var(y, -y * y * (ex - 1/ex)/2, x.id);
}
inline Var csch(const Var& x)
{
	const float ex = exp(x.val);
	const float y = 2/(ex - 1/ex);
	return x.tape->var(y, -y * y * (ex + 1/ex)/2, x.id);
}
inline Var coth(const Var& x)
{
	const float ex = exp(x.val);
	const float y = (ex + 1/ex)/(ex - 1/ex);
	return x.tape->var(y, -pow(y * 2/(ex + 1/ex), 2), x.id);
}

inline Var sinc(const Var& x)
{
	if (x.val == 0)
		return x.tape->var(1, 0, x.id);
	else
		return x.tape->var(sin(x.val)/x.val, cos(x.val)/x.val - sin(x.val)/(x.val * x.val), x.id);
}

inline Var exp(const Var& x)
{
	return x.tape->var(exp(x.val), exp(x.val), x.id);
}
inline Var log(const Var& x)
{
	return x.tape->var(log(x.val), 1/x.val, x.id);
}
inline Var log(const Var& x, const float a)
{
	return x.tape->var(log10(x.val) / log10(a), 1/(x.val * log(a)), x.id);
}

inline Var sigmoid(const Var& x)
{
	const float y = 1/(1 + 1/exp(x.val));
	return x.tape->var(y, y * (1 - y), x.id);
}

#undef uint
#endif
#endif