fn main() {
    for partition in partitionen((1..=4).collect()) {
        println!("{:?}", partition);
    }
}

fn partitionen(input: Vec<u8>) -> Vec<Vec<Vec<u8>>> {
    if input.is_empty() {
        return vec![vec![]];
    }
    (0..input.len() as u8).flat_map(|i| {
        teilmengen(input.iter().cloned().skip(1).collect(), i)
            .into_iter()
            .flat_map(|subset| {
                let rest: Vec<u8> = input.iter().cloned().filter(|x| !subset.contains(x)).collect();
                partitionen(subset)
                    .into_iter()
                    .map(|mut partition| { partition.push(rest.clone()); partition })
                    .collect::<Vec<_>>()
            })
    }).collect()
} 

// Bestimmt alle n Elemenigen Teilmenge der input Menge
fn teilmengen(input: Vec<u8>, n: u8) -> Vec<Vec<u8>> {
    if n == 0 {
        return vec![vec![]];
    }  
    if input.is_empty() {
        return vec![];
    }
    let rest = input[1..].to_vec();
    teilmengen(rest.clone(), n - 1)
        .into_iter()
        .map(|mut subset| {subset.push(input[0]); subset})
        .chain(teilmengen(rest, n).into_iter())
        .collect()
}