use collatz_conjecture::collatz_conjecture;

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
