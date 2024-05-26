use euclidean_algorithm::gcd;

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
