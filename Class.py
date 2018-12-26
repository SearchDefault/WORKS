class List(list):
    def append(self, x):
        return super(List, self).append(x)
        
    def st_append(self, x):
        return super(List, self).insert(0, x)
    
    def pop(self):
        return super(List, self).pop()
    
    def st_pop(self):
        return super(List, self).pop(0)

x = List([1,2,3,4,5])
x.st_pop()
print (x)
