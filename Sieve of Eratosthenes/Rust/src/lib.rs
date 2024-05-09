/// The sieve of Eratosthenes.
/// Finds all primes less than or equal to n.
/// Uses some clever optimizations compared to the naive
/// implementation to reduce memory usage and improve performance.
/// # Arguments
/// * `n` - The number to find all primes less than or equal to.
/// # Returns
/// * `Vec<u64>` - All primes less than or equal to n.
pub fn sieve_of_eratosthenes(n: u64) -> Vec<u64> {
    match n {
        0..=1 => Vec::with_capacity(0),
        2 => vec![2],
        _ => {
            let mut results = vec![2];
            let mut sieve = vec![true; (n - 1) as usize / 2];

            let ind_to_val = |i: usize| ((i as u64) << 1) + 3; // calculate number value from index in sieve
            let val_to_ind = |v: u64| ((v - 3) >> 1) as usize; // calculate index in sieve from number value

            for prime_ind in 0..sieve.len() {
                if sieve[prime_ind] {
                    // get prime number value
                    let prime_val = ind_to_val(prime_ind);

                    // check all multiples of prime number value and mark them as not prime
                    // start checking at prime_val^2 (all smaller multiples have already been checked by smaller primes)
                    let mut check_val = prime_val * prime_val;
                    let mut check_ind = val_to_ind(check_val);
                    if check_ind >= sieve.len() {
                        break;
                    }

                    while check_ind < sieve.len() {
                        sieve[check_ind] = false;
                        // we want check_val to always be odd, prime_val is always odd so we can just add prime_val * 2
                        // (because if we added 2 odd numbers we would get an even number)
                        check_val += prime_val << 1;
                        check_ind = val_to_ind(check_val);
                    }
                }
            }

            // convert sieve indices that are true to their corresponding number values and add them to results
            results.extend(sieve.into_iter().enumerate().filter_map(|(i, prime)| {
                if prime {
                    Some(ind_to_val(i))
                } else {
                    None
                }
            }));

            // return results
            results
        }
    }
}
