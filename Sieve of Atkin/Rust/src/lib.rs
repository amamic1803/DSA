pub fn sieve_of_atkin(limit: usize) -> Vec<usize> {
    let mut sieve = vec![false; limit + 1];

    if limit >= 2 {
        sieve[2] = true;
    }
    if limit >= 3 {
        sieve[3] = true;
    }

    let mut n;
    let root = (limit as f64).sqrt().floor() as usize;
    for x in 1..=root {
        for y in 1..=root {
            n = 4 * x * x + y * y;
            if n <= limit && [1, 5].contains(&(n % 12)) {
                sieve[n] ^= true;
            }

            n = 3 * x * x + y * y;
            if n <= limit && n % 12 == 7 {
                sieve[n] ^= true;
            }

            n = (3 * x * x).saturating_sub(y * y); // avoid underflow (0 % 12 != 11)
            if x > y && n <= limit && n % 12 == 11 {
                sieve[n] ^= true;
            }
        }
    }

    for r in 5..=root {
        if sieve[r] {
            n = r * r;
            for i in (n..=limit).step_by(n) {
                sieve[i] = false;
            }
        }
    }

    sieve
        .into_iter()
        .enumerate()
        .filter(|&(_, is_prime)| is_prime)
        .map(|(i, _)| i)
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn primes_100() {
        assert_eq!(sieve_of_atkin(100).len(), 25);
    }

    #[test]
    fn primes_1000() {
        assert_eq!(sieve_of_atkin(1000).len(), 168);
    }

    #[test]
    fn primes_10000() {
        assert_eq!(sieve_of_atkin(10_000).len(), 1229);
    }

    #[test]
    fn primes_100000() {
        assert_eq!(sieve_of_atkin(100_000).len(), 9592);
    }

    #[test]
    fn primes_1000000() {
        assert_eq!(sieve_of_atkin(1_000_000).len(), 78498);
    }

    #[test]
    fn primes_10000000() {
        assert_eq!(sieve_of_atkin(10_000_000).len(), 664579);
    }

    #[test]
    fn primes_100000000() {
        assert_eq!(sieve_of_atkin(100_000_000).len(), 5761455);
    }
}
