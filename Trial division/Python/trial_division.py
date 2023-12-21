def trial_division(n: int) -> list[int]:
	"""Return a list of the prime factors for a natural number."""

	factors = []
	while n % 2 == 0:
		factors.append(2)
		n //= 2

	f = 3
	while f * f <= n and n > 1:
		if n % f == 0:
			factors.append(f)
			n //= f
		else:
			f += 2

	if n != 1:
		factors.append(n)

	return factors


if __name__ == "__main__":
	integer = int(input("Enter an integer: "))
	print(f"Prime factors of {integer}: {", ".join(map(str, trial_division(integer)))}")
