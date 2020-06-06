largest = None
smallest = None
while True:
    try:
        num = input("Enter a number: ")
        if num == "done" : break
        num = int(num)
    except:
        print("Invalid input")
        continue
    largest = max(largest, num)
    smallest = num if smallest is None else min(smallest, num)

print("Maximum is", largest)
print("Minimum is", smallest)
