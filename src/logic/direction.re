type t =
  | Up
  | Right
  | Down
  | Left;

let apply = (idx, size, direction) =>
  switch (direction) {
  | Up => idx - size < 0 ? size * (size - 1) + idx : idx - size
  | _ => idx
  };