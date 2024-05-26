use std::cmp::Reverse;

/// Find the solution to a system of congruences using the Chinese Remainder Theorem.
/// For a system of congruences:
/// x ≡ a1 (mod m1)
/// x ≡ a2 (mod m2)
/// ...
/// x ≡ an (mod mn)
/// Where m1, m2, ..., mn are pairwise coprime, the solution x is unique modulo M, where M = m1 * m2 * ... * mn.
/// # Arguments
/// * `congruences` - The vector over tuples of congruences. Each tuple contains the (remainder, modulus).
/// # Returns
/// * `u64` - The solution to the system of congruences.
/// # Panics
/// If there are no congruences.
pub fn chinese_remainder_theorem(mut congruences: Vec<(u64, u64)>) -> u64 {
    // sort by modulus in descending order
    congruences.sort_by_key(|&(_, modulus)| Reverse(modulus));

    // check if moduli are pairwise coprime
    for i in 0..congruences.len() {
        for j in i + 1..congruences.len() {
            if gcd(congruences[i].1, congruences[j].1) != 1 {
                panic!("The moduli are not pairwise coprime.");
            }
        }
    }

    match congruences.len() {
        0 => panic!("There must be at least 1 congruence."),
        1 => congruences[0].0,
        _ => {
            let (mut solution, mut modulus) = congruences[0];

            for congruence in congruences.into_iter().skip(1) {
                while solution % congruence.1 != congruence.0 {
                    solution += modulus;
                }
                modulus *= congruence.1;
            }

            solution
        }
    }
}

/// Calculate the greatest common divisor of two numbers using the Euclidean algorithm.
fn gcd(mut num1: u64, mut num2: u64) -> u64 {
    if num1 < num2 {
        (num1, num2) = (num2, num1);
    }
    while num2 != 0 {
        (num1, num2) = (num2, num1 % num2);
    }
    num1
}
