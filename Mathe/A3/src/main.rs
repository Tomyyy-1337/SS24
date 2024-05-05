use itertools::Itertools;

fn main() {
    println!("Hello, world!");

    for i in 1..10 {
        let count = (1..=i)
            .permutations(i)
            .unique()
            .filter(|v| v.iter().enumerate().all(|(i, &x)| x != i + 1));
        println!("{}: {}", i, count.count());
    }

    let mut count = 0;
    for n in 2..=10 {
        count = n * count + (-1i32).pow(n as u32); 
        println!("{}: {}", n, count);
    }
}
