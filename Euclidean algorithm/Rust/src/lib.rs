use std::ops::Rem;

/// Finds the greatest common divisor of two numbers.
/// Uses the Euclidean algorithm.
/// # Arguments
/// * `num1` - The first number.
/// * `num2` - The second number.
/// # Returns
/// * The greatest common divisor.
pub fn gcd<T>(mut num1: T, mut num2: T) -> T
where
    T: Copy + PartialOrd + PartialEq + Rem<Output = T> + TryFrom<u8>,
{
    let zero = T::try_from(0).unwrap_or_else(|_| unreachable!());
    if num1 < num2 {
        (num1, num2) = (num2, num1);
    }
    while num2 != zero {
        (num1, num2) = (num2, num1 % num2);
    }
    num1
}
