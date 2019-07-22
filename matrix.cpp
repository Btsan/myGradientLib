#include "tape.cpp"
#include <random>

#ifndef uint
#define uint unsigned int

using namespace std;

struct Matrix
{
	vector< vector<Var> > m;

	Matrix(Tape& t, const uint rows, const uint cols, const float x = 0)
	{
		m.resize(rows);

		for (uint i = 0; i < rows; i++)
		{
			m[i].reserve(cols);

			for (uint j = 0; j < cols; j++)
			{
				m[i].push_back(t.var(x));
			}
		}
	}

	uint size()
	{
		return m.size();
	}

	inline const vector<Var>& operator[](const uint i) const
	{
		return m[i];
	}

	inline vector<Var>& operator[](const uint i)
	{
		return m[i];
	} 

	Matrix& operator=(const Matrix& b)
	{
		m.clear();
		m = b.m;
		return *this;
	}

	Matrix& operator+=(const Matrix& b)
	{
		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m[i].size(); j++)
			{
				m[i][j] += b.m[i][j];
			}
		}
		return *this;
	}

	Matrix& operator-=(const Matrix& b)
	{
		for (int i = 0; i < m.size(); i++)
		{
			for (int j = 0; j < m[i].size(); j++)
			{
				m[i][j] -= b.m[i][j];
			}
		}
		return *this;
	}

	Matrix& operator*=(const Matrix& b)
	{
		const uint rows_a = m.size();
		const uint cols_a = m[0].size();
		const uint rows_b = b.m.size();
		const uint cols_b = b.m[0].size();

		vector< vector<Var> > prod;
		prod.resize(rows_a);
		for (uint i = 0; i < rows_a; i++)
		{
			prod[i].reserve(cols_b);
		}

		for (uint i = 0; i < rows_a; i++)
		{
			Var ax = m[i][0];
			for (uint j = 0; j < cols_b; j++)
			{
				prod[i].push_back(ax * b[0][j]);
			}
			for (uint k = 1; k < cols_a; k++)
			{
				ax = m[i][k];
				for (uint j = 0; j < cols_b; j++)
				{
					prod[i][j] += ax * b[k][j];
				}
			}
		}

		m.clear();
		m = prod;
		return *this;
	}

	Matrix& operator+=(const Var& c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] += c;
			}
		}
		return *this;
	} 

	Matrix& operator-=(const Var& c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] -= c;
			}
		}
		return *this;
	}

	Matrix& operator*=(const Var& c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] *= c;
			}
		}
		return *this;
	}

	Matrix& operator/=(const Var& c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] /= c;
			}
		}
		return *this;
	}

	Matrix& operator+=(const float c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] += c;
			}
		}
		return *this;
	} 

	Matrix& operator-=(const float c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] -= c;
			}
		}
		return *this;
	}

	Matrix& operator*=(const float c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] *= c;
			}
		}
		return *this;
	}

	Matrix& operator/=(const float c)
	{
		for (uint i = 0; i < m.size(); i++)
		{
			for (uint j = 0; j < m[i].size(); j++)
			{
				m[i][j] /= c;
			}
		}
		return *this;
	}
};

inline Matrix operator+(Matrix lhs, const Matrix& rhs)
{
	lhs += rhs;
	return lhs;
}
inline Matrix operator-(Matrix lhs, const Matrix& rhs)
{
	lhs -= rhs;
	return lhs;
}
inline Matrix operator*(Matrix lhs, const Matrix& rhs)
{
	lhs *= rhs;
	return lhs;
}

inline Matrix operator+(Matrix lhs, const Var& rhs)
{
	lhs += rhs;
	return lhs;
}
inline Matrix operator-(Matrix lhs, const Var& rhs)
{
	lhs -= rhs;
	return lhs;
}
inline Matrix operator*(Matrix lhs, const Var& rhs)
{
	lhs *= rhs;
	return lhs;
}
inline Matrix operator/(Matrix lhs, const Var& rhs)
{
	lhs /= rhs;
	return lhs;
}

inline Matrix operator+(Matrix lhs, const float rhs)
{
	lhs += rhs;
	return lhs;
}
inline Matrix operator-(Matrix lhs, const float rhs)
{
	lhs -= rhs;
	return lhs;
}
inline Matrix operator*(Matrix lhs, const float rhs)
{
	lhs *= rhs;
	return lhs;
}
inline Matrix operator/(Matrix lhs, const float rhs)
{
	lhs /= rhs;
	return lhs;
}

inline Matrix elementwise_mult(Matrix lhs, const Matrix& rhs)
{
	for (uint i = 0; i < lhs.size(); i++)
	{
		for (uint j = 0; j < lhs[i].size(); j++)
		{
			lhs[i][j] *= rhs[i][j];
		}
	}

	return lhs;
}

Matrix transpose(Matrix mat)
{
	const uint rows = mat.m.size();
	const uint cols = mat.m[0].size();

	vector< vector<Var> > t;
	t.resize(cols);

	for (uint i = 0; i < cols; i++)
	{
		t[i].reserve(rows);

		for (uint j = 0; j < rows; j++)
		{
			t[i].push_back(mat.m[j][i]);
		}
	}

	mat.m = t;
	return mat;
}

Matrix random_matrix(Tape& t, const uint rows, const uint cols, const float mean=0, const float stdev=1) {
	Matrix m(t, rows, cols);
	mt19937 gen;
	normal_distribution<float> distrib(mean, stdev);

	for (uint i = 0; i < rows; i++) {
		for (uint j = 0; j < cols; j++) {
			m[i][j].val = distrib(gen);
		}
	}

	return m;
}

#undef uint
#endif