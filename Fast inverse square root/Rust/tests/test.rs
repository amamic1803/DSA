use fast_inverse_square_root::Q_rsqrt;

#[test]
fn test_1_to_1000() {
    for n in 1..=1000 {
        let n_float = n as f32;
        assert!((Q_rsqrt(n_float) - (1.0 / n_float).sqrt()).abs() <= 0.01);
    }
}
