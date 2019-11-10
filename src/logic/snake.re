type t = list((int, Direction.t));
let positions = snake => snake |> List.map(fst);