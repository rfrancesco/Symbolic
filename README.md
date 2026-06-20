# Symbolic
## A C++ Computer Algebra System

This is my attempt to create a CAS in C++. 

```
mkdir build
cd build
cmake ..
make
./Symbolic  // for now it's just a test Main
```

Numerical expressions are implemented as an AST (Abstract Syntax Tree), whose nodes are operations (+-*/^), values (1.2345) and symbols (x,y,...). Expressions can be manipulated algebraically or evaluated on a given (x = ..., y = ..., ...). Not all of this things are implemented yet.

This is a fun educational pet project and not a serious attempt for a professional CAS. Do not use this for ANY serious purpose, since the correctness of the results is not guaranteed.

The scope is restricted, on purpose, to

#### Implemented
- Arithmetical operations (+-*/^) 
- Special functions: exp(x)
- Variable symbols (x, y, z...)
- Representation and evaluation of an expression

#### To be implemented
- Switch from doubles (numerical nightmare) to rational fractions 
- Simplifier (Group constants, remove trivial sums, trivial products, etc.)
- Parsing from string to expression and REPL
- Analytical differentiation
- Substitution

#### Possible ideas going forward
- Numerical integration
- Root finding
- Compilation into Bytecode for performance! (It seems already fast enough, it would be just for fun)

#### Outside of scope - will not be implemented
- Analytical integration (it's an art, after all)
- Trigonometry (mostly because simplifying expressions becomes a mess)

