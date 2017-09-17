%Final work of Prolog discipline
%By: Abrothguer

inicio :-
	menu,
	write('Deseja realmente sair?'), nl,
	removeRespostas,
	leiachar(X), (X == n, !; fail).

menu:-
	repeat,
	write('[1]. Especificar evidencia.'), nl,
	write('[2]. Visualizar evidencias.'), nl,
	write('[3]. Adivinhar animal.'), nl,
	write('[4]. Remover respostas.'), nl,
	write('[5]. Sair'),nl,nl,
	leianum(X),
	opcao(X),
	(X == 53, !; fail).

opcao(49):-
	findall(X,evidencias(X),Lista),
	write('As evidencias disponiveis sao: '), nl,
	showlista_enum(1,Lista),
	write('Digite a evidencia ou o seu respectivo numero na lista acima: '), nl,
	le_atomo(X),
	valida_evidencia(X).

opcao(50):-
	write('Suas evidencias: '), nl,
	findall(X,sim(X),Lista),
	showlista(Lista).

opcao(51):-
	hipotetiza(Animal),
	write('O animal eh '),
	write(Animal), nl,
	removeRespostas.

opcao(52):-
	removeRespostas.

opcao(53).

evidencias(tem_manchas_escuras).
evidencias(tem_pelo).
evidencias(amamenta).
evidencias(tem_listras_pretas).
evidencias(tem_pescoco_grande).
evidencias(tem_pernas_grandes).
evidencias(tem_listras_pretas).
evidencias(nao_voa).
evidencias(nada).
evidencias(branco_e_preto).
evidencias(aparece_em_estoria_de_marinheiro).
evidencias(voa).
evidencias(tem_penas).
evidencias(poe_ovos).
evidencias(come_carne).
evidencias(tem_dentes_pontiagudos).
evidencias(tem_garras).
evidencias(tem_cascos).
evidencias(rumina).

nth(1,[X|_]):-
    !,assert(sim(X)).
nth(_,[]):-
    !,write('Opcao nao encontrada!'),nl,
    write('Favor escolher um numero de 1 a 19...'),nl,nl.

nth(X,[_|Z]):-
    X1 is X - 1,
    nth(X1,Z).

valida_evidencia(X):-
    number(X),!,
    findall(Y,evidencias(Y),Lista),
    nth(X,Lista).

valida_evidencia(X):-
	call(evidencias(X)),!,
	assert(sim(X)).

valida_evidencia(_):-
	write('Digite uma evidencia valida!!!'),nl,
	write('As evidencias sao:'), nl,
	findall(X,evidencias(X),Lista),
	showlista(Lista).

leianum(X):-
	get(Y),
	get0(_),
	validenum(Y,X).

validenum(Y,X):-
	Y < 49,!,
	write('Digite um numero!'), nl,
	leianum(X).

validenum(Y,X):-
	Y > 53,!,
	write('Digite um numero!'), nl,
	leianum(X).

validenum(Y,Y).


leiachar(X):-
	get(Y),
	get0(_),
	validechar(Y,X).

validechar(115,s):-!.
validechar(110,n):-!.
validechar(_,X):-
	write('Digite somente s, para sim, ou n, para nao.'),nl,
	leiachar(X).

showlista([]):-
	!,write('Nao ha evidencias na base de conhecimento'),nl,nl.
showlista([X]):-
	!,write(X),nl,nl.
showlista([X|Y]):-
	write(X),nl,
	showlista(Y).

showlista_enum(X,[Y]):-
    !, write(X), write(' - '), write(Y),nl,nl.

showlista_enum(X,[Y|Z]):-
    X1 is X + 1,
    write(X), write(' - '), write(Y),nl,
    showlista_enum(X1,Z).

le_atomo(X):-
	le_str(String),
	name(X,String).

le_str(String):-
	get0(Ch),
	le_str_aux(Ch,String).

le_str_aux(-1, []):- !.
le_str_aux(10, []):- !.
le_str_aux(13, []):- !.
le_str_aux(Char, [Char|Resto]):-
	le_str(Resto).



/* hipoteses a serem testadas*/
hipotetiza(leopardo) :- leopardo, !.
hipotetiza(tigre) :- tigre, !.
hipotetiza(girafa) :- girafa, !.
hipotetiza(zebra) :- zebra, !.
hipotetiza(avestruz) :- avestruz, !.
hipotetiza(pinguim) :- pinguim, !.
hipotetiza(albatroz) :- albatroz, !.
hipotetiza(desconhecido). /* nao diagnosticado */

/* regras de identificação do animal */
leopardo :-
	mamifero,
	carnivoro,
	verifica(tem_manchas_escuras).
tigre :-
	mamifero,
	carnivoro,
	verifica(tem_listras_pretas).
girafa :-
	ungulado,
	verifica(tem_pescoco_grande),
	verifica(tem_pernas_grandes).
zebra :-
	ungulado,
	verifica(tem_listras_pretas).
avestruz :-
	passaro,
	verifica(nao_voa),
	verifica(tem_pescoco_grande).
pinguim :-
	passaro,
	verifica(nao_voa),
	verifica(nada),
	verifica(branco_e_preto).
albatroz :-
	passaro,
	verifica(aparece_em_estoria_de_marinheiro),
	verifica(voa).

/* regras de classificação */

mamifero :-
	verifica(tem_pelo), !.
mamifero :-
	verifica(amamenta).
passaro :-
	verifica(tem_penas), !.
passaro :-
	verifica(voa),
	verifica(poe_ovos).
carnivoro :-
	verifica(come_carne), !.
carnivoro :-
	verifica(tem_dentes_pontiagudos),
	verifica(tem_garras).
ungulado :-
	mamifero,
	verifica(tem_cascos), !.
ungulado :-
	mamifero,
	verifica(rumina).

/* formulando perguntas */
pergunta(Pergunta) :-
	write('O animal tem a seguinte caracteristica: '),
	write(Pergunta),
	write('? '),
	leiachar(Resposta),
	nl,
	trate(Pergunta,Resposta).

trate(Pergunta,Resposta) :-
	Resposta == s,
	assert(sim(Pergunta)),!.
trate(Pergunta,_) :-
	assert(nao(Pergunta)),fail.

:- dynamic sim/1,nao/1.

/* verificando */

verifica(S) :- sim(S),!.
verifica(S) :- nao(S),!, fail.
verifica(S) :- pergunta(S).

/* remove todas as assercoes de sim e nao */

removeRespostas :-
	retractall(sim(_)),
	retractall(nao(_)).
