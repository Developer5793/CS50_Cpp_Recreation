print("Enter a Creditcardnumber please: ")
Creditcardnumber=input()



#Store number in array and revers its order to modify it
arr = [int(x) for x in str(Creditcardnumber)]
res = arr[::-1] #reversing using list slicing

length =len(res)
print(length)

#Extract every second number
multiplier = res[1:length:2] 
normalnumbers = res[0:length:2]
print(multiplier)
print(normalnumbers)


#multiply every second number by two
myinput=[]
for x in multiplier:
    x=x*2
    myinput.append(x)
print(myinput)




#Convert numbers to string 
string =""
for y in myinput:
    string += str(y)
print(string)

string2 =""
for z in normalnumbers:
    string2 +=str(z)
print(string2)



#Convert string to number array and add numbers
y=0
arrforaddition = [int(x) for x in str(string)]
print(arrforaddition)
for x in arrforaddition:
    y +=x
print(y)

k=0
normalarrforaddition = [int(x) for x in str(string2)]
print(normalarrforaddition)
for x in normalarrforaddition:
  k +=x
print(k)

checksum=y+k

print(checksum)

fraudulent=checksum%10
print(fraudulent)




if length == 15 and arr[0]==3 and arr[1]==4 and fraudulent==0 or length == 15 and arr[0]==3 and arr[1]==7 and fraudulent==0:
    print("American Express")
    exit



elif length == 16 and arr[0]==5 and arr[1]==1 and fraudulent==0 or length == 16 and arr[0]==5 and arr[1]==2 and fraudulent==0 or length == 16 and arr[0]==5 and arr[1]==3 and fraudulent==0 or length == 16 and arr[0]==5 and arr[1]==4 and fraudulent==0 or length == 16 and arr[0]==5 and arr[1]==5 and fraudulent==0:

    print("Master Card")
    exit


elif length == 13 and arr[0]==4 and fraudulent==0 or length == 16 and arr[0]==4 and fraudulent==0:

     print("VISA")
     exit


else:
    print("Invalid")


