%List rules using operators.
%By: Abrothguer

:-op(100,xfx,generates).
:-op(100,xfx,iss).

%Find the length of a list.
:-op(90,fx,length).
:-op(30,fx,of).

length of [] iss 0:-!.

length of [_|Y] iss R:-
    length of Y iss R1,
    R is R1 + 1.

%Find the nth element of a list.
:-op(90,fx,the).
:-op(80,xfx,element).

the 1 element of [X|_] iss X:-!.

the X element of [_|Y] iss R:-
    X > 0,
    X1 is X - 1,
    the X1 element of Y iss R.

%Find the biggest element in a list.
:-op(90,fx,maximum).
:-op(80,fx,member).
:-op(80,fx,between).
:-op(20,yfx,and).

maximum between X and Y iss X:-
    X >= Y,!.

maximum between _ and Y iss Y:-!.

maximum member of [X] iss X:-!.

maximum member of [X|Y] iss R:-
    maximum member of Y iss R1,
    maximum between X and R1 iss R.

%Find the smallest element in a list.
:-op(90,fx,minimum).

minimum between X and Y iss X:-
    X =< Y,!.

minimum between _ and Y iss Y:-!.

minimum member of [X] iss X:-!.

minimum member of [X|Y] iss R:-
    minimum member of Y iss R1,
    minimum between X and R1 iss R.

%Find the position of an element in a list.
:-op(70,fx,position_of).

position_of X in [X|_] iss 1:-!.

position_of X in [_|Z] iss N:-
    position_of X in Z iss N1,
    N is N1 + 1.

%Find all positions of an element in a list.
:-op(100,xfx,are).

all position_of _ in [] are []:-!.

all position_of X in [Y|Z] are L:-
    call(position_of X in [Y|Z] iss N),!,
    remove X from [Y|Z] generates W,
    all position_of X in W are L1,
    L = [N|L1].

all position_of _ in [_|_] are []:-!.


%Concatenate two lists.
:-op(90,xfx,concatenated_with).

[] concatenated_with L generates L:-!.

[X|Y] concatenated_with L generates [X|R1]:-
    Y concatenated_with L generates R1.

%Invert a list.
:-op(90,fx,invert).

invert [] generates []:-!.

invert [X|Y] generates R:-
    invert Y generates R1,
    R1 concatenated_with [X] generates R.

%Sort a list.
:-op(90,fx,sort).
:-op(80,fx,insert_sorted).
:-op(50,xfx,in).

insert_sorted X in [] generates [X].

insert_sorted X in [Y|Z] generates [X,Y|Z]:-
    X =< Y,!.

insert_sorted X in [Y|Z] generates [Y|W]:-
    insert_sorted X in Z generates W.

sort [] generates []:-!.

sort [X|Y] generates R:-
    sort Y generates W,!,
    insert_sorted X in W generates R.

%Remove first occurrence of an element in a list.
:-op(90,fx,remove).
:-op(60,xfx,from).

remove X from [X|Y] generates Y:-!.

remove X from [Y|Z] generates [Y|W]:-
    remove X from Z generates W.

%Remove all occurrences of an element in a list.
:-op(80,fx,all).

remove all _ from [] generates []:-!.

remove all X from [X|Y] generates W:-
    !,remove all X from Y generates W.

remove all X from [Y|Z] generates [Y|W]:-
    remove all X from Z generates W.

%Remove all replicate elements in a list.
:-op(70,fx,replicates).
:-op(60,fx,fromm).

remove all replicates fromm [] generates []:-!.

remove all replicates fromm [X|Y] generates [X|L]:-
    remove all X from Y generates W,!,
    remove all replicates fromm W generates L.

%Take elements from a list and put them on another list.
:-op(90,fx,take).
:-op(80,fx,positions).

take positions [] from _ generates []:-!.

take positions [X|Y] from L generates [N|W]:-
    the X element of L iss N,
    take positions Y from L generates W.

%Add an element in the head of a list.
:-op(90,fx,add).
:-op(40,fx,head).

add X in head of [] generates [X]:-!.

add X in head of [Y|Z] generates [X,Y|Z]:-!.

%Add an element in the tail of a list.
:-op(40,fx,tail).

add X in tail of [] generates [X]:-!.

add X in tail of [Y|Z] generates [Y|W]:-!,
    add X in tail of Z generates W.

%Remove first element from a list.
:-op(80,fx,first).

remove first fromm [] generates []:-!.

remove first fromm [_|Y] generates Y:-!.

%Remove last element from a list.
:-op(80,fx,last).

remove last fromm [] generates []:-!.

remove last fromm [_] generates []:-!.

remove last fromm [X|Y] generates [X|W]:-!,
    remove last fromm Y generates W.

%Add an element in the nth position of a list.
:-op(80,xfx,position).
:-op(50,xfx,at).

add X at 1 position of [] generates [X]:-!.

add X at 1 position of [Y|Z] generates [X,Y|Z]:-!.

add X at Y position of [Z|W] generates [Z|L]:-
    Y > 0,
    Y1 is Y - 1,
    add X at Y1 position of W generates L.

%Remove an element in the nth position of a list.
:-op(50,fx,att).

remove att 1 position of [_|Y] generates Y:-!.

remove att X position of [Y|Z] generates [Y|W]:-
    X > 0,
    X1 is X - 1,
    remove att X1 position of Z generates W.

%Replace an element first occurrence in a list.
:-op(90,fx,replace).
:-op(70,xfx,on).
:-op(60,xfx,with).

replace _ with _ on [] generates []:-!.

replace X with Y on [X|W] generates [Y|W]:-!.

replace X with Y on [W|Z] generates [W|L1]:-!,
    replace X with Y on Z generates L1.

%Replace all occurrence of an element in a list.

replace all _ with _ on [] generates []:-!.

replace all X with Y on [X|W] generates [Y|R]:-!,
    replace all X with Y on W generates R.

replace all X with Y on [W|Z] generates [W|L]:-
    replace all X with Y on Z generates L.

%Duplicate all elements in a list.
:-op(90,fx,duplicate).

duplicate all [] generates []:-!.

duplicate all [X|Y] generates [X,X|L]:-!,
    duplicate all Y generates L.

%Duplicate an element in a list.

duplicate _ in [] generates []:-!.

duplicate X in [X|Y] generates [X,X|L]:-!,
    duplicate X in Y generates L.

duplicate X in [Y|Z] generates [Y|L]:-
    duplicate X in Z generates L.

%Union of two lists.
:-op(90,fx,union).

union of [] and [] generates []:-!.

union of [] and X generates X:-!.

union of X and [] generates X:-!.

union of [X|Y] and [W|Z] generates L:-
    [X|Y] concatenated_with [W|Z] generates L1,
    remove all replicates fromm L1 generates L.

%Intersection of two lists.
:-op(90,fx,intersection).

intersection of [] and _ generates []:-!.

intersection of _ and [] generates []:-!.

intersection of [X|Y] and [W|Z] generates L:-
    X belongs to [W|Z],!,
    intersection of Y and [W|Z] generates R,
    L1 = [X|R],
    remove all replicates fromm L1 generates L.

intersection of [_|Y] and [W|Z] generates L:-
    intersection of Y and [W|Z] generates L.

%Replace the nth element for a given number.
:-op(90,fx,place).

place X at 1 on [] generates [X]:-!.

place _ at _ on [] generates []:-!.

place X at Y on [Z|W] generates R:-
    remove att Y position of [Z|W] generates L,
    add X at Y position of L generates R.

%Swap two positions on a list.
:-op(90,fx,swap).

swap positions X and Y on [Z|W] generates R:-
    the X element of [Z|W] iss R1,
    the Y element of [Z|W] iss R2,
    place R1 at Y on [Z|W] generates L,
    place R2 at X on L generates R.

%Permute a list.
:-op(90,fx,permute).
:-op(80,fx,insert).

insert X on [] generates [X]:-!.

insert X on [Y|W] generates [X,Y|W].

insert X on [Y|W] generates [Y|Z]:-
    insert X on W generates Z.

permute [] generates [].

permute [X|Y] generates L:-
    permute Y generates L1,
    insert X on L1 generates L.

%Find if a list is empty.
:-op(100,xf,is_empty).
[] is_empty.

%Find if two lists are disjoint.
:-op(90,xfx,disjoint).

[] disjoint _:-!.

_ disjoint []:-!.

[X|Y] disjoint [W|Z]:-
    intersection of [X|Y] and [W|Z] generates L,
    L = [].

%Find if an element belongs to a list.
:-op(90,xfx,belongs).
:-op(30,fx,to).

X belongs to [X|_]:-!.

X belongs to [_|Z]:-
    X belongs to Z.

%Find if two lists are equal.
:-op(90,xfx,equal).

[] equal to [].

[X|W] equal to [X|Y]:-
    W equal to Y.
