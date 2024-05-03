use itertools::Itertools;

fn main() {
    let input = vec!{0,1,2,3};

    let result = input.iter()
        .permutations(input.len())
        .unique()
        .filter(|x| !x.into_iter()
            .enumerate()
            .any(|(i, &e)| *e == i)
        )
        .collect::<Vec<_>>();

    println!("{:?} \n len: {}", result, result.len());
}
