carray = [""]
carrayindex = 0

message = input("Input message:\n")
message = message.split(" ")

for word in message:
    if len(carray[carrayindex]+word) < 21:
        carray[carrayindex] += word
        if len(carray[carrayindex]+" ") < 21:
            carray[carrayindex] += " "
    else:
        carray.append("")
        carrayindex += 1
        carray[carrayindex] += word
        if len(carray[carrayindex]+" ") < 21:
            carray[carrayindex] += " "

buffer = ""
for i in carray:
    buffer += f"\t\"{i}\",\n"

print(buffer)
print(len(carray))
