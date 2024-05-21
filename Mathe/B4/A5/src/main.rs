<<<<<<< HEAD
use std::vec;

fn main() {
    let input = 4;
    let m = 2;
    let result = partitions(input, m);
    for r in result.iter() {
        println!("{:?}", r);
    }


}
fn partitions(n: usize, m: usize) -> Vec<Vec<Vec<usize>>> {
    if m == 0 {
        return vec![];
    }
    if m == 1 {
        return vec![vec![(1..=n).collect::<Vec<_>>()]];
    }
    if n == 0 {
        return vec![];
    }
    let mut result = vec![];

    let mut parts = partitions(n - 1, m - 1);
    for p in parts.iter_mut() {
        p.push(vec![n]);
        result.push(p.clone());
    }

    let mut parts = partitions(n - 1, m);
    for p in parts.iter_mut() {
        for i in 0..m {
            let mut q = p.clone();
            q[i].push(n);
            result.push(q);
        }
    }

    result
}   
=======
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
>>>>>>> 65b051abf57e2a569e9f5a45ea0e8f76c37bb0f9
