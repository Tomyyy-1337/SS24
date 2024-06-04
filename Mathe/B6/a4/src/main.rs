fn main() {
    let result = multimenge(&vec![1,2,3], 3);

    for i in result {
        println!("{:?}", i);
    }
}

fn multimenge(input: &Vec<u8>, n: u8) -> Vec<Vec<u8>> {
    if n == 0 {
        return vec![vec![]];
    }
    if n == 1 {
        return input.iter().map(|&x| vec![x]).collect();
    }
    multimenge(input, n - 1).iter().flat_map(|x| 
        input.iter()
            .filter(|&y| x[x.len() - 1] <= *y)
            .map(|y: &u8| {
                let mut z = x.clone();
                z.push(*y);
                z
            })
    ).collect()
}
