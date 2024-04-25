use rayon::iter::{IntoParallelIterator, ParallelIterator};

fn main() {
    let teiler: Vec<u64> = vec![3,5,7,11];
    for n in (1..=10).map(|i| 10u64.pow(i)) {
        println!(
            "{:11} Zahlen zwischen 1 und {n:11} sind durch mindestens einen der Teiler {} teilbar.", 
            count_numbers(n, &teiler), 
            teiler.iter().map(|&t| t.to_string()).collect::<Vec<String>>().join(", ")
        );
    }
}

fn count_numbers(n: u64, teiler: &Vec<u64>) -> usize {
    (1..=n).into_par_iter()
        .filter(|&n| teiler.iter().any(|&t| n % t == 0))
        .count()
}   