#include "tape.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	Tape t;

	random_device rd;
	mt19937 gen(rd());

	int N = 100;
	int dim = 2;

	float data[N][dim];
	float target[N];

	for (int i = 0; i < N; i++)
	{
		int sign = 0;
		for (int j = 0; j < dim; j++)
		{
			data[i][j] = gen() / (float)gen.max() - 0.5f;
			if (data[i][j] > 0)
			{
				sign++;
			}
		}
		target[i] = sign < dim;
	}

	float weights1[2][3], weights2[3];

	normal_distribution<float> distrib(0., 0.5f);

	for (int i = 0; i < 3; i++)
	{
		weights2[i] = distrib(gen);
		for (int j = 0; j < 2; j++)
		{
			weights1[j][i] = distrib(gen);
		}
	}

	int iterations = 100;
	float learn_rate = 0.01;

	for (int it = 0; it < iterations; it++)
	{
		Grad error;
		float squared_loss = 0;
		for (int sample = 0; sample < N; sample++)
		{
			vector< vector<Var> > w1;
			vector<Var> w2;

			w1.resize(2);
			for (int i = 0; i < 3; i++)
			{
				w2.push_back(t.var(weights2[i]));
				for (int j = 0; j < 2; j++)
				{
					w1[j].push_back(t.var(weights1[j][i]));
				}
			}

			vector<Var> hidden;
			for (int i = 0; i < 3; i++)
			{
				hidden.push_back(sigmoid(w1[0][i] * data[sample][0] + w1[1][i] * data[sample][1]));
			}
			Var output = sigmoid(hidden[0] * w2[0] + hidden[1] * w2[1] + hidden[2] * w2[2]);
			Var loss = (output - target[sample])^2;
			squared_loss += loss.val;

			loss.grad(error);

			for (int i = 0; i < 3; i++)
			{
				weights2[i] -= error.wrt(w2[i]) * learn_rate; 
				for (int j = 0; j < 2; j++)
				{
					weights1[j][i] -= error.wrt(w1[j][i]) * learn_rate;
				}
			}

			t.repeat();
		}

		cout << "iteration " << it << "/100 \tmean_squared_loss = " << squared_loss/100 << '\n';
		learn_rate *= 0.99;
	}

	return 0;
}