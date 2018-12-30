#include "tape.h" // Tape, Var, Grad

#include <iostream>
#include <random> // random_device, mt19937, normal_distribution
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	// Tape saves partial derivatives from operations on Var objects
	Tape t;

	// seed pseudo-rng
	int seed = 2036384550;
	mt19937 gen(seed);

	int N = 100;
	int dim = 2;

	// XOR dataset of N samples and 2 dimensions per sample
	float data[N][dim];
	float target[N];

	for (int i = 0; i < N; i++)
	{
		int sign = 0;
		for (int j = 0; j < dim; j++)
		{
			// randomly generate data
			data[i][j] = gen() / (float)gen.max() - 0.5f;
			if (data[i][j] > 0)
			{
				sign++;
			}
		}
		// label data with XOR
		target[i] = sign < dim;
	}

	// weights for a neural network of 2 inputs, 3 hidden units, and 1 output
	float weights1[2][3], weights2[3];

	// pseudo-rng with 0 mean and 0.5 std-deviation
	normal_distribution<float> distrib(0., 0.5f);

	// initialize weights with normal distribution
	for (int i = 0; i < 3; i++)
	{
		weights2[i] = distrib(gen);
		for (int j = 0; j < 2; j++)
		{
			weights1[j][i] = distrib(gen);
		}
	}

	// number of iterations over dataset
	int iterations = 100;

	// initial learning rate
	float learn_rate = 0.01;

	for (int it = 0; it < iterations; it++)
	{
		// Grad object that will store the loss gradient
		Grad error;
		float squared_loss = 0;

		// stochastic gradient descent loop over dataset
		for (int sample = 0; sample < N; sample++)
		{
			// arrays of Var objects
			vector< vector<Var> > w1;
			vector<Var> w2;
			w1.resize(2);

			// wrap the weights in Var objects, so the Tape can calculate derivatives
			for (int i = 0; i < 3; i++)
			{
				w2.push_back(t.var(weights2[i]));
				for (int j = 0; j < 2; j++)
				{
					w1[j].push_back(t.var(weights1[j][i]));
				}
			}

			// hidden layer of 3 sigmoid units
			vector<Var> hidden;

			// compute the dot product of the 1x2 input and the 2x3 weights (w1)
			for (int i = 0; i < 3; i++)
			{
				hidden.push_back(sigmoid(w1[0][i] * data[sample][0] + w1[1][i] * data[sample][1]));
			}

			// output sigmoid unit = dot product between the 1x3 hidden layer and the 3x1 weights (w2)
			Var output = sigmoid(hidden[0] * w2[0] + hidden[1] * w2[1] + hidden[2] * w2[2]);

			// squared loss
			Var loss = (output - target[sample])^2;
			squared_loss += loss.val;

			// save the loss gradient
			loss.grad(error);

			// update weights
			for (int i = 0; i < 3; i++)
			{
				weights2[i] -= error.wrt(w2[i]) * learn_rate; 
				for (int j = 0; j < 2; j++)
				{
					weights1[j][i] -= error.wrt(w1[j][i]) * learn_rate;
				}
			}

			// set Tape object on repeat, discards previous gradients to avoid allocating extra memory
			t.repeat();
		}

		cout << "iteration " << it << "/100 \tmean_squared_loss = " << squared_loss/100 << '\n';

		// decay learning rate
		learn_rate *= 0.99;
	}

	cout << "seed was " << seed << endl;
	return 0;
}