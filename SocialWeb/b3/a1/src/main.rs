use std::collections::HashSet;

use serde::Deserialize;


fn main() {
    println!("========= Task 1 =========");

    let raw_us = std::fs::read_to_string("data/20230512_twitter_us_trends.json").unwrap();
    let raw_world = std::fs::read_to_string("data/20230512_twitter_world_trends.json").unwrap();

    let data_us = &serde_json::from_str::<Vec<Trends>>(&raw_us).unwrap()[0];
    let data_world = &serde_json::from_str::<Vec<Trends>>(&raw_world).unwrap()[0];

    println!("US Trends: \n{}", to_string(data_us.trends.iter().collect()));
    println!("Global Trends: \n{}", to_string(data_world.trends.iter().collect()));
    

    println!("========= Task 2 =========");

    let world_set = data_world.trends.iter().map(|trend| trend.name.clone()).collect::<HashSet<String>>();
    let common = data_us.trends.iter().filter(|trend| world_set.contains(&trend.name)).collect::<Vec<_>>();
    println!("Common Trends: \n{}", to_string(common));

    let us_without_world = data_us.trends.iter().filter(|trend| !world_set.contains(&trend.name)).collect::<Vec<_>>();
    println!("US Trends without World Trends: \n{}", to_string(us_without_world));

}

fn to_string(data: Vec<&Trend>) -> String {
    data.iter().map(|trend| trend.name.clone()).collect::<Vec<String>>().join(", ")
}

#[derive(Deserialize)]
struct Trends {
    trends: Vec<Trend>,
}

#[derive(Deserialize)]
struct Trend {
    name: String,
    // url: String,
    // query: String,
    // tweet_volume: Option<u64>,
}
