fn main() {
    let teilmengen = teilmengen_rec(4);
    println!("Teilmengen: {:?}", teilmengen);
    println!("Anzahl der Teilmengen: {}", teilmengen.len());
}

fn teilmengen(n: u8) -> Vec<Vec<u8>> { 
    (1..=n).fold(vec![vec![]], |teilmengen, x| 
        teilmengen.into_iter()
            .flat_map(|old| {
                let mut new = old.clone();
                new.push(x);
                [old, new]
            })
            .collect()
    )
}

fn teilmengen_rec(n: u8) -> Vec<Vec<u8>> {
    if n == 0 {
        return vec![vec![]];
    } 
    teilmengen_rec(n - 1)
        .into_iter()
        .flat_map(|old| {
            let mut new = old.clone();
            new.push(n);
            [old, new]
        })
        .collect()
}