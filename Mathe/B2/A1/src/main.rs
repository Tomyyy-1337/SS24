use itertools::Itertools;

fn main() {
    let input = vec!{10,10,10,10,20,20,20};

    let result = input.iter()
        .permutations(input.len())
        .unique()
        .filter(|x| !x.into_iter()
            .scan(0, |acc, &e| {
                *acc += if *e == 10 {1} else {-1};
                Some(*acc)
            })
            .any(|x| x < 0)
        )
        .collect::<Vec<_>>();

    println!("{:?} \n len: {}", result, result.len());
}
