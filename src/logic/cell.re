type t =
  | Empty
  | Player
  | Apple;

module Set = {
  type t_ = (t, list(int));

  let make = (state, indexes) => (state, indexes);

  let ofApple = idx => make(Apple, [idx]);
  let ofSnake = snake => snake |> List.map(fst) |> make(Player);

  let map = (sets: list(t_), idx, fallback) => {
    let optionals =
      List.map(
        ((state, indexes)) =>
          if (indexes |> List.exists(i => i == idx)) {
            Some(state);
          } else {
            None;
          },
        sets,
      );

    switch (List.find(Js.Option.isSome, optionals)) {
    | Some(s) => s
    | exception Not_found => fallback
    };
  };
};