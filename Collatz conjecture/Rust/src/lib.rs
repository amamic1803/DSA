/// Calculate the number of steps and the maximum number
/// reached for the Collatz conjecture with starting number `n`.
/// # Arguments
/// * `n` - The starting number for the Collatz conjecture.
/// # Returns
/// * A tuple containing the number of steps and the maximum number reached.
pub fn collatz_conjecture(mut n: u64) -> (u64, u64) {
    let mut steps = 0;
    let mut max = n;
    while n != 1 {
        if n % 2 == 0 {
            n /= 2;
        } else {
            n = 3 * n + 1;
        };
        steps += 1;
        if n > max {
            max = n;
        }
    }
    (steps, max)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn max_up_to(n: u64) -> (u64, u64, u64) {
        let mut num = 0;
        let mut high_val = 0;
        let mut max_steps = 0;
        for i in 1..=n {
            let (steps, max_reached) = collatz_conjecture(i);
            if steps > max_steps {
                max_steps = steps;
                high_val = max_reached;
                num = i;
            }
        }
        (max_steps, num, high_val)
    }

    #[test]
    fn max_1000() {
        assert_eq!(max_up_to(1000), (178, 871, 190_996));
    }

    #[test]
    fn max_10000() {
        assert_eq!(max_up_to(10_000), (261, 6_171, 975_400));
    }

    #[test]
    fn max_100000() {
        assert_eq!(max_up_to(100_000), (350, 77_031, 21_933_016));
    }

    #[test]
    fn max_1000000() {
        assert_eq!(max_up_to(1_000_000), (524, 837_799, 2_974_984_576));
    }

    #[test]
    fn max_10000000() {
        assert_eq!(max_up_to(10_000_000), (685, 8_400_511, 159_424_614_880));
    }
}
