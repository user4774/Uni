class Graph(object):
    """
    Class to represent a matrix graph, with functionality to add vertices, add or remove edges and print the matrix.
    """

    def __init__(self, size):
        """
        Constructor for the Graph class, takes size as input and uses it to create a list of lists corresponding to
        the size input and then fills each list with the same amount of zeroes.
        :param size: integer parameter that defines the size of the matrix.
        """
        self.adjMatrix = []                                     # Initialises empty list for the matrix.
        for i in range(size):                                   # Loop that runs input amount of times.
            self.adjMatrix.append([0 for i in range(size)])     # Adds a list with all zeroes to adjMatrix list.
        self.size = size                                        # Sets size to size variable.

    def add_vertex(self):
        """
        Graph method to add a new vertex to the graph with all zeroes as values.
        :return: void
        """
        self.size += 1                                          # Increment the size of graph by one
        for row in self.adjMatrix:                              # Loop through each existing row in matrix
            row.append(0)                                       # Append zero to already existing list in adjMatrix
        self.adjMatrix.append([0 for i in range(self.size)])    # add a new row initialised with all zeroes at the end

    def add_edge(self, first_vertex, second_vertex):
        """
        Adds new edge to the matrix by changing the corresponding edge value from zero to new specified value.
        :param first_vertex: Vertex in the form of an integer that represents one side of the edge.
        :param second_vertex: Vertex in the form of an integer that represents the other side of the edge.
        :return: void
        """
        if (0 < first_vertex <= self.size) and (0 < second_vertex <= self.size):    # Check if both vertices exist
            if self.adjMatrix[first_vertex - 1][second_vertex - 1] == 0:            # Check if edge already has a value
                self.adjMatrix[first_vertex - 1][second_vertex - 1] = 1            # Add value for edge between vertices
            else:
                print("Edge already exists!")                                     # inform user that edge already exists

    def remove_edge(self, first_vertex, second_vertex):
        """
        Removes existing edge between vertices by changing its value in the matrix between them to zero.
        :param first_vertex: Vertex as integer pointing to one end of the edge.
        :param second_vertex: Vertex as integer pointing to the other end of the edge.
        :return: void
        """
        if (0 < first_vertex <= self.size) and (0 < second_vertex <= self.size):    # Check if vertices exist
            if self.adjMatrix[first_vertex - 1][second_vertex - 1] == 1:            # Check if edge exists
                self.adjMatrix[first_vertex - 1][second_vertex - 1] = 0  # If both true, remove edge, setting it to zero
            else:
                print("Edge doesn't exist!")                                        # Inform user if edge doesn't exist

    def print_matrix(self):
        """
        Prints out existing matrix by formatting it into a table of edges based on vertices.
        :return: void
        """
        size = self.size        # Save graph size in size variable
        count = 0               # Set counter to 0
        while size // 10 != 0:  # Loop until size divided by 10 is 0
            size = size // 10   # Divide size by 10
            count += 1          # Increment counter by 1
        for i in range(self.size):      # Loop over size of matrix
            if i == 0:                  # Check if first loop
                print("    " + (' ' * count) + str(i + 1), end='')   # Print space based on largest int, prevent newline
            else:
                print("   " + (' ' * (len(str(self.size)) -
                                      len(str(i + 1)))) + str(i + 1), end='')  # Print vertices with variable space len
        print("\n    " + (' ' * count) + '-' * (
                self.size + (2 + 1 * (len(str(self.size)))) * (self.size - 1)))  # Print line between vertices and edges
        for i in range(self.size):      # Loop over size of matrix again
            print(str(i + 1) + (' ' * (len(str(self.size)) -
                                       len(str(i + 1)))) + " | ", end='')  # Print other vertex with '|' as separator
            for j in range(self.size):      # Inner loop over size of matrix
                print(str(self.adjMatrix[j][i]) + "  " +
                      (' ' * (len(str(self.size)))), end='')  # Print edge values with variable space length
            print('')       # Print newline after last edge value


def main():
    g = Graph(6)
    g.add_vertex()
    g.add_vertex()
    g.add_edge(1, 6)
    g.print_matrix()


if __name__ == '__main__':
    main()
