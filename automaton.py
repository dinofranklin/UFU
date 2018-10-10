"""
Trabalho de LFA, criacao de uma classe Automaton que implementa a quintupla de
um automato e verifica se determinadas cadeias pertencem ou nao a esse automato

Consideracoes:
    - @ Denota o estado vazio
    - & Denota a palavra vazia epsilon
"""


class Automaton(object):
    """ Implementa o objeto automato """

    def __init__(self, states, alphabet, function, finals, initial):

        """ Inicializacao da quintupla """
        self.states = states
        self.alphabet = alphabet
        self.function = function
        self.finals = finals
        self.initial = initial

        """
        print(f" States:{self.states}")
        print(f" Alpha:{self.alphabet}")
        print(f" Finals:{self.finals}")
        print(f" Initial:{self.initial}")
        print(f" Function:{self.function}")
        """


    def verify_chain(self, chain, verbose=False):
        """ Faz a verificacao de determinada cadeia """

        current_states = {self.initial}

        for symbol in chain:
            newest_states = set()

            if verbose: print(f"Estados: {current_states}, Simbolo: {symbol}")

            for state in current_states:
                transitions = self.get_transition(state, symbol)
                if transitions is None:
                    if verbose: print(f"{symbol} nao reconhecido")
                    return False

                for new_state in transitions:
                    if new_state is None:
                        pass
                    else:
                        newest_states.add(new_state)

            if len(newest_states) == 0:
                if verbose: print("Estados: {}")
                return False

            current_states = newest_states

        if verbose: print(f"Estados: {current_states}")
        for state in current_states:
            if state in self.finals:
                return True

        return False

    def get_transition(self, state, symbol):
        """ Calcula o novo estado, dado o estado atual e o simbolo lido """

        if symbol not in self.alphabet:
            return None

        return self.function[state][symbol]


def main():

    states = set(input().replace(' ','').split(','))
    alphabet = set(input().replace(' ', '').split(','))
    initial = input()

    if initial not in states:
        print(f"Estado inicial nao reconhecido: {initial}!")
        return

    finals = set(input().replace(' ', '').split(','))

    for state in finals:
        if state not in states:
            print(f"Estado final nao reconhecido: {state}")
            return

    function = {}
    symbol_order = []
    for i in range(0, len(states)+1):

        if i == 0:
            symbol_order = input().replace(' ','').split(';')
            for symbol in symbol_order:
                if symbol not in alphabet:
                    print(f"Simbolo nao reconhecido {symbol}")
                    return

            if len(symbol_order) > len(alphabet):
                print(f"Funcao nao contempla todo o alfabeto!")
                return

        else:
            transitions = input().replace(' ', '').split(';')
            if len(transitions) < (len(alphabet)+1):
                print(f"Funcao nao contempla todas transicoes para {transitions[0]}")
                return

            main_state = transitions[0]
            if main_state in function.keys():
                print(f"Estado {main_state} ja contemplado na funcao de transicao!")
                return

            function[main_state] = {}
            for j in range(1, len(transitions)):
                function[main_state][symbol_order[j-1]] = [None if x == '@' else x for x in transitions[j].split(',')]

                for value in function[main_state][symbol_order[j-1]]:
                    if value is not None and value not in states:
                        print(f"Estado nao reconhecido {value} na funcao de transicao!")
                        return

    automaton = Automaton(states, alphabet, function, finals, initial)

    while True:
        try:
            chain = input()
        except EOFError:
            break

        recognize = automaton.verify_chain(chain)

        if recognize:
            print(f"A cadeia {chain} e reconhecida pelo automato")
        else:
            print(f"A cadeia {chain} nao e reconhecida pelo automato")


if __name__ == "__main__":
    main()
