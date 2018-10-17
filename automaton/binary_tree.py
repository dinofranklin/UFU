"""
Implementacao simples de uma arvore binaria
"""

class BinaryTree(object):
    """ Implementa arvore binaria """

    def __init__(self, value):

        self.value = value
        self.right_child = None
        self.left_child = None

    def print_treeview(self, space=0):

        print(f' '*space + f"|{self.value}")

        if self.left_child:
            self.left_child.print_treeview(space = space+4)
        if self.right_child:
            self.right_child.print_treeview(space = space+4)


    def set_right_child(self, bin_tree):

        if type(bin_tree) != BinaryTree:
            bin_tree = BinaryTree(bin_tree)
        self.right_child = bin_tree

    def set_left_child(self, bin_tree):

        if type(bin_tree) != BinaryTree:
            bin_tree = BinaryTree(bin_tree)
        self.left_child = bin_tree

    def get_value(self):

        return self.value

    def get_right_child(self):

        return self.right_child

    def get_left_child(self):

        return self.left_child
