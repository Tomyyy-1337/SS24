fn main() {
    let parts = partitions(5, 3);

    for (i, part) in parts.iter().enumerate() {
        println!("{:3}: {:?}", i, part);    
    }
}

fn partitions(n: u8, m: u8) -> Vec<Vec<Vec<u8>>> {
    if m == 0 || n == 0 {
        return Vec::new();
    }
    if m == 1 {
        return vec![vec![(1..=n).collect()]];
    }

    let part1 = partitions(n-1, m).into_iter().flat_map(|p| {
        (0..m as usize)
            .map(|i| {
                let mut p = p.clone();
                p[i].push(n);
                p
            })
            .collect::<Vec<_>>()
        });

    let part2 = partitions(n - 1, m - 1)
        .into_iter()
        .map(|mut p| { p.push(vec![n]); p });

    part1.chain(part2).collect()
}
