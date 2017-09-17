%Usando operadores prolog.
%By: Abrothguer

:-op(100,xfx,eh).
:-op(90,fx,um).
:-op(90,fx,uma).

gimli eh um anao.
aragorn eh um humano.
legolas eh um elfo.
frodo eh um hobbit.
sam eh um hobbit.
gandalf eh um mago.
galadriel eh uma elfa.
merry eh um hobbit.
pippin eh um hobbit.
boromir eh um humano.
arwen eh uma elfa.
bilbo eh um hobbit.
saruman eh um mago.

:-op(100,xfx,vence).
:-op(60,fx,de).

tesoura vence de papel.
papel vence de pedra.
pedra vence de tesoura.

:-op(100,xfx,salva).

doctor salva galifrey.
doctor salva terra.
doctor salva clara.
clara salva doctor.
tardis salva doctor.

X salva Y :-
    X salva Z,
    Z salva Y.

:-op(100,xfx,é).
:-op(80,fx,ancestral).
:-op(80,fx,pai).
:-op(50,fx,de).

joao é pai de pedro.
pedro é pai de jose.
pedro é pai de ana.
jose é pai de antonio.
lucas é pai de joao.

X é ancestral de Y:-
    X é pai de Y.
X é ancestral de Y:-
    X é pai de Z,
    Z é ancestral de Y.
