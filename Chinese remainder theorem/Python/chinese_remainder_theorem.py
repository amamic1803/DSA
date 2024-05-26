import math


def chinese_remainder_theorem(congruences: list[tuple[int, int]]) -> int:
	"""
	Find the solution to a system of congruences using the Chinese Remainder Theorem.
	For a system of congruences:
    x ≡ a1 (mod m1)
    x ≡ a2 (mod m2)
    ...
    x ≡ an (mod mn)
    Where m1, m2, ..., mn are pairwise coprime, the solution x is unique modulo M, where M = m1 * m2 * ... * mn.

    :return:
    :param List[Tuple[int, int]] congruences: The congruences as a list of tuples. Each tuple contains the (remainder, modulus).
    :return: The solution to the system of congruences.
	"""

	# sort by modulus in descending order
	congruences.sort(key=lambda x: x[1], reverse=True)

	# check if the moduli are pairwise coprime
	for i in range(len(congruences)):
		for j in range(i + 1, len(congruences)):
			if math.gcd(congruences[i][1], congruences[j][1]) != 1:
				raise ValueError("The moduli are not pairwise coprime.")

	# find the solution
	match len(congruences):
		case 0:
			raise ValueError("There must be at least 1 congruence.")
		case 1:
			return congruences[0][0]
		case _:  # more than 1 congruence
			solution, modulus = congruences[0]
			for congruence in congruences[1:]:
				while solution % congruence[1] != congruence[0]:
					solution += modulus
				modulus *= congruence[1]
			return solution


if __name__ == "__main__":
	congruences = list()
	while True:
		remainder = int(input("Enter remainder: "))
		modulus = int(input("Enter modulus: "))
		congruences.append((remainder, modulus))
		if input("Do you want to add more congruences? (y/n): ").lower() != "y":
			break
	print(f"The solution to the system of congruences is {chinese_remainder_theorem(congruences)}.")
