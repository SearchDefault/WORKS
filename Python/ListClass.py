class Node():
    def __init__(self, data, prev = None, next = None):
        self.__data = data
        self.prev = prev
        self.next = next
        pass


    def getData(self):
        return self.__data
        pass


    def __str__(self):
        Str = 'data: ' + str(self.getData()) + ', ' + 'prev: '
        if self.prev is None:
            Str += 'None' + ', ' + 'next: '
        else:
            Str += str(self.prev.getData()) + ', ' + 'next: '
        if self.next is None:
            Str += 'None'
        else:
            Str += str(self.next.getData())
        return Str
        pass


class LinkedList:
    def __init__(self, first = None, last = None): 
        self.first = first
        self.last = last
        self.__length = 0
        if self.first is not None and self.last is not None:
            self.__length = 2
            self.first = Node(self.first)
            self.last = Node(self.last, self.first)
            self.first.next = self.last
        elif self.first is not None and self.last is None:
            self.__length = 1
            self.first = Node(self.first)
            self.last = self.first
        elif self.first is None and self.last is not None:
            raise ValueError('invalid value for last')
        pass


    def __len__(self):
        return self.__length
        pass


    def __str__(self):
        if self.__length == 0:
            return 'LinkedList[]'
        if self.__length == 1:
            return 'LinkedList[length = ' + str(self.__length) + ',' + ' [' + str(self.first) + ']]'
        if self.__length > 1:
            num = self.first
            Str = 'LinkedList[length = ' + str(self.__length) + ',' + ' [' + str(num)
            num = num.next
            while num != None:
                Str += '; ' + str(num)
                num = num.next
            Str += ']]'
            return Str
        pass


    def clear(self):
        LinkedList.__init__(self)
        pass


    def append(self, element):
        self.__length += 1
        if self.__length >= 2:
            self.last.next = Node(element, self.last)
            self.last = self.last.next
        else:
            self.first = Node(element)
            self.last = self.first
        pass


    def pop(self):
        if self.__length is 0:
            raise IndexError('LinkedList is empty!')
        if self.__length is 1:
            LinkedList.__init__(self)
            return
        self.last = self.last.prev
        self.last.next = None
        self.__length -= 1
        pass


    def popitem(self, element):
        flag = 0
        if self.__length == 0:
            raise KeyError(str(element) + " doesn't exist!")
        num = self.first
        while num.getData() is not element:
            if num is None:
                break
            num = num.next
        if num.next is None:
            flag = 1
            self.pop()
        elif num.prev is not None and num.next is not None:
            num.next.prev = num.prev
            num.prev.next = num.next
            self.__length -= 1
        else:
            self.first = self.first.next
            self.first.prev = None
            self.__length -= 1
            flag = 1
        if flag is 0:
            raise KeyError(str(element) + " doesn't exist!")
        pass
