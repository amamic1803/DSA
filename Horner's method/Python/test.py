import unittest
from horners_method import horners_method


class TestHornersMethod(unittest.TestCase):
	def test_1(self):
		result = horners_method([2, 1, 0, 0, -2, -1], 2)
		self.assertEqual(result, 75)

	def test_2(self):
		# horner's method can be used to convert a number from any base to decimal
		# for example, convert 1011 from base 2 to decimal
		# 1 * 2^3 + 0 * 2^2 + 1 * 2^1 + 1 * 2^0
		# 8 + 0 + 2 + 1
		# 11
		result = horners_method([1, 0, 1, 1], 2)
		self.assertEqual(result, 11)

	def test_3(self):
		# convert af6b7c from base 16 to decimal
		# 10 * 16^5 + 15 * 16^4 + 6 * 16^3 + 11 * 16^2 + 7 * 16^1 + 12 * 16^0
		# 10485760 + 983040 + 24576 + 2816 + 112 + 12
		# 11496316
		result = horners_method([10, 15, 6, 11, 7, 12], 16)
		self.assertEqual(result, 11496316)


if __name__ == '__main__':
	unittest.main()
