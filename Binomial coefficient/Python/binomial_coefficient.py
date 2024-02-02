def binomial_coefficient(n: int, k: int) -> int:
	"""
	Binomial coefficient.
	Calculate the binomial coefficient of n and k.
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


if __name__ == "__main__":
	n = int(input("Enter n: "))
	k = int(input("Enter k: "))
	print(f"Binomial coefficient of {n} and {k} is {binomial_coefficient(n, k)}.")
