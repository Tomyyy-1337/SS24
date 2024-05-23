fn main() {
    let n = 3;
    let partitions = partitionen(n);
    
    for partition in partitions {
        println!("{:?}", partition);
    }
}

fn partitionen(n: u8) -> Vec<Vec<Vec<u8>>> {
    match n {
        0 => vec![vec![]],
        _ => partitionen(n - 1).iter().flat_map(|partition| 
            (0..partition.len()).map(|i| {
                let mut new_partition = partition.clone();
                new_partition[i].push(n);
                new_partition
            }).chain(std::iter::once({
                let mut new_partition = partition.clone();
                new_partition.push(vec![n]);
                new_partition
            }))).collect(),
    }
}

