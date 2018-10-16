"""
Trabalho de LFA, criacao de uma classe Automaton que implementa a quintupla de
um automato e verifica se determinadas cadeias pertencem ou nao a esse automato

Consideracoes:
    - @ Denota o estado vazio
    - & Denota a palavra vazia epsilon
"""


class Automaton(object):
    """ Implementa o objeto automato """

    def __init__(self, states, alphabet, function, finals, initial):  # pylint: disable=R0913
        """ Inicializacao da quintupla """
        self.states = states
        self.alphabet = alphabet
        self.function = function
        self.finals = finals
        self.initial = initial

        # print(f" States:{self.states}")
        # print(f" Alpha:{self.alphabet}")
        # print(f" Finals:{self.finals}")
        # print(f" Initial:{self.initial}")
        # print(f" Function:{self.function}")

    def verify_chain(self, chain, verbose=False):
        """ Faz a verificacao de uma dada cadeia """

        current_states = {self.initial}
        if chain == "":
            # print(self.get_transition(self.initial, '&'))
            if self.get_transition(self.initial, '&').intersection(self.finals):
                return True
            return False

        for symbol in chain:
            if symbol not in self.alphabet:
                return False

            generated_states = set()
            if verbose:
                print(f"Estados Atuais: {current_states}, Simbolo lido: {symbol}")

            for state in current_states:
                generated_states = generated_states.union([new_state for new_state in set(
                    self.get_transition(state, symbol)) if new_state is not None])

            if not generated_states:
                return False
            else:
                current_states = generated_states

        for state in current_states:
            current_states = current_states.union(self.get_transition(state, '&'))
        if verbose:
            print(f"Estados Atuais: {current_states}")
        if current_states.intersection(set(self.finals)):
            return True
        return False

    def get_transition(self, state, symbol, visited=[]):  # pylint: disable=W0102
        """ Calcula o novo estado, dado o estado atual e o simbolo lido """

        natural_states = self.function[state].get(symbol)
        epsilon_states = self.function[state].get("&")
        generated_states = set()

        if visited == []:
            visited.append(state)
        for ep_state in epsilon_states:
            if ep_state not in visited:
                generated_states = generated_states.union(
                    self.get_transition(ep_state, symbol, visited))

        if natural_states is None:
            return generated_states
        return natural_states.union(generated_states)


def main():
    """ Le cadeias e verifica se as mesmas pertencem ao automato """

    data = read_automaton()
    automaton = Automaton(data[0], data[1], data[2], data[3], data[4])

    while True:
        print("Digite uma cadeia: ")
        try:
            chain = input()
        except EOFError:
            break

        recognize = automaton.verify_chain(chain)

        if recognize:
            print(f"A cadeia '{chain}' eh reconhecida pelo automato\n")
        else:
            print(f"A cadeia '{chain}' nao eh reconhecida pelo automato\n")


def read_automaton():
    """ Le o automato e retorna uma quintupla ou None caso haja erro """

    autfile = open(input("Arquivo: "))

    states = set(autfile.readline().strip().replace(' ', '').split(','))
    alphabet = set(autfile.readline().strip().replace(' ', '').split(','))
    initial = autfile.readline().strip().replace(' ', '')

    if initial not in states:
        print(f"Estado inicial nao reconhecido: {initial}!")
        return None

    finals = set(autfile.readline().strip().replace(' ', '').split(','))

    if finals - states:
        print(f"Estado(s) final nao reconhecido: {finals - states}")
        return None

    function = {}
    for state in states:
        function[state] = {}
        function[state]['&'] = set()

    while True:
        delta = autfile.readline().replace(' ', '').strip().split(';')
        if delta == [""]:
            break

        flag = False
        if len(delta) < 3:
            print(f"Padrao nao reconhecido na funcao {delta}")
            flag = True
        if delta[0] not in states and delta[0] != '@':
            print(f"Estado nao reconhecido na funcao: '{delta[0]}'")
            flag = True
        if delta[2] not in states and delta[2] != '@':
            print(f"Estado nao reconhecido na funcao: '{delta[2]}'")
            flag = True
        if delta[1] not in alphabet and delta[1] != '&':
            print(f"Simbolo {delta[1]} nao reconhecido na funcao")
            flag = True
        if flag:
            return None

        if function[delta[0]].get(delta[1]) is not None:
            function[delta[0]][delta[1]] = function[delta[0]][delta[1]].union(set([delta[2]]))
        else:
            function[delta[0]][delta[1]] = set([delta[2]])

        # print(f"Para {delta[0]} com {delta[1]} = {function[delta[0]][delta[1]]}")

    return (states, alphabet, function, finals, initial)


if __name__ == "__main__":
    main()
