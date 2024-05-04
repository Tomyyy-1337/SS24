fn main() {
    let mut all_paths = vec![];
    get_paths_a(3, 2, &mut vec![], &mut all_paths);

    let mut upper_paths = vec![];
    get_paths_b(3, 2, 0, &mut vec![], &mut upper_paths);

    println!("All paths: {:?}", all_paths);
    println!("Upper paths: {:?}", upper_paths);
}

fn get_paths_a(n: u8, m: u8, path: &mut Vec<u8>, paths: &mut Vec<Vec<u8>>) {
    if n == 0 && m == 0 {
        paths.push(path.clone());
    } else {
        if n > 0 {
            path.push(0);
            get_paths_a(n - 1, m, path, paths);
            path.pop();
        }
        if m > 0 {
            path.push(1);
            get_paths_a(n, m - 1, path, paths);
            path.pop();
        }
    }
}

fn get_paths_b(n: u8, m: u8, c: u8, path: &mut Vec<u8>, paths: &mut Vec<Vec<u8>>) {
    if n == 0 && m == 0 {
        paths.push(path.clone());
    } else {
        if n > 0 {
            path.push(0);
            get_paths_b(n - 1, m, c + 1 , path, paths);
            path.pop();
        }
        if m > 0 && c > 0 {
            path.push(1);
            get_paths_b(n, m - 1, c - 1, path, paths);
            path.pop();
        }
    }
}