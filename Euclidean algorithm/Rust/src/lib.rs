use std::fmt::Debug;
use std::ops::Rem;

/// Find the greatest common divisor of two numbers.
///
/// Uses the Euclidean algorithm.
/// # Arguments
/// * `num1` - The first number.
/// * `num2` - The second number.
/// # Returns
/// * The greatest common divisor.
pub fn gcd<T>(mut num1: T, mut num2: T) -> T
where
    T: Copy + PartialOrd + PartialEq + Rem<Output = T> + TryFrom<u8>,
    <T as TryFrom<u8>>::Error: Debug,
{
    let zero = T::try_from(0).expect("Failed to convert 0 to type T");
    if num1 < num2 {
        (num1, num2) = (num2, num1);
    }
    while num2 != zero {
        (num1, num2) = (num2, num1 % num2);
    }
    num1
}

#[cfg(test)]
mod tests {
    use super::gcd;

    #[test]
    fn test_1() {
        assert_eq!(gcd(9, 12), 3);
    }

    #[test]
    fn test_2() {
        assert_eq!(gcd(12, 9), 3);
    }

    #[test]
    fn test_3() {
        assert_eq!(gcd(9, 0), 9);
    }

    #[test]
    fn test_4() {
        assert_eq!(gcd(0, 9), 9);
    }

    #[test]
    fn test_5() {
        assert_eq!(gcd(0, 0), 0);
    }
}
