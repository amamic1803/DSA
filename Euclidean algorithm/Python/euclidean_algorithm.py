def gcd(a: int, b: int) -> int:
	"""
	Euclidean algorithm.
	Calculate the greatest common divisor of two numbers.
	"""

	if b > a:
		a, b = b, a

	while b != 0:
		a, b = b, a % b

	return a


if __name__ == "__main__":
	x = int(input("Enter the first number: "))
	y = int(input("Enter the second number: "))
	print(f"The greatest common divisor of {x} and {y} is {gcd(x, y)}.")
