:-op(100,xfx,iss).
:-op(90,fx,fibonacci).
:-op(90,xf,factorial).
:-op(90,fx,gcd).
:-op(90,fx,lcm).
:-op(90,fx,collatz).
:-op(90,xf,divisors).
:-op(90,xfx,modulus).
:-op(70,xfx,has).
:-op(70,fx,of).
:-op(50,xfx,and).

%Operators to calculate the fibonacci of a number.
fibonacci of 1 iss 1:-!.

fibonacci of 2 iss 1:-!.

fibonacci of X iss A:-
    X1 is X - 1, X2 is X - 2,
    fibonacci of X1 iss R1,
    fibonacci of X2 iss R2,
    A is R1 + R2.

%Operators to calculate the factorial of a number.
0 factorial iss 1:-!.

X factorial iss A:-
    X1 is X - 1,
    X1 factorial iss R,
    A is R*X.

%Operators to calculate the GCD of two numbers.
gcd of X and Y iss Y:-
    X \= 0, Y \= 0,
    mod(X,Y) =:= 0,!.

gcd of X and Y iss A:-
    X \= 0, Y \= 0,
    M is mod(X,Y),
    gcd of Y and M iss A.

%Operator to calculate the LCM of two numbers.
lcm of X and Y iss Z:-
    X \= 0, Y \= 0,
    gcd of X and Y iss G,
    Z is (X*Y)/G.

%Operators to find the number of divisors a number has.
_ modulus 1 iss 1:-!.

X modulus Y iss A:-
    X > 0, Y > 0,
    mod(X,Y) =:= 0,!,
    Y1 is Y - 1,
    X modulus Y1 iss N,
    A is N + 1.

X modulus Y iss N:-
    X > 0, Y > 0,
    Y1 is Y - 1,
    X modulus Y1 iss N.

1 has 1 divisors:-!.

X has N divisors:-
    X > 0,
    X modulus X iss N.

%Operator write the collatz sequence of a number.
collatz of 1:-
    !,write(1).

collatz of X:-
    X > 0,
    write(X), write(" "),
    mod(X,2) =:= 0,!,
    X1 is X/2,
    collatz of X1.

collatz of X:-
    X > 0,
    X1 is X*3 + 1,
    collatz of X1.
