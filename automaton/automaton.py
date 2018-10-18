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
        self.epsilon_transitions = {}

        self.calculate_epsilon()
        # print(f"Epsilon Transitions = {self.epsilon_transitions}")

    def print_automaton(self):
        """ Exibe o automato """

        print("\nAutomato:\n")
        print(f"Alfabeto: {self.alphabet}")
        print(f"Estados: {self.states}")
        print(f"Estado Inicial: {self.initial}")
        print(f"Estados Finais: {self.finals}")
        print(f"Funcao de transicao: {self.function}\n")

    def calculate_epsilon(self):
        """ Calcula o Epsilon-fecho para cada estado do automato """

        visited = {}
        calculated = {}
        for state in self.states:
            self.epsilon_transitions[state] = self.function[state]['&']
            visited[state] = False
            calculated[state] = False

        for state in self.states:
            if not calculated[state]:
                self.calculate_epsilon_transition(state, calculated, visited)
                for state in visited:
                    visited[state] = False


    def calculate_epsilon_transition(self, state, calculated, visited):
        """ Calcula o Epsilon-fecho para um estado do automato """

        if calculated[state]:
            return
        if visited[state]:
            return

        visited[state] = True
        natural_closure = self.function[state]['&']

        if natural_closure == [state]:
            calculated[state] = True
            return

        for ep_state in natural_closure:
            self.calculate_epsilon_transition(ep_state, calculated, visited)
            self.epsilon_transitions[state] = self.epsilon_transitions[state].union(
                self.epsilon_transitions[ep_state])


    def verify_chain(self, chain, verbose=False):
        """ Faz a verificacao de uma dada cadeia """

        current_states = {self.initial}
        if chain == "":
            # print(self.get_transition(self.initial, '&'))
            if self.epsilon_transitions[self.initial].intersection(self.finals):
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

    def get_transition(self, state, symbol):
        """ Calcula o novo estado, dado o estado atual e o simbolo lido """

        generated_states = set()

        for ep_state in self.epsilon_transitions[state]:
            new_states = self.function[ep_state].get(symbol)
            if new_states is None:
                continue
            generated_states = generated_states.union(new_states)
        return generated_states


def main():
    """ Le cadeias e verifica se as mesmas pertencem ao automato """

    data = read_automaton()
    automaton = Automaton(data[0], data[1], data[2], data[3], data[4])
    automaton.print_automaton()

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

    states = set(autfile.readline().strip().replace(' ', '').split(';'))
    states = states - {'@'}
    alphabet = set(autfile.readline().strip().replace(' ', '').split(';'))
    initial = autfile.readline().strip().replace(' ', '')

    if initial not in states:
        print(f"Estado inicial nao reconhecido: {initial}!")
        return None

    finals = set(autfile.readline().strip().replace(' ', '').split(';'))
    finals = finals - {'@'}

    if finals - states:
        print(f"Estado(s) final nao reconhecido: {finals - states}")
        return None

    function = {}
    for state in states:
        function[state] = {}
        function[state]['&'] = {state}

    while True:
        delta = autfile.readline().replace(' ', '').strip().split(';')
        if delta == [""]:
            break

        flag = False
        if len(delta) < 3:
            print(f"Padrao nao reconhecido na funcao {delta}")
            flag = True
        if delta[0] not in states:
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

        if delta[2] != '@' and function[delta[0]].get(delta[1]) is not None:
            function[delta[0]][delta[1]] = function[delta[0]][delta[1]].union(set([delta[2]]))
        elif delta[2] != '@':
            function[delta[0]][delta[1]] = set([delta[2]])

        # print(f"Para {delta[0]} com {delta[1]} = {function[delta[0]][delta[1]]}")

    return (states, alphabet, function, finals, initial)


if __name__ == "__main__":
    main()
