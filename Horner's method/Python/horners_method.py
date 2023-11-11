def horners_method(coefs: list[int | float], x: int | float) -> int | float:
	"""Horner's method for polynomial evaluation."""

	rezultat: int | float = 0
	for i in range(len(coefs)):
		if i == 0:
			rezultat = coefs[i]
		else:
			rezultat = x * rezultat + coefs[i]
	return rezultat


if __name__ == "__main__":
	coefficients = list(map(int, input("Coefficients (space separated): ").split()))
	x = int(input("X: "))
	print(f"Result: {horners_method(coefficients, x)}")

	# EXAMPLE:
	# Expression: 2 * x^5 + x^4 - 2 * x - 1
	# Coefficients: 2 1 0 0 -2 -1
	# x: 2
	# Result: 75
