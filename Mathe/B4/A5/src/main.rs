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