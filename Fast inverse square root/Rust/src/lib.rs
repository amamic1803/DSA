#[allow(non_snake_case)]
pub fn Q_rsqrt(mut number: f32) -> f32 {
    let threehalfs: f32 = 1.5;
    let x2: f32 = number * 0.5;

    let mut i: i32 = i32::from_ne_bytes(number.to_ne_bytes()); // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // what the fuck?
    number = f32::from_ne_bytes(i.to_ne_bytes());

    number = number * (threehalfs - (x2 * number * number)); // 1st iteration

    // number = number * (threehalfs - (x2 * number * number));    // 2nd iteration, this can be removed

    number
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1_to_1000() {
        for n in 1..=1000 {
            let n_float = n as f32;
            assert!((Q_rsqrt(n_float) - (1.0 / n_float).sqrt()).abs() <= 0.01);
        }
    }
}
