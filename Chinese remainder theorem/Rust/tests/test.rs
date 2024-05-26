use chinese_remainder_theorem::chinese_remainder_theorem;

#[test]
fn test_1() {
    let congruences = vec![(2, 3), (3, 5), (2, 7)];
    assert_eq!(chinese_remainder_theorem(congruences), 23);
}

#[test]
fn test_2() {
    let congruences = vec![(1, 2), (2, 3), (3, 5)];
    assert_eq!(chinese_remainder_theorem(congruences), 23);
}

#[test]
fn test_3() {
    let congruences = vec![(1, 2), (0, 3), (0, 5), (1, 7)];
    assert_eq!(chinese_remainder_theorem(congruences), 15);
}

#[test]
fn test_4() {
    let result = 160;
    let congruences = vec![
        (result % 2, 2),
        (result % 3, 3),
        (result % 5, 5),
        (result % 7, 7),
    ];
    assert_eq!(chinese_remainder_theorem(congruences), result);
}

#[test]
fn test_5() {
    let result = 1000;
    let congruences = vec![
        (result % 11, 11),
        (result % 13, 13),
        (result % 17, 17),
        (result % 19, 19),
    ];
    assert_eq!(chinese_remainder_theorem(congruences), result);
}
