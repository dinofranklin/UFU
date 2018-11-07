"""
Trabalho de LFA, criacao de uma classe RegularExpression que implementa uma expressao regular
e converte a mesma para seu respectivo automato

Consideracoes:
    - @ Denota o estado vazio
    - & Denota a palavra vazia epsilon
"""

from collections import defaultdict
from automaton import Automaton
from binary_tree import BinaryTree

PREC = defaultdict(int)
PREC['.'] = 2
PREC['+'] = 1
PREC['*'] = 3
CSTE = 0

class RegularExpression(object):
    """ Implementa uma expressao regular """

    def __init__(self, expression):

        self.expression = expression.replace(' ', '')
        if self.expression == "":
            raise ValueError("Expressao Vazia")
        self.postfix_expression = self.infix_to_postfix()
        self.automaton = None
        self.expression_tree = None
        self.create_expression_tree()

    def infix_to_postfix(self):
        """ Converte uma expressao infixa para uma posfixa """
        stack = []
        postfix = []
        previous = False

        for element in self.expression:
            if element == '(':
                previous = False
                stack.append(element)

            elif element == ')':
                previous = False
                while True:
                    stack_value = stack.pop()
                    if stack_value == '(':
                        break
                    postfix.append(stack_value)

            elif element in '.+':
                previous = False
                while stack != [] and PREC[element] <= PREC[stack[-1]]:
                    postfix.append(stack.pop())
                stack.append(element)

            elif element == '*':
                previous = False
                while stack != [] and PREC[element] <= PREC[stack[-1]]:
                    postfix.append(stack.pop())
                stack.append(element)

            else:
                if previous:
                    while stack != [] and PREC['.'] <= PREC[stack[-1]]:
                        postfix.append(stack.pop())
                    stack.append('.')
                    postfix.append(element)
                    previous = True
                else:
                    postfix.append(element)
                    previous = True


        while stack != []:
            postfix.append(stack.pop())

        print(f"Postfix is {postfix}")
        return postfix

    def union_to_automaton(self, first_aut, second_aut):
        """ Converte uma expressao de uniao em seu respectivo automato """

        global CSTE
        final_state = 'Q'+str(CSTE)
        finals = {final_state}
        CSTE += 1
        initial = 'Q'+str(CSTE)
        CSTE += 1
        states = first_aut.states.union(second_aut.states).union({initial, final_state})
        alphabet = first_aut.alphabet.union(second_aut.alphabet)

        resulting_function = {}
        resulting_function.update(first_aut.function)
        resulting_function.update(second_aut.function)

        resulting_function[initial] = {'&': {initial, first_aut.initial, second_aut.initial}}
        resulting_function[final_state] = {'&': finals}

        for final in first_aut.finals.union(second_aut.finals):
            resulting_function[final]['&'].add(final_state)

        # print(f"resulting_function = {resulting_function}")

        return Automaton(states, alphabet, resulting_function, finals, initial)

    def closure_to_automaton(self, automaton):
        """ Converte o fechamento para um automato """

        print("I have this dude: ")
        automaton.print_automaton()

        global CSTE
        final_state = 'Q'+str(CSTE)
        finals = {final_state}
        CSTE += 1
        initial = 'Q'+str(CSTE)
        CSTE += 1
        states = automaton.states.union({initial, final_state})
        alphabet = automaton.alphabet

        resulting_function = {}
        resulting_function.update(automaton.function)

        resulting_function[initial] = {'&': {initial, automaton.initial, final_state}}
        resulting_function[final_state] = {'&': finals}
        
        finals_copy = automaton.finals.copy()
        for final in finals_copy:
            resulting_function[final]['&'].add(automaton.initial)
            resulting_function[final]['&'].add(final_state)

        # print(f"resulting_function = {resulting_function}")

        return Automaton(states, alphabet, resulting_function, finals, initial)

    def concatenation_to_automaton(self, first_aut, second_aut):
        """ Converte uma expressao de concatenacao em seu respectivo automato """

        states = first_aut.states.union(second_aut.states)
        finals = second_aut.finals
        initial = first_aut.initial
        alphabet = first_aut.alphabet.union(second_aut.alphabet)

        resulting_function = {}
        resulting_function.update(first_aut.function)
        resulting_function.update(second_aut.function)

        finals_copy = first_aut.finals.copy()
        for final in finals_copy:
            resulting_function[final]['&'].add(second_aut.initial)

        return Automaton(states, alphabet, resulting_function, finals, initial)

    
    def create_expression_tree(self):
        """ Cria uma arvore binaria a partir da expressao posfixa """

        if len(self.postfix_expression) == 1:
            self.expression_tree = BinaryTree(self.postfix_expression[0])
            return

        stack = []
        for value in self.postfix_expression:

            if value in '.+':

                right = stack.pop()
                left = stack.pop()
                bin_tree = BinaryTree(value)
                bin_tree.set_left_child(left)
                bin_tree.set_right_child(right)
                stack.append(bin_tree)

            elif value == '*':

                right = stack.pop()
                bin_tree = BinaryTree(value)
                bin_tree.set_right_child(right)
                stack.append(bin_tree)

            else:
                stack.append(value)

        input()

        self.expression_tree = stack[0]
        self.expression_tree.print_treeview()

        input()

    def create_automaton(self, current_node=None):
        """ Cria o automato que corresponde a expressao """

        if current_node is None:
            current_node = self.expression_tree

        # print(f"Current node is {current_node.get_value()}")

        if current_node.get_left_child() is None and current_node.get_right_child() is None:
            global CSTE
            state = 'Q'+str(CSTE)
            CSTE += 1
            final = 'Q'+str(CSTE)
            CSTE += 1
            function = {state: {'&': {state}, current_node.get_value(): {final}}, final: {'&': {final}}}
            aut = Automaton({state, final}, {current_node.get_value()}, function, {final}, state)
            return aut

        if current_node.get_left_child() is not None:
            left_aut = self.create_automaton(current_node.get_left_child())
        if current_node.get_right_child() is not None:
            right_aut = self.create_automaton(current_node.get_right_child())

        if current_node.get_value() == '.':
            return self.concatenation_to_automaton(left_aut, right_aut)

        if current_node.get_value() == '+':
            return self.union_to_automaton(left_aut, right_aut)

        # O valor eh *
        if current_node.get_left_child() is not None:
            return self.closure_to_automaton(left_aut)
        else:
            return self.closure_to_automaton(right_aut)


def main():
    """ Le e cria expressoes regulares, exibindo os automatos gerados """

    while True:
        print("Digite uma expressao: ")
        try:
            expression = input()
        except EOFError:
            break

        try:
            regex = RegularExpression(expression)
            nfa_epsilon = regex.create_automaton()

            nfa_epsilon.print_automaton()

            filename = 'newaut.txt'
            print(f"Salvando automato no arquivo '{filename}'")
            nfa_epsilon.print_to_file()
            print(f"Automato salvo!\n")
        except ValueError:
            print("Expressao regular vazia")


if __name__ == "__main__":
    main()
