"""
Trabalho de LFA, criacao de uma classe RegularExpression que implementa uma expresão regular
e converte a mesma para seu respectivo automato

Consideracoes:
    - @ Denota o estado vazio
    - & Denota a palavra vazia epsilon
"""

import automaton
from collections import defaultdict

PREC = defaultdict(int)
PREC['*'] = 3
PREC['.'] = 2
PREC['+'] = 1


class RegularExpression(object):
    """ Implementa uma expressao regular """

    def __init__(self, expression):

        self.expression = expression
        self.postfix_expression = self.infix_to_postfix()
        self.automaton = None
        self.binary_tree = None

    def infix_to_postfix(self):
        """ Converte uma expressao infixa para uma posfixa """
        stack = []
        postfix = []

        for element in self.expression:
            if element == '(':
                stack.append(element)

            elif element == ')':
                while True:
                    stack_value = stack.pop()
                    if stack_value == '(':
                        break
                    postfix.append(stack_value)

            elif element in '*.+':
                while stack != [] and PREC[element] <= PREC[stack[-1]]:
                    postfix.append(stack.pop())
                stack.append(element)

            else:
                postfix.append(element)

        while stack != []:
            postfix.append(stack.pop())

        self.postfix_expression = postfix
        # print(f"Postfix is {self.postfix_expression}")

    def union_to_automaton(self, first_aut, second_aut):
        """ Converte uma expressao de uniao em seu respectivo automato """
        pass

    def concatenation_to_automaton(self, head_aut, tail_aut):
        """ Converte uma expressao de concatenacao em seu respectivo automato """
        pass

    def closure_to_automaton(self, first_aut, second_aut):
        """ Converte uma expressao de fechamento em seu respectivo automato """
        pass

    def create_binary_tree(self):
        """ Cria uma arvore binaria a partir da expressao posfixa """
        pass

    def create_automaton(self):
        """ Cria o automato que corresponde a expressao """
        pass


def main():
    """ Le e cria expressoes regulares, exibindo os automatos gerados """

    while True:
        print("Digite uma expressao: ")
        try:
            expression = input()
        except EOFError:
            break

        regex = RegularExpression(expression)
        nfa_epsilon = regex.create_automaton()


if __name__ == "__main__":
    main()
