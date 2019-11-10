type t =
  | Up
  | Right
  | Down
  | Left;

let apply = (direction, ~forSize, idx) => {
  let size = forSize;
  switch (direction) {
  | Up => idx - size < 0 ? size * (size - 1) + idx : idx - size
  | Right => (idx + 1) mod size == 0 ? idx - (size - 1) : idx + 1
  | Down => idx + size >= size * size ? idx mod size : idx + size
  | Left => idx mod size == 0 ? idx + (size - 1) : idx - 1
  };
};