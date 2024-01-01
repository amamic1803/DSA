/// Calculates the number of steps and the maximum number reached for the Collatz conjecture with starting number `n`.
/// # Arguments
/// * `n` - The starting number for the Collatz conjecture.
/// # Returns
/// A tuple containing the number of steps and the maximum number reached.
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
