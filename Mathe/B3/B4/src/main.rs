fn main() {
    for i in 0..=16 {
        println!("{}: {}", i, count_partitions(i));
    }
}

fn count_partitions(n: u64) -> u64 {
    if n == 0 {
        return 1;
    }
    (0..n).map(|k| binom_koeff(n - 1, k) * count_partitions(k)).sum()
}

fn binom_koeff(n: u64, k: u64) -> u64 {
    if k == 0 || k == n {
        return 1;
    }
    binom_koeff(n - 1, k - 1) + binom_koeff(n - 1, k)
}