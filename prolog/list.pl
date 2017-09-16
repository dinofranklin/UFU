%Lists rules

%Rule to concatenate lists.
conc([],L,L).

conc([X|Y],L,[X|R1]):-
    conc(Y,L,R1).

%Rule to invert a list.
invert([],[]).

invert([X|Y],R):-
    invert(Y,R1),
    conc(R1,[X],R).

%Rules to sort a list.
insort(X,[],[X]):- !.

insort(X,[Y|Z],A):-
    X =< Y,!,
    A = [X,Y|Z].
insort(X,[Y|Z],[Y|L1]):-
    X > Y,!,
    insort(X,Z,L1).

sortlist([],[]):-!.

sortlist([X|Y],R):-
    sortlist(Y,L1),
    insort(X,L1,R).

%Rules to find the number of elements/length of list.
len([],Ac,Ac).

len([_|Y],Ac,R):-
    Ac1 is Ac + 1,
    len(Y,Ac1,R).

listlen([],0):-!.

listlen([X|Y],R):-
    Ac = 0,
    len([X|Y],Ac,R).

%Rule to find the nth element of a list.
nth([X|_],1,X):-!.

nth([_|Y],N,R):-
    N > 0,
    N1 is N - 1,%Lists rules

%Rule to concatenate lists.
conc([],L,L).

conc([X|Y],L,[X|R1]):-
    conc(Y,L,R1).

%Rule to invert a list.
invert([],[]).

invert([X|Y],R):-
    invert(Y,R1),
    conc(R1,[X],R).

%Rules to sort a list.
insort(X,[],[X]):- !.

insort(X,[Y|Z],A):-
    X =< Y,!,
    A = [X,Y|Z].
insort(X,[Y|Z],[Y|L1]):-
    X > Y,!,
    insort(X,Z,L1).

sortlist([],[]):-!.

sortlist([X|Y],R):-
    sortlist(Y,L1),
    insort(X,L1,R).

%Rules to find the number of elements/length of list.
len([],Ac,Ac).

len([_|Y],Ac,R):-
    Ac1 is Ac + 1,
    len(Y,Ac1,R).

listlen([],0):-!.

listlen([X|Y],R):-
    Ac = 0,
    len([X|Y],Ac,R).

%Rule to find the nth element of a list.
nth([X|_],1,X):-!.

nth([_|Y],N,R):-
    N > 0,
    N1 is N - 1,
    nth(Y,N1,R).

%Rule to remove the first occurrence of an element in a list.
remove(_,[],[]):-!.

remove(X,[X|Y],Y):-!.

remove(X,[Y|Z],L):-
    remove(X,Z,L1),
    L = [Y|L1].

%Rule to remove all ocurrences of an element in a list.
removeall(_,[],[]):-!.

removeall(X,[X|Y],L):-
    !,removeall(X,Y,L1),
    L = L1.

removeall(X,[Y|Z],L):-
    removeall(X,Z,L1),
    L = [Y|L1].

%Rule to remove all replicate elements in a list.
removerep([],[]):-!.

removerep([X|Y],L):-
    removeall(X,Y,L1),
    removerep(L1,L2),
    L = [X|L2].

%Rules to find the biggest element in a list.

listmax([X],X):-!.

listmax([X|Y],A):-
    listmax(Y,A),
    A >= X,!.

listmax([X|_],X).

%Rules to find the smaller element in a list.

listmin([X],X):-!.

listmin([X|Y],A):-
    listmin(Y,A),
    A =< X,!.

listmin([X|_],X).

%Rule to take elements from a list and put them in another list.
takepos([],_,[]):-!.

takepos([X|Y],L,R):-
    nth(L,X,R1),
    takepos(Y,L,R2),
    R = [R1|R2].

%Rule to add an element to the head of a list.
addhead(X,[],[X]):-!.

addhead(X,[Y|Z],[X,Y|Z]).

%Rule to add an element to the tail of a list.
addtail(X,[],[X]):-!.

addtail(X,[Y|Z],[Y|L1]):-
    addtail(X,Z,L1).

%Rule to remove the first element of a list.
removefirst([],[]).

removefirst([_|Y],Y).

%Rule to remove the last element of a list.
removelast([],[]):-!.

removelast([_],[]):-!.

removelast([X|Y],L):-
    removelast(Y,L1),
    L = [X|L1].

%Rule to add an element in the nth position of a list.
addpos(X,1,[Y|Z],[X,Y|Z]):- !.

addpos(X,P,[Y|Z],[Y|L1]):-
    P1 is P-1,
    addpos(X,P1,Z,L1).

add_at(X,N,[Y|Z],L):-
    listlen([Y|Z],Len),
    N =< Len,
    N > 0,
    addpos(X,N,[Y|Z],L).

%Rule to remove an element in the nth position of a list.
removepos(N,N,[_|Y],Y):-!.

removepos(N,P,[X|Y],L):-
    P1 is P + 1,
    removepos(N,P1,Y,L1),
    L = [X|L1].

remove_at(N,[X|Y],L):-
    listlen([X|Y],Len),
    N =< Len,
    N > 0,
    removepos(N,1,[X|Y],L).

%Rule to find if a certain element X belongs to a list.
belongs(X,[X|_]):-!.

belongs(X,[_|Z]):-
    belongs(X,Z).

%Rule to find the position of an element in a list.
findpos(X,[X|_],Ac,Ac):-!.

findpos(X,[_|Z],Ac,P):-
    Ac1 is Ac + 1,
    findpos(X,Z,Ac1,P).

find(X,[X|_],1):-!.

find(X,[_|Z],P):-
    findpos(X,Z,2,P).

%Rule to find all position of an element in a list.
discoverpos(_,[],_,[]):-!.

discoverpos(X,[X|Y],P,L):-
   !, P1 is P + 1,
   discoverpos(X,Y,P1,L1),
   L = [P|L1].

discoverpos(X,[_|Z],P,L):-
    P1 is P + 1,
    discoverpos(X,Z,P1,L).

discover(_,[],[]):-!.

discover(X,[Y|Z],L):-
    discoverpos(X,[Y|Z],1,L).

%Rule to replace the first occurrence of an element in a list.
replace(X,Y,[X|Z],[Y|Z]):-!.

replace(X,Y,[Z|W],[Z|L1]):-
    replace(X,Y,W,L1).

%Rule to replace all occurrences of an element in a list.
replaceall(_,_,[],[]):-!.

replaceall(X,Y,[X|Z],[Y|L1]):-
    !, replaceall(X,Y,Z,L1).

replaceall(X,Y,[Z|W],[Z|L1]):-
    replaceall(X,Y,W,L1).

%Rule to find out if two lists are the same.
equalist([],[]):-!.

equalist([X|Y],[X|Z]):-
    equalist(Y,Z).

%Rule to duplicate all elements of a list.
duplicateall([],[]):-!.

duplicateall([X|Y],L):-
    duplicate(Y,L1),
    L = [X,X|L1].

%Rule to duplicate an element of a list.
duplicate(_,[],[]):-!.

duplicate(X,[X|Y],[X,X|L1]):-
    !, duplicate(X,Y,L1).

duplicate(X,[Y|Z],[Y|L1]):-
    duplicate(X,Z,L1).

%Rule to find the union of two lists.
union([],L,L):-!.

union([],[],[]):-!.

union(L,[],L):-!.

union([X|Y],[Z|W],L):-
    conc([X|Y],[Z|W],L1),
    removerep(L1,L).

%Rules to find the intersection of two lists.
interlist([],[_|_],Ac,Ac):-!.

interlist([X|Y],[Z|W],Ac,L):-
    belongs(X,[Z|W]),!,
    conc(Ac,[X],Ac1),
    interlist(Y,[Z|W],Ac1,L).

interlist([_|Y],[Z|W],Ac,L):-
    interlist(Y,[Z|W],Ac,L).

intersec([],_,[]):-!.

intersec(_,[],[]):-!.

intersec([X|Y],[Z|W],L):-
    removerep([X|Y],L1),
    interlist(L1,[Z|W],[],L).

%Rule to find if two lists are disjoint.
disjoint([],_):-!.

disjoint(_,[]):-!.

disjoint([X|Y],[Z|W]):-
    intersec([X|Y],[Z|W],L),
    L = [].

%Rule to find if a list is empty.
empty([]).

%Rule to swap the nth element in a list.
swapnth(X,1,[_|Z],[X|Z]):-!.

swapnth(X,N,[Y|Z],[Y|L1]):-
    N1 is N - 1,
    swapnth(X,N1,Z,L1).

%Rule to swap two element in a list.
swap(P1,P2,[X|Y],L1):-
    nth([X|Y],P1,E1),
    nth([X|Y],P2,E2),
    swapnth(E1,P2,[X|Y],L),
    swapnth(E2,P1,L,L1).

%Rules to permute a list.
insert(X,[],[X]):-!.

insert(X,[Y|Z],L):-
    L = [X,Y|Z].

insert(X,[Y|Z],L):-
    insert(X,Z,L1),
    L = [Y|L1].

permute([],[]).

permute([X|Y],L):-
    permute(Y,L1),
    insert(X,L1,L).

%Rules to find the sum of all elements in a list.
sum([],0):-!.

sum([X],X):-!.

sum([X|Y],Z):-
    sum(Y,R),
    Z is X + R.

%Rules to find the average of all elements in a list.
average([],0):-!.

average([X],X):-!.

average([X|Y],Z):-
    sum([X|Y],S),
    listlen([X|Y],L),
    Z is S/L.
    
%Rules to find the median of a list.
median([X],X):-!.

median([X|Y],N):-
    listlen([X|Y],L),
    mod(L,2) =:= 0,!,
    L1 is L/2, L2 is L/2 + 1,
    nth([X|Y],L1,N1),
    nth([X|Y],L2,N2),
    N is (N1+N2)/2.

median([X|Y],N):-
    listlen([X|Y],L),
    L1 is L//2 + 1,
    nth([X|Y],L1,N).

%Rules to count the number of occurrences of an element in a list.
count(_,[],0):-!.

count(X,[X|Z],N):-
    !,count(X,Z,N1),
    N is N1 + 1.

count(X,[_|Z],N):-
    count(X,Z,N).

%Rules to find the mode of a list.

mode([X],X):-!.

mode([X|Y],R):-
    mode(Y,R),
    count(X,[X|Y],A1),
    count(R,[X|Y],A2),
    A2 >= A1,!.

mode([X|_],X).

    nth(Y,N1,R).

%Rule to remove the first occurrence of an element in a list.
remove(_,[],[]):-!.

remove(X,[X|Y],Y):-!.

remove(X,[Y|Z],L):-
    remove(X,Z,L1),
    L = [Y|L1].

%Rule to remove all ocurrences of an element in a list.
removeall(_,[],[]):-!.

removeall(X,[X|Y],L):-
    !,removeall(X,Y,L1),
    L = L1.

removeall(X,[Y|Z],L):-
    removeall(X,Z,L1),
    L = [Y|L1].

%Rule to remove all replicate elements in a list.
removerep([],[]):-!.

removerep([X|Y],L):-
    removeall(X,Y,L1),
    removerep(L1,L2),
    L = [X|L2].

%Rules to find the biggest element in a list.

listmax([X],X):-!.

listmax([X|Y],A):-
    listmax(Y,A),
    A >= X,!.

listmax([X|_],X).

%Rules to find the smaller element in a list.

listmin([X],X):-!.

listmin([X|Y],A):-
    listmin(Y,A),
    A =< X,!.

listmin([X|_],X).

%Rule to remove the first element of a list.
removefirst([],[]).

removefirst([_|Y],Y).

%Rule to remove the last element of a list.
removelast([],[]):-!.

removelast([_],[]):-!.

removelast([X|Y],L):-
    removelast(Y,L1),
    L = [X|L1].

%Rule to remove an element in the nth position of a list.
removepos(N,N,[_|Y],Y):-!.

removepos(N,P,[X|Y],L):-
    P1 is P + 1,
    removepos(N,P1,Y,L1),
    L = [X|L1].

remove_at(N,[X|Y],L):-
    listlen([X|Y],Len),
    N =< Len,
    N > 0,
    removepos(N,1,[X|Y],L).

%Rule to find if a certain element X belongs to a list.
belongs(X,[X|_]):-!.

belongs(X,[_|Z]):-
    belongs(X,Z).

%Rule to find the position of an element in a list.
findpos(X,[X|_],Ac,Ac):-!.

findpos(X,[_|Z],Ac,P):-
    Ac1 is Ac + 1,
    findpos(X,Z,Ac1,P).

find(X,[X|_],1):-!.

find(X,[_|Z],P):-
    findpos(X,Z,2,P).

%Rule to find all position of an element in a list.
discoverpos(_,[],_,[]):-!.

discoverpos(X,[X|Y],P,L):-
   !, P1 is P + 1,
   discoverpos(X,Y,P1,L1),
   L = [P|L1].

discoverpos(X,[_|Z],P,L):-
    P1 is P + 1,
    discoverpos(X,Z,P1,L).

discover(_,[],[]):-!.

discover(X,[Y|Z],L):-
    discoverpos(X,[Y|Z],1,L).

%Rule to replace the first occurrence of an element in a list.
replace(X,Y,[X|Z],[Y|Z]):-!.

replace(X,Y,[Z|W],[Z|L1]):-
    replace(X,Y,W,L1).

%Rule to replace all occurrences of an element in a list.
replaceall(_,_,[],[]):-!.

replaceall(X,Y,[X|Z],[Y|L1]):-
    !, replaceall(X,Y,Z,L1).

replaceall(X,Y,[Z|W],[Z|L1]):-
    replaceall(X,Y,W,L1).

%Rule to find out if two lists are the same.
equalist([],[]):-!.

equalist([X|Y],[X|Z]):-
    equalist(Y,Z).

%Rule to duplicate all elements of a list.
duplicateall([],[]):-!.

duplicateall([X|Y],L):-
    duplicate(Y,L1),
    L = [X,X|L1].

%Rule to duplicate an element of a list.
duplicate(_,[],[]):-!.

duplicate(X,[X|Y],[X,X|L1]):-
    !, duplicate(X,Y,L1).

duplicate(X,[Y|Z],[Y|L1]):-
    duplicate(X,Z,L1).

%Rule to find the union of two lists.
union([],L,L):-!.

union([],[],[]):-!.

union(L,[],L):-!.

union([X|Y],[Z|W],L):-
    conc([X|Y],[Z|W],L1),
    removerep(L1,L).

%Rules to find the intersection of two lists.
interlist([],[_|_],Ac,Ac):-!.

interlist([X|Y],[Z|W],Ac,L):-
    belongs(X,[Z|W]),!,
    conc(Ac,[X],Ac1),
    interlist(Y,[Z|W],Ac1,L).

interlist([_|Y],[Z|W],Ac,L):-
    interlist(Y,[Z|W],Ac,L).

intersec([],_,[]):-!.

intersec(_,[],[]):-!.

intersec([X|Y],[Z|W],L):-
    removerep([X|Y],L1),
    interlist(L1,[Z|W],[],L).

%Rule to find if two lists are disjoint.
disjoint([],_):-!.

disjoint(_,[]):-!.

disjoint([X|Y],[Z|W]):-
    intersec([X|Y],[Z|W],L),
    L = [].

%Rule to find if a list is empty.
empty([]).

%Rule to swap the nth element in a list.
swapnth(X,1,[_|Z],[X|Z]):-!.

swapnth(X,N,[Y|Z],[Y|L1]):-
    N1 is N - 1,
    swapnth(X,N1,Z,L1).

%Rule to swap two element in a list.
swap(P1,P2,[X|Y],L1):-
    nth([X|Y],P1,E1),
    nth([X|Y],P2,E2),
    swapnth(E1,P2,[X|Y],L),
    swapnth(E2,P1,L,L1).

%Rules to permute a list.
insert(X,[],[X]):-!.

insert(X,[Y|Z],L):-
    L = [X,Y|Z].

insert(X,[Y|Z],L):-
    insert(X,Z,L1),
    L = [Y|L1].

permute([],[]).

permute([X|Y],L):-
    permute(Y,L1),
    insert(X,L1,L).

%Rules to find the sum of all elements in a list.
sum([],0):-!.

sum([X],X):-!.

sum([X|Y],Z):-
    sum(Y,R),
    Z is X + R.

%Rules to find the average of all elements in a list.
average([],0):-!.

average([X],X):-!.

average([X|Y],Z):-
    sum([X|Y],S),
    listlen([X|Y],L),
    Z is S/L.
    
%Rules to find the median of a list.
median([X],X):-!.

median([X|Y],N):-
    listlen([X|Y],L),
    mod(L,2) =:= 0,!,
    L1 is L/2, L2 is L/2 + 1,
    nth([X|Y],L1,N1),
    nth([X|Y],L2,N2),
    N is (N1+N2)/2.

median([X|Y],N):-
    listlen([X|Y],L),
    L1 is L//2 + 1,
    nth([X|Y],L1,N).

%Rules to count the number of occurrences of an element in a list.
count(_,[],0):-!.

count(X,[X|Z],N):-
    !,count(X,Z,N1),
    N is N1 + 1.

count(X,[_|Z],N):-
    count(X,Z,N).

%Rules to find the mode of a list.

mode([X],X):-!.

mode([X|Y],R):-
    mode(Y,R),
    count(X,[X|Y],A1),
    count(R,[X|Y],A2),
    A2 >= A1,!.

mode([X|_],X).

%Rules to compress a list.

compress_aux([],_,Ac,Ac).

compress_aux([X|Y],Prev,Ac,R):-
    X \= Prev,!,
    conc(Ac,[X],L),
    compress_aux(Y,X,L,R).

compress_aux([X|Y],_,Ac,R):-
    compress_aux(Y,X,Ac,R).

compress([],[]).

compress([X|Y],[X|L]):-
   compress_aux(Y,X,[],L).

%Rules to multiply the elements of two lists of same length.

mult([],[],[]).

mult([X|Y],[W|Z],[G|L1]):-
    G is X*W,
    mult(Y,Z,L1).
    
%Rule to verify if a list is a palindrome.

palindrome([]).

palindrome([X|Y]):-
    invert([X|Y],L),
    equalist([X|Y],L).

%Rule to calculate the weighted average of a list.

weighted_average([],[],0).

weighted_average([X|Y],[Z|W],R):-
    mult([X|Y],[Z|W],M),
    sum(M,Top),
    sum([X|Y],Bottom),
    R is Top/Bottom.

% Rules to separate a list in two lists, one of odds and one of even numbers.

separate_even_odd([],E,O,E,O).

separate_even_odd([X|Y],E,O,Ef,Of):-
    M is mod(X,2),
    M =:= 0,!,
    conc(E,[X],E2),
    separate_even_odd(Y,E2,O,Ef,Of).

separate_even_odd([X|Y],E,O,Ef,Of):-
    conc(O,[X],O2),
    separate_even_odd(Y,E,O2,Ef,Of).

even_odd([],[],[]).

even_odd([X|Y],E,O):-
    separate_even_odd([X|Y],[],[],E,O).
