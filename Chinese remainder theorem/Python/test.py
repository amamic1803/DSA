import unittest
from chinese_remainder_theorem import chinese_remainder_theorem


class TestChineseRemainderTheorem(unittest.TestCase):
	def test_1(self):
		congruences = [(2, 3), (3, 5), (2, 7)]
		self.assertEqual(chinese_remainder_theorem(congruences), 23)

	def test_2(self):
		congruences = [(1, 2), (2, 3), (3, 5)]
		self.assertEqual(chinese_remainder_theorem(congruences), 23)

	def test_3(self):
		congruences = [(1, 2), (0, 3), (0, 5), (1, 7)]
		self.assertEqual(chinese_remainder_theorem(congruences), 15)

	def test4(self):
		result = 160
		congruences = [(result % 2, 2), (result % 3, 3), (result % 5, 5), (result % 7, 7)]
		self.assertEqual(chinese_remainder_theorem(congruences), result)

	def test5(self):
		result = 1000
		congruences = [(result % 11, 11), (result % 13, 13), (result % 17, 17), (result % 19, 19)]
		self.assertEqual(chinese_remainder_theorem(congruences), result)


if __name__ == '__main__':
	unittest.main()
