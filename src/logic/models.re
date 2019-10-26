type direction =
  | Up
  | Right
  | Down
  | Left;

type move = (int, direction);

type cell =
  | Empty
  | Player
  | Apple;