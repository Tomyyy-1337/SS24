use std::collections::HashSet;

fn main() {
    let content_us = std::fs::read_to_string("20230512_twitter_us_trends.json")
        .unwrap()
        .lines()
        .map(|line| line.trim())
        .filter(|line| line.contains(r#""name": "#))
        .map(|line| line.split(": ").nth(1).unwrap().trim().to_string())
        .collect::<HashSet<_>>();
    
    let content_world = std::fs::read_to_string("20230512_twitter_world_trends.json")
        .unwrap()
        .lines()
        .map(|line| line.trim())
        .filter(|line| line.starts_with(r#""name": "#))
        .map(|line| line.split(": ").nth(1).unwrap().trim().to_string())
        .collect::<Vec<_>>();

    content_world.iter()
        .filter(|trend| content_us.contains(*trend))
        .for_each(|trend| println!("{}", trend));


}
