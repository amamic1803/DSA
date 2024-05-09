use sieve_of_eratosthenes::sieve_of_eratosthenes;

#[test]
fn primes_100() {
    assert_eq!(sieve_of_eratosthenes(100).len(), 25);
}

#[test]
fn primes_1000() {
    assert_eq!(sieve_of_eratosthenes(1000).len(), 168);
}

#[test]
fn primes_10000() {
    assert_eq!(sieve_of_eratosthenes(10_000).len(), 1229);
}

#[test]
fn primes_100000() {
    assert_eq!(sieve_of_eratosthenes(100_000).len(), 9592);
}

#[test]
fn primes_1000000() {
    assert_eq!(sieve_of_eratosthenes(1_000_000).len(), 78498);
}

#[test]
fn primes_10000000() {
    assert_eq!(sieve_of_eratosthenes(10_000_000).len(), 664579);
}

#[test]
fn primes_100000000() {
    assert_eq!(sieve_of_eratosthenes(100_000_000).len(), 5761455);
}
