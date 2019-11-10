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
  let (positions, setPositions) =
    React.useState(() =>
      [(36, Direction.Up), (46, Direction.Up), (56, Direction.Up)]
    );

  let tick =
    React.useCallback3(
      () => setPositions(List.map(_toAppliedDirection(size, direction))),
      (positions, direction, size),
    );

  useInterval(tick, 1000);

  Array.make(size * size, Cell.Empty)
  |> Array.mapi((i, c) =>
       List.exists(((p, _)) => p == i, positions) ? Cell.Player : c
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