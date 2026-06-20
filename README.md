# Symbolic
## A C++ Computer Algebra System

__Symbolic__ is a C++ library for symbolic mathematics.

Numerical expressions are implemented as ASTs (Abstract Syntax Trees), whose nodes are operations (+-*/^, exp...), values (1.2345) and symbols (x,y,...). Expressions can be evaluated on a given (x = ..., y = ..., ...).

The project is under active development and still missing unit tests - results could be wrong.

### Features
- `Expression` objects encapsulate the AST (symbolic representation) and a `NodeStorage` object, which manages the storage and ownership of the `Node`s of the tree. Non-owning raw pointers `Node*` are used internally for traversal.
- Supported operations: Arithmetics (addition, subtraction through negation, multiplication, division, power) and special functions (`exp`, `sin`, `cos`, `tan`).
- Numerical evaluation of the symbolic expression on a given `SymbolContext {x = ..., y = ..., etc.}`
- New operators and functions can be easily implemented by subclassing abstract `Node, UnaryNode, BinaryNode, NaryNode` objects.

#### To be implemented
- __Important!__ Unit tests 
- Rational arithmetics for exact symbolic computations (and switch to double for performance)
- Algebraic simplification and canonical forms
- Symbolic substitution (`x + y` , ` <- y = 3/x`)
- Analytic differentiation
- String parser (`x^2 + 2*x - y + 3/2`)
- REPL

#### Possible ideas going forward
- Numerical algorithms for integration (Trapezoids, Monte Carlo...) and Root Finding

### Example

```
Expression expr;
auto x = expr.makeSymbol("x");
auto y = expr.makeSymbol("y");

auto sum = expr.makeNode<Sum>({expr.makeNode<Sin>(x), 
                               expr.makeNode<Power>(y, expr.makeNode<Value>(2.0))});
expr.root = sum;

SymbolContext ctx = {{"x", 1.57}, {"y", 3.0}};
std::cout << expr << std::endl;
std::cout << expr.evaluate(ctx) << std::endl; // sin(x) + y^2
```

### Build

```
mkdir build
cd build
cmake ..
make
./Symbolic  // for now it's just a test Main
```