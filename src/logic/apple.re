type t = int;

let _includes = random => List.exists(i => i == random);

let rec _findAvailable = (blacklist, max, check) =>
  if (blacklist |> _includes(check)) {
    let inc = check + 1;
    _findAvailable(blacklist, max, inc == max ? 0 : inc);
  } else {
    check;
  };

let make = (size, snake) => {
  let blacklist = Snake.positions(snake);
  let max = size * size;
  _findAvailable(blacklist, max, Random.int(max));
};