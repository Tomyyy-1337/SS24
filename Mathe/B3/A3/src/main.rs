fn main() {
    for i in 1..=10 {
        for j in 2..=i {
            println!("{} choose {} = {}", i, j, binom_coeff(i as u64 - 1, j as u64 - 1));
            println!("Partitions of {} into {} parts: {}", i, j, (0..=i-j).map(|k| binom_coeff(j as u64 + k as u64 - 2, j as u64 - 2)).sum::<u64>());
        }
    }
}

fn partition(n: u32, m: u32) -> Vec<Vec<u32>> {
    if m == 1 {
        return vec![vec![n]];
    }
    (1..=n-m+1).flat_map(|i| 
        partition(n-i, m-1)
            .into_iter()
            .map(|mut p| { p.push(i); p })
            .collect::<Vec<_>>()
    ).collect()
}

fn binom_coeff(n: u64, k: u64) -> u64 {
    if k == 0 || k == n {
        return 1;
    }
    binom_coeff(n - 1, k - 1) + binom_coeff(n - 1, k)
}