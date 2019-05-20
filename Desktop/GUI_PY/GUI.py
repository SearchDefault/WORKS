from tkinter import *

class Window (Frame):

	def __init__ ( self, parent ):

		Frame.__init__ ( self, parent, background = "white" )
		self.parent = parent
		self.initUI ()

		pass

	def initUI ( self ):

		self.parent.title ( "##NEW WINDOW##" )

		self.pack ( fill = BOTH, expand = 1 )

		exitButton = Button ( self, text = "Exit", command = self.quit, width = 100, height = 5 )
		exitButton.pack ()

		pass


if __name__ == "__main__":

	root = Tk ()

	root.geometry ( "800x600" )

	app = Window ( root )

	root.mainloop ()

	pass
