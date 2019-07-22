# myGradientLib
simple C++ auto-differentiation library being implemented for exercise

### Automatic Differentiation

Every computer program uses primitive operations (e.g. add, subtract, multiply, divide) and functions (e.g. log, sin, cos) that have simple derivatives. Knowing their derivatives, the chain rule can be used to compute the gradient of any function composed of these primitives.

---

[*tape.h*](https://github.com/Btsan/myGradientLib/blob/master/tape.h) defines the following classes:

- __Var__:

   a class that represents a floating point value. It contains a reference to its containing dependency graph. Additionally, its operators (+, -, *, /, ^) have been overloaded to update a dependency graph with a new node.
   
- __Node__: 

   this object stores the resulting partial derivatives of a primitive operation/function on Var objects and references to those Var objects.
   
- __Tape__:

   A dependency graph of Node objects. This gets traversed during gradient calculation, called from a Var object.
   
- __Grad__:

   Container that stores a calculated gradient. It has a function for returning the derivative w.r.t. a Var object.
   
### [test.cpp](https://github.com/Btsan/myGradientLib/blob/master/test.cpp) output:
###### Note that floating point error is noticeable in particularly long/complex functions
```
./test
a = 2
b = 3
c = (ab + a + sin(b)a)/b
c += log(a)

calculating gradient of c:
dc/da = 1.88037 	correct answer: 1.88037...
dc/db = -0.913577 	correct answer: -0.9135...

e = c - a
f = c + ab

calculating gradient of e:
de/da = 0.880373 	correct answer: 0.88037...
de/db = -0.913577 	correct answer: -0.9135...

calculating gradient of f:
df/da = 4.88037 	correct answer: 4.88037...
df/db = 1.08642 	correct answer: 1.086...

g = sin(a) + cos(a) + tan(a) + sec(a) + csc(a) + cot(a) + sinh(a) + cosh(a) + tanh(a) + sech(a) + csch(a) + coth(a)

calculating gradient of g:
dg/da = 16.0349 	correct answer: 15.8348...
dg/db = 0 	correct answer: 0

h = (e^log10(b))^2 + a

calculating gradient of h:
dh/da = 1 	correct answer: 1
dh/db = 0.751823 	correct answer: 0.7518...

i = sinc(a) + sigmoid(b)

calculating gradient of i:
di/da = -0.435398 	correct answer: -0.43539...
di/db = -0.0451767 	correct answer: -0.04517...
a = 0
b = 1
m = asin(b) + acos(a) + atan(a)

calculating gradient of m:
dm/da = 0 	correct answer: 0
dm/db = inf 	correct answer: 1/0
```

### Usage

```c
#include "tape.cpp"
```
compile with C++11+

```make
g++ example.cpp -std=c++11 -o example
```

### Example

[example.cpp](https://github.com/Btsan/myGradientLib/blob/master/example.cpp) demonstrates using this library to train a multilayer perceptron neural network to predict random noise.

```make
make example
g++ example.cpp tape.cpp -O2 -std=c++11 -o example
./example
iteration 0/100 	mean_squared_loss = 0.387794
iteration 1/100 	mean_squared_loss = 0.37101
iteration 2/100 	mean_squared_loss = 0.354636
iteration 3/100 	mean_squared_loss = 0.339012
iteration 4/100 	mean_squared_loss = 0.324428
iteration 5/100 	mean_squared_loss = 0.311094
iteration 6/100 	mean_squared_loss = 0.299131
iteration 7/100 	mean_squared_loss = 0.288576
iteration 8/100 	mean_squared_loss = 0.27939
iteration 9/100 	mean_squared_loss = 0.271484
iteration 10/100 	mean_squared_loss = 0.264738
iteration 11/100 	mean_squared_loss = 0.259018
iteration 12/100 	mean_squared_loss = 0.254188
iteration 13/100 	mean_squared_loss = 0.250121
iteration 14/100 	mean_squared_loss = 0.2467
iteration 15/100 	mean_squared_loss = 0.243823
iteration 16/100 	mean_squared_loss = 0.241402
iteration 17/100 	mean_squared_loss = 0.239362
iteration 18/100 	mean_squared_loss = 0.237641
iteration 19/100 	mean_squared_loss = 0.236185
iteration 20/100 	mean_squared_loss = 0.234951
iteration 21/100 	mean_squared_loss = 0.233902
iteration 22/100 	mean_squared_loss = 0.233008
iteration 23/100 	mean_squared_loss = 0.232244
iteration 24/100 	mean_squared_loss = 0.23159
iteration 25/100 	mean_squared_loss = 0.231028
iteration 26/100 	mean_squared_loss = 0.230544
iteration 27/100 	mean_squared_loss = 0.230126
iteration 28/100 	mean_squared_loss = 0.229764
...
iteration 99/100 	mean_squared_loss = 0.226924
seed was -1925795689
rm example
```

---

I referenced these webpages on auto-differentiation:
- <https://stats.stackexchange.com/questions/224140/step-by-step-example-of-reverse-mode-automatic-differentiation>

   A concise example of how reverse-accumulation of derivatives can compute gradients.
- <https://rufflewind.com/2016-12-30/reverse-mode-automatic-differentiation>

   More technical example of implementing auto-differentiation in the Python and Rust languages.
