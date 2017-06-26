%Simple rules using Prolog.

%Rule to calculate Fibonacci.
fib(1,1):-!.

fib(2,1):-!.

fib(X,N):-
    X1 is X - 1,
    X2 is X - 2,
    fib(X1,N1),
    fib(X2,N2),
    N is N1 + N2.

%Rule to calculate factorial using simple recursion.
fat(0,1):-!.

fat(X,N):-
    X1 is X - 1,
    fat(X1,N1),
    N is X*N1.

%Rule to calculate factorial using tail recursion.
fatl(0,Ac,Ac):-!.

fatl(X,Ac,R):-
    X1 is X - 1,
    Ac1 is Ac * X,
    fatl(X1,Ac1,R).

%Rules to find the number of dividers using simple recursion.
divide(X,Y,B):-
    B1 is mod(X,Y),
    B1 =:= 0,!,
    B = 1.

divide(_,_,B):-
    B = 0.

ndiv(X,X,1):-!.

ndiv(X,C,R):-
    C =< X,
    C > 0,
    divide(X,C,R1),
    C1 is C + 1,
    ndiv(X,C1,R2),
    R is R1 + R2.

%Rules to find the number of dividers using tail recursion.
ntdiv(X,X,Ac,T):-
    !, T is Ac + 1.

ntdiv(X,C,Ac,R):-
    C > 0,
    divide(X,C,R1),
    Ac1 is Ac + R1,
    C1 is C + 1,
    ntdiv(X,C1,Ac1,R).

%Rules to find the Greatest Commom Divisor between two numbers.
gcd(X,Y,Y):-
    X \= 0, Y \= 0,
    N is mod(X,Y),
    N =:= 0,!.

gcd(X,Y,Z):-
    X \= 0, Y \= 0,
    N is mod(X,Y),
    gcd(Y,N,Z).

%Rule to find the Least Commom Multiplier between two numbers.
lcm(X,Y,N):-
    X \= 0, Y \= 0,
    gcd(X,Y,R),
    N is (X*Y)/R.

%Rules to print the collatz sequence of a number.
collatz(1):-
    !,write(1).

collatz(X):-
    write(X),write(" "),
    N is mod(X,2),
    N =:= 0,!,
    X1 is X/2,
    collatz(X1).

collatz(X):-
    X1 is X*3 + 1,
    collatz(X1).
