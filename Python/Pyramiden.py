
print ("Please enter the height of your pyramide")
height =int(input())

decrement=height
z=1

for i in range (height):
	for j in range (decrement, 1, -1):
		print(' ', end="")
	decrement = decrement-1
	for k in range (z):
		print ('#', end="")		
	print (' ', end="")
	for k in range (z):
		print ('#', end="")
	z=z+1
	print()
	



