hours = float(input("Enter Hours:"))
rate = float(input("Enter Rate:"))
res = hours * rate
if hours > 40:
    res += (hours - 40) * rate * 0.5
print(res)
