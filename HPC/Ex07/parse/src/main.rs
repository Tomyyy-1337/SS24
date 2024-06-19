fn main() {
    let contents = std::fs::read_to_string("taskbench_skylake.out").unwrap();
    
    extract(&contents, "PARALLEL TASK overhead");
    extract(&contents, "TASK WAIT overhead");
    extract(&contents, "TASK BARRIER overhead");
    extract(&contents, "TASKLOOP overhead");    
}
    
fn extract(contents: &str, mask: &str) {
    let indx = mask.split_ascii_whitespace().count() + 1;
    let string = contents.lines()
        .filter(|line| line.starts_with(mask))
        .map(|line| line.split_whitespace().nth(indx).unwrap().parse().unwrap())
        .map(|x: f64| format!("{:.2};", x))
        .collect::<String>();
    
    println!("{}; {}", mask, string);
}
