"""
Trabalho de LFA, criacao de uma classe RegularExpression que implementa uma expresão regular
e converte a mesma para seu respectivo automato

Consideracoes:
    - @ Denota o estado vazio
    - & Denota a palavra vazia epsilon
"""

from automaton import Automaton
from collections import defaultdict
from binary_tree import BinaryTree

PREC = defaultdict(int)
PREC['.'] = 2
PREC['+'] = 1
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

        resulting_function = {}
        resulting_function.update(first_aut.function)
        resulting_function.update(second_aut.function)




    def concatenation_to_automaton(self, head_aut, tail_aut):
        """ Converte uma expressao de concatenacao em seu respectivo automato """



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

            else:
                stack.append(value)

        self.expression_tree = stack[0]
        self.expression_tree.print_treeview()

    def create_automaton(self, current_node = None):
        """ Cria o automato que corresponde a expressao """

        if current_node is None:
            current_node = self.expression_tree

        if current_node.get_left_child() == None and current_node.get_right_child() == None:
            state = 'Q'+CSTE
            CSTE += 1
            final = 'Q'+CSTE
            CSTE += 1
            return Automaton({state, final}, current_node.get_value(), {state: {'&': {state}} {current_node.get_value(): {final}}}, {final}, state)

        left_aut = create_automaton(current_node.get_left_child())
        right_aut = create_automaton(current_node.get_right_child())

        if current_node.get_value() == '.':
            return self.concatenation_to_automaton(left_aut, right_aut)

        if current_node.get_value() == '+':
            return self.union_to_automaton(left_aut, right_aut)


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
        except ValueError:
            print("Expressao regular vazia")


if __name__ == "__main__":
    main()
