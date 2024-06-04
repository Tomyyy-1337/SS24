fn main() {
    let n = 4;
    let m = 3;
    let result = partition2(n, m);
    for p in result {
        println!("{:?}", p);
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

fn partition2(n: u32, m: u32) -> Vec<Vec<u32>> {
    if m == 1 {
        return vec![vec![n]];
    }
    (0..=n-m+1).flat_map(|i| 
        partition2(n-i, m-1)
            .into_iter()
            .map(|mut p| { p.push(i); p })
            .collect::<Vec<_>>()
    ).collect()
}