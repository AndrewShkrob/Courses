def computepay(hours, rate):
    res = hours * rate
    if hours > 40:
        res += (hours - 40) * rate * 0.5
    return res

hours = float(input("Enter Hours:"))
rate = float(input("Enter Rate:"))
pay = computepay(hours, rate)
print("Pay", pay)
