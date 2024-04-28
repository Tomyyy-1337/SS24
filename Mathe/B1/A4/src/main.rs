fn main() {
    for i in 1..=20 {
        let teilmengen = teilmengen_rec(i);
        println!("Anzahl der Teilmengen von {{1,..,{}}}: {}", i, teilmengen.len());
        if i <= 4 {
            println!("Teilmengen von {{1,..,{}}}: {:?}", i, teilmengen);
        }
    }  
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