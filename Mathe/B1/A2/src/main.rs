fn main() {
    for i in 1..10 {
        for j in 1..10 {
            print!("{:5} ", number_of_shortest_paths(i, j));
        }
        println!();
    }

    for i in 1..10 {
        for j in 1..10 {
            print!("{:5} ", binom_coef(i + j - 2, i - 1));
        }
        println!();
    }
}

fn number_of_shortest_paths(a: u32, b: u32) -> u32 {
    match (a, b) {
        (0, _) | (_, 0) => 0,
        (1, 1) => 1,
        _ => number_of_shortest_paths(a - 1, b) + number_of_shortest_paths(a, b - 1),
    }
}

fn binom_coef(n: u32, m: u32) -> u32 {
    if m == 0 || n == m {
        1
    } else {
        binom_coef(n - 1, m - 1) + binom_coef(n - 1, m)
    }

}