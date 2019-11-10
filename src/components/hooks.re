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

let _toAppliedDirection = (size, direction) => {
  let prevDirection = ref(direction);
  ((p, d)) => {
    let shifted = (Direction.apply(prevDirection^, size, p), prevDirection^);
    prevDirection := d;
    shifted;
  };
};

let useCells = (size, direction) => {
  let (player, setPlayer) =
    React.useState(() =>
      [(36, Direction.Up), (46, Direction.Up), (56, Direction.Up)]
    );

  let tick =
    React.useCallback3(
      () => setPlayer(List.map(_toAppliedDirection(size, direction))),
      (player, direction, size),
    );

  useInterval(tick, 1000);

  Array.make(size * size, Cell.Empty)
  |> Array.mapi((i, c) =>
       List.exists(((p, _)) => p == i, player) ? Cell.Player : c
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