fn main() {
    let contents = std::fs::read_to_string("epyc_2b.out").unwrap();

    contents.lines().skip(3).for_each( |line| {
        if let Some(val) = line.split_ascii_whitespace()
            .skip(2)
            .next() {
                println!("{}", val.replace(".", ","));
        }
    });


}
