%Using prolog operators to make logic operators.

%Operator not("!").
:-op(20,fy,!).
%Operator if then("=>").
:-op(100,xfy,=>).
%Operator if and only if("<=>").
:-op(100,xfy,<=>).
%Operator and("&").
:-op(40,xfy,&).
%Operator or("#").
:-op(40,xfy,#).
%Operator xor("$").
:-op(40,xfy,$).

%Operator not definition:
!X:-not(call(X)).

%Operator if then definition:
X=>_:-not(call(X)),!.
X=>Y:-call(X),call(Y).

%Operator if and only if definition:
X<=>Y:-call(X) = call(Y).

%Operator and definition:
X&Y:-call(X),call(Y).

%Operator or definition:
X#_:-call(X),!.
_#Y:-call(Y).

%Operator xor definition:
X$Y:-call(X),not(call(Y)),!.
X$Y:-call(Y),not(call(X)).

