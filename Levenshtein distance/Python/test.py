import unittest
from levenshtein_distance import lev


class TestLevenshteinDistance(unittest.TestCase):
    def test_empty_strings(self):
        self.assertEqual(lev("", ""), 0)

    def test_one_empty_string(self):
        self.assertEqual(lev("abc", ""), 3)
        self.assertEqual(lev("", "abc"), 3)

    def test_identical_strings(self):
        self.assertEqual(lev("test", "test"), 0)
        self.assertEqual(lev("a", "a"), 0)
        self.assertEqual(lev("abc", "abc"), 0)
        self.assertEqual(lev("longerstring", "longerstring"), 0)

    def test_single_character_difference(self):
        self.assertEqual(lev("test", "tent"), 1)
        self.assertEqual(lev("a", "b"), 1)
        self.assertEqual(lev("ab", "ac"), 1)
        self.assertEqual(lev("abc", "ab"), 1)
        self.assertEqual(lev("ab", "abc"), 1)

    def test_multiple_character_differences(self):
        self.assertEqual(lev("kitten", "sitting"), 3)

    def test_insertions(self):
        self.assertEqual(lev("abc", "abxc"), 1)
        self.assertEqual(lev("abc", "xabc"), 1)
        self.assertEqual(lev("abc", "abcx"), 1)

    def test_deletions(self):
        self.assertEqual(lev("abcd", "abd"), 1)
        self.assertEqual(lev("abcd", "bcd"), 1)
        self.assertEqual(lev("abcd", "acd"), 1)

    def test_substitutions(self):
        self.assertEqual(lev("kitten", "sitten"), 1)
        self.assertEqual(lev("kitten", "sittin"), 2)
        self.assertEqual(lev("flaw", "lawn"), 2)

    def test_unicode(self):
        self.assertEqual(lev("café", "cafe"), 1)
        self.assertEqual(lev("programčić", "profić"), 5)
        self.assertEqual(lev("你好", "您好"), 1)

    def test_longer_strings(self):
        s1 = "the quick brown fox jumps over the lazy dog"
        s2 = "the quick brown fox jumped over the lazy dogs"
        self.assertEqual(lev(s1, s2), 3)

        self.assertEqual(lev("intention", "execution"), 5)

        s3 = "a" * 1000
        s4 = "a" * 999 + "b"
        self.assertEqual(lev(s3, s4), 1)

    def test_case_sensitivity(self):
        self.assertEqual(lev("abc", "ABC"), 3)
        self.assertEqual(lev("Test", "test"), 1)

    def test_completely_different(self):
        self.assertEqual(lev("abc", "xyz"), 3)
        self.assertEqual(lev("12345", "abcde"), 5)


if __name__ == '__main__':
    unittest.main()
