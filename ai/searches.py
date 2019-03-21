import heapq

MAX_DEPTH = 10

class CountryMap():

    def __init__(self, name):
        self.name = name
        self.cities = 0
        self.__city_relation = {}
        self.__graph = []

    def print_dict(self):
        print(self.__graph)

    def add_city(self, name):
        if self.__city_relation.get(name) is None:
            self.__city_relation[name] = self.cities
            self.__graph.append([])
            self.cities += 1
        # print(self.__city_relation)

    def add_connection(self, city_1, city_2, cost):
        self.__graph[self.__city_relation[city_1]].append( (self.__city_relation[city_2], cost) )

    def depth_search(self, origin, target):

        visited = [False]*self.cities

        return self.__dfs(self.__city_relation[origin], self.__city_relation[target], visited)

    def __dfs(self, origin, target, visited):

        if origin == target:
            return  [[target], 0]

        visited[origin] = True
        for node, cost in self.__graph[origin]:

            if visited[node] is False:
                result = self.__dfs(node, target, visited)
                if result is not None:
                    result[0].append(origin)
                    result[1] += cost
                    return result

        return None

    def iterative_search(self, origin, target, max_depth=MAX_DEPTH):

        for depth in range(max_depth+1):
            result = self.__iddfs(self.__city_relation[origin], self.__city_relation[target], depth)
            if result is not None:
                return result
        return None

    def __iddfs(self, origin, target, limit):

        if origin == target:
            return [[target], 0]
        if limit <= 0:
            return None

        for node, cost in self.__graph[origin]:
            result = self.__iddfs(node, target, limit-1)
            if result is not None:
                result[0].append(origin)
                result[1] += cost
                return result

        return None

    def breadth_search(self, origin, target):

        origin = self.__city_relation[origin]
        target = self.__city_relation[target]

        queue = []
        queue.append(([origin],0))
        result = None

        while True:

            path, total_cost = queue[0]
            print("path = {}; cost = {}".format(path,  total_cost))
            current = path[-1]

            if current == target:
                result = queue[0]
                break
            queue.remove(queue[0])

            for node, cost in self.__graph[current]:

                new_path = list(path)
                new_path.append(node)
                queue.append( ( new_path, total_cost + cost ) )

        return result

    def uniform_search(self, origin, target):

        priority_q = [(0, [self.__city_relation[ origin ]] )]
        result = None

        while True:
            total_cost, path = heapq.heappop(priority_q)
            current = path[-1]

            if current == target:
                result = (path, total_cost)
                break

            for node, cost in self.__graph[current]:

                new_path = list(path)
                new_path.append(node)
                heapq.heappush( priority_q, (cost+total_cost, new_path) )

        return result


def main():
    country = read_file()

    while True:

        choice = input("""Escolha o metodo:\n
                          [0].Largura\n
                          [1].Profundidade\n
                          [2].Custo Uniforme\n
                          [3].Busca Iterativa\n""")
        choice = int(choice)

        city_1 = input("Cidade de origem: ")
        city_2 = input("Cidade de destino: ")

        if choice == 3:
            depth = int(input("Profundidade maxima: "))

        if choice == 0:
            result = country.breadth_search(city_1, city_2)
            print(result)
        elif choice == 1:
            result = country.depth_search(city_1, city_2)
            print(result)
        elif choice == 2:
            result = country.uniform_search(city_1, city_2)
            print(result)
        elif choice == 3:
            result = country.iterative_search(city_1, city_2, depth)
            print(result)
        else:
            break

def read_file():

    filename = input("Nome do arquivo: ")
    print("Lendo arquivo...\n")

    with open(filename) as file:

        name = file.readline()
        country = CountryMap(name)
        file.readline()

        while True:
            line = file.readline().strip()
            if line == '':
                break
            country.add_city(line)

        while True:
            line = file.readline().strip()
            if line == '':
                break
            line = line.split(';')
            country.add_connection(line[0], line[1], int(line[2]))


    print("Feito...\n")
    country.print_dict()
    return country

if __name__ == "__main__":
    main()
