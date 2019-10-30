let useInterval = (callback, delay) => {
  let savedCallback = React.useRef(() => ());

  React.useEffect1(
    () => {
      React.Ref.setCurrent(savedCallback, callback);
      None;
    },
    [|callback|],
  );

  React.useEffect1(
    () => {
      let handler = () => React.Ref.current(savedCallback, ());
      let id = Js.Global.setInterval(handler, delay);
      Some(() => Js.Global.clearInterval(id));
    },
    [|delay|],
  );
};

let _player_is_in_space = (playerSpaces, idx) =>
  switch (List.find(i => i == idx, playerSpaces)) {
  | _ => true
  | exception Not_found => false
  };

let useCells = (size, direction) => {
  let (positions, setPositions) =
    React.useState(() => [size * size / 2 + size / 2]);

  let loop =
    React.useCallback1(
      () => setPositions(List.map(Direction.apply(~size, ~direction))),
      [|direction|],
    );

  useInterval(loop, 500);

  Array.make(size * size, Cell.Empty)
  |> Array.mapi((i, c) =>
       _player_is_in_space(positions, i) ? Cell.Player : c
     );
};

open Webapi.Dom;

let useDirection = () => {
  let (direction, setDirection) = React.useState(() => Direction.Up);
  let listener =
    React.useCallback0((e: KeyboardEvent.t) => {
      let dir =
        switch (e->KeyboardEvent.key) {
        | "ArrowUp" => Some(Direction.Up)
        | "ArrowRight" => Some(Direction.Right)
        | "ArrowDown" => Some(Direction.Down)
        | "ArrowLeft" => Some(Direction.Left)
        | _ => None
        };
      switch (dir) {
      | Some(dir) => setDirection(_ => dir)
      | None => ()
      };
    });

  React.useEffect1(
    () => {
      window |> Window.addKeyUpEventListener(listener);
      Some(() => window |> Window.removeKeyUpEventListener(listener));
    },
    [||],
  );

  direction;
};