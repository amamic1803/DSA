def binomial_coefficient(n: int, k: int) -> int:
	"""
	Binomial coefficient.
	Calculate the binomial coefficient of n and k.
	"""

	numerator = 1
	for _ in range(k):
		numerator *= n
		n -= 1
	denominator = 1
	for i in range(2, k + 1):
		denominator *= i

	return numerator // denominator

def binomial_coefficient_pascal(n: int, k: int) -> int:
	"""
	Binomial coefficient using Pascal's triangle.
	Calculate the binomial coefficient of n and k using Pascal's triangle.
	"""

	if n < 0 or not 0 <= k <= n:
		return 0
	k = min(k, n - k)

	triangle = [[0] * (min(n_loop, k) + 1) for n_loop in range(n + 1)]

	for n_loop in range(n + 1):
		triangle[n_loop][0] = 1
		for k_loop in range(1, len(triangle[n_loop])):
			if n_loop == k_loop:
				triangle[n_loop][k_loop] = 1
			else:
				triangle[n_loop][k_loop] = triangle[n_loop - 1][k_loop - 1] + triangle[n_loop - 1][k_loop]

	return triangle[n][k]

def pascal_triangle(n: int) -> list[list[int]]:
	"""
	Pascal's triangle.
	Generate Pascal's triangle with n rows.
	"""

	triangle = [[0] * i for i in range(1, n + 1)]

	for i in range(n):
		triangle[i][0] = 1
		triangle[i][-1] = 1
		for j in range(1, len(triangle[i]) - 1):
			triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j]

	return triangle


if __name__ == "__main__":
	n = int(input("Enter n: "))
	k = int(input("Enter k: "))
	print(f"Binomial coefficient of {n} and {k} is {binomial_coefficient(n, k)}.")
