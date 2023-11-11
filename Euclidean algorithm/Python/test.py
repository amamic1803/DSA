import unittest
from euclidean_algorithm import gcd


class TestEuclideanAlgorithm(unittest.TestCase):
	def test_1(self):
		self.assertEqual(gcd(9, 12), 3)

	def test_2(self):
		self.assertEqual(gcd(12, 9), 3)

	def test_3(self):
		self.assertEqual(gcd(9, 0), 9)

	def test_4(self):
		self.assertEqual(gcd(0, 9), 9)

	def test_5(self):
		self.assertEqual(gcd(0, 0), 0)

	def test_6(self):
		self.assertEqual(gcd(978, 89798763754892653453379597352537489494736), 6)

	def test_7(self):
		self.assertEqual(gcd(89798763754892653453379597352537489494736, 978), 6)

	def test_8(self):
		self.assertEqual(gcd(1221, 1234567891011121314151617181920212223242526272829), 3)

	def test_9(self):
		self.assertEqual(gcd(1234567891011121314151617181920212223242526272829, 1221), 3)


if __name__ == '__main__':
	unittest.main()
