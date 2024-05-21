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

    let mut result = Vec::new();
    for p in partitions(n - 1, m - 1).iter_mut() {
        p.push(vec![n]);
        result.push(p.clone());
    }
    for p in partitions(n-1, m) {
        for i in 0..p.len() {
            let mut p = p.clone();
            p[i].push(n);
            result.push(p);
        }
    }
    result
}
