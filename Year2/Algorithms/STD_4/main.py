class Node:
    def __init__(self, dataval=None):
        self.dataval = dataval
        self.nextval = None


class SLinkedList:
    def __init__(self):
        self.headval = None

    def listprint(self):
        """
        Method which iterates over each node in the linked list and prints the data stored in
        that element on a new line in the console.
        :return: void
        """
        printval = self.headval             # Sets the first node to be printed to the headval
        while printval is not None:         # While loop to keep iterating while printval has a value
            print(printval.dataval)         # Print the data stored in the node
            printval = printval.nextval     # Set printval to the next node in the linked list

    def AtBeginning(self, newdata):
        """
        Method to create a new node for an empty linked list.
        :param newdata: data to be placed into the new node.
        :return: void
        """
        NewNode = Node(newdata)             # Creates a new node with newdata as its data

    def AtEnd(self, newdata):
        """
        Method to add the last node into a linked list.
        :param newdata: data to be placed into the new node.
        :return: void
        """
        NewNode = Node(newdata)             # Creates a new node with newdata as its data
        if self.headval is None:            # Check if headval is currently empty
            self.headval = NewNode          # Set headval to the node that was created
            return                          # Exit method
        last = self.headval                 # Set last to first node in list
        while (last.nextval):               # Loop while next node isn't None
            last = last.nextval             # Set last to next node
        last.nextval = NewNode              # Add the node as the next node to the current last value

    def Insert(self, val_before, newdata):
        """
        Method to insert node to the middle of the linked list
        :param val_before: node that precedes the node to be added
        :param newdata: data that the new node will hold
        :return: void
        """
        if val_before is None:                  # Check if there is a node to add a new node to
            print("No node to insert after")    # Print message informing the user that the preceding node doesn't exist
            return                              # Exit the program
        else:
            node = Node(newdata)                # Create new node with given data
            node.nextval = val_before.nextval   # Set next value of the new node to the next value of the preceding one
            val_before.nextval = node           # Tag the new node to the preceding node


if __name__ == '__main__':
    list = SLinkedList()
    list.headval = Node("Mon")

    e2 = Node("Tue")
    e3 = Node("Thur")
    e4 = Node("Fri")
    e5 = Node("Sat")
    list.headval.nextval = e2
    e2.nextval = e3
    e3.nextval = e4
    e4.nextval = e5

    list.AtEnd("Sun")

    list.Insert(e2, "Weds")

    list.listprint()
