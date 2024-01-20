import unittest
from trial_division import trial_division, is_prime


class TestTrialDivision(unittest.TestCase):
	def test_1(self):
		result = trial_division(68141354861)
		self.assertEqual(result, [68141354861])  # 68141354861 is prime

	def test_2(self):
		result = trial_division(68141354862)
		self.assertEqual(result, [2, 3, 7, 19, 59, 1447291])

	def test_3(self):
		result = trial_division(2 ** 128)
		self.assertEqual(result, [2 for _ in range(128)])

	def test_4(self):
		result = trial_division(23584860)
		self.assertEqual(result, [2, 2, 3, 3, 5, 13, 10079])

	def test_5(self):
		result = trial_division(39798123)
		self.assertEqual(result, [3, 13266041])

	def test_6(self):
		for i in range(1, 10_001):
			factors = trial_division(i)
			primality = is_prime(i)
			self.assertEqual(len(factors) == 1, primality)


if __name__ == '__main__':
	unittest.main()
