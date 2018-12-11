"""
Trabalho de LFA, criacao de um automato de pilha


Consideracoes:
    - @ Denota o estado vazio
    - & Denota a palavra vazia epsilon
    - ! Denota o estado Z0 da pilha
"""

class PushdownAutomaton(object): #pylint: disable=R0902
    """ Implementa o automato de pilha """

    def __init__(self, states, alphabet, stack_symbols, function, initial, stack_initial, finals): #pylint: disable=R0913

        self.states = states
        self.alphabet = alphabet
        self.stack_symbols = stack_symbols
        self.function = function
        self.initial = initial
        self.stack_initial = stack_initial
        self.finals = finals

    def print_automaton(self):
        """ Exibe o automato """

        print("\nAutomato:\n")
        print(f"Alfabeto: {self.alphabet}")
        print(f"Estados: {self.states}")
        print(f"Estado Inicial: {self.initial}")
        print(f"Estados Finais: {self.finals}")
        print(f"Estado Inicial da pilha: {self.stack_initial}")
        print(f"Simbolos da pilha: {self.stack_symbols}")
        print(f"Funcao de transicao: ")
        for key in self.function:
            print('Para', key, ':')
            for value in self.function[key]:
                print('Lendo', value, ':', self.function[key][value])

    def verify_chain(self, chain):
        """ Verifica se uma cadeia pertence ou nao ao automato """

        if chain == "":
            visited = {}
            for original_state in self.states:
                visited[original_state] = {}

            values = self.get_epsilon_transition(self.initial, tuple(self.stack_initial), visited)
            generated_finals = {x for x, _ in values}

            print(f"Finals = {generated_finals}")
            if generated_finals.intersection(self.finals):
                return True
            return False

        current_pairs = {(self.initial, tuple(self.stack_initial))}

        for symbol in chain:
            if symbol not in self.alphabet:
                return False

            print(f"Current states = {current_pairs}, Symbol = {symbol}")

            generated_states = set()
            for state, stack in current_pairs:
                generated_states = generated_states.union(self.get_transition(state, symbol, stack))

            print(f"Generated = {generated_states}\n\n")

            if not generated_states:
                return False
            else:
                current_pairs = generated_states

        if self.finals.intersection({state for state, _ in current_pairs}):
            return True
        return False

    def get_transition(self, state, symbol, stack):
        """ Calcula o novo estado e a pilha, com base no simbolo e no topo atual da pilha """

        stack = list(stack)
        topmost = stack.pop()
        # print(f"Getting transition for {state, symbol, topmost}")

        try:
            trivial_value = self.function[state][symbol].get(topmost)
        except KeyError:
            return set()
        # print(f"Trivial is {trivial_value}")

        if trivial_value is None:
            return set()

        new_stack = push_to_stack(stack, trivial_value[1::])

        visited = {}
        for original_state in self.states:
            visited[original_state] = {}
        epsilon_values = self.get_epsilon_transition(trivial_value[0], list(new_stack), visited)

        print(f"Episilon values = {epsilon_values}")
        # print(f"GenFunc = {epsilon_values.union({(trivial_value[0], new_stack)})}")

        return epsilon_values.union({(trivial_value[0], new_stack)})

    def get_epsilon_transition(self, state, stack, visited):
        """ Calcula o Epsilon fecho de um determinado estado e pilha """

        stack = list(stack)
        topmost = stack.pop()

        print(f"Finding Epsilon {state} for {topmost}")

        if visited[state].get(topmost) is not None:
            return set()

        visited[state][topmost] = True
        epsilon_value = self.function[state]['&'].get(topmost)

        if epsilon_value is None:
            return set()

        final_stack = push_to_stack(stack, epsilon_value[1::])

        recursive_epsilons = self.get_epsilon_transition(epsilon_value[0],
                                                         list(final_stack), visited)
        return recursive_epsilons.union({(epsilon_value[0], final_stack)})

def push_to_stack(stack, values):
    """ Empilha valores na pilha """
    stk_list = list(stack)

    for value in values[::-1]:
        if value != '&':
            stk_list.append(value)
    return tuple(stk_list)

def main():
    """ Le cadeias e verifica se as mesmas pertencem ao automato """

    data = read_automaton()
    automaton = PushdownAutomaton(*data)
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
    stack_alphabet = set(autfile.readline().strip().replace(' ', '').split(';'))

    initial = autfile.readline().strip().replace(' ', '')
    stack_initial = autfile.readline().strip().replace(' ', '')

    if initial not in states:
        print(f"Estado inicial nao reconhecido: {initial}!")
        return None

    finals = set(autfile.readline().strip().replace(' ', '').split(';'))
    finals = finals - {'@'}

    if finals - states:
        print(f"Estado(s) final nao reconhecido: {finals - states}")
        return None

    function = read_function(autfile, states, alphabet, stack_alphabet)
    if function is None:
        return None

    return (states, alphabet, stack_alphabet, function, initial, stack_initial, finals)

def read_function(autfile, states, alphabet, stack_alphabet):
    """ Le a funcao de transicao do arquivo """

    function = {}
    for state in states:
        function[state] = {}
        function[state]['&'] = {}

    while True:
        delta = autfile.readline().replace(' ', '').strip().split(';')
        if delta == [""]:
            break

        flag = False
        if len(delta) < 5 or len(delta) > 6:
            print(f"Padrao nao reconhecido na funcao {delta}")
            flag = True
        if delta[0] not in states or delta[3] not in states:
            print(f"Estado nao reconhecido na funcao'")
            flag = True
        if delta[1] not in alphabet and delta[1] != '&':
            print(f"Simbolo {delta[1]} nao reconhecido na funcao")
            flag = True
        if (delta[2] not in stack_alphabet and delta[2] != '&') or \
           (delta[4] not in stack_alphabet and delta[4] != '&'):
            print(f"Simbolo de pilha nao reconhecido")
            flag = True
        if len(delta) > 5 and delta[4] not in stack_alphabet:
            print(f"Simbolo de pilha nao reconhecido")
            flag = True
        if flag:
            return None

        new_tuple = tuple(delta[3:])

        if function[delta[0]].get(delta[1]) is not None:
            function[delta[0]][delta[1]] = {**function[delta[0]][delta[1]], delta[2]:new_tuple}
        else:
            function[delta[0]][delta[1]] = {delta[2]:new_tuple}

        print(f"Para {delta[0]} com {delta[1]} e pilha {delta[2]} = {function[delta[0]][delta[1]]}")
    return function

if __name__ == "__main__":
    main()
