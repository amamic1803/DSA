def lev(a: str, b: str) -> int:
    """
    Calculate the Levenshtein distance between two strings.

    :param a: First string
    :param b: Second string
    :return: The Levenshtein distance
    """

    prev_row = [x for x in range(0, len(b) + 1)]
    curr_row = [0] * len(prev_row)

    for i in range(1, len(a) + 1):
        curr_row[0] = i
        for j in range(1, len(curr_row)):
            if a[i - 1] == b[j - 1]:
                curr_row[j] = prev_row[j - 1]
            else:
                curr_row[j] = 1 + min(prev_row[j], curr_row[j - 1], prev_row[j - 1])
        prev_row, curr_row = curr_row, prev_row

    return prev_row[-1]


if __name__ == "__main__":
    # Example usage
    str1 = "kitten"
    str2 = "sitting"
    distance = lev(str1, str2)
    print(f"The Levenshtein distance between '{str1}' and '{str2}' is {distance}.")
