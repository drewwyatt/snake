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

let rec _prependHead = (prepended, rest) =>
  switch (rest) {
  | [head, ...tail] when List.length(rest) > 1 =>
    _prependHead(List.append(prepended, [head]), tail)
  | _ => prepended
  };

let _last = list => List.nth(list, List.length(list) - 1);

let _appendSnake = (positions, ~directions, ~size) => {
  let p = _last(positions);
  let direction = _last(directions);
  List.append(positions, [Direction.apply(p, ~direction, ~size)]);
};

let useCells = (size, direction) => {
  let (positions, setPositions) =
    React.useState(() => [size * size / 2 + size / 2]);
  let (directions, setDirections) = React.useState(() => [direction]);
  let (runs, setRuns) = React.useState(() => 0);
  let tick = React.useCallback1(() => setRuns(r => r + 1), [||]);

  React.useEffect1(
    () => {
      if (List.length(positions) == List.length(directions)) {
        setDirections(_ => _prependHead([direction], directions));
      } else {
        Js.log("Oh no.");
      };
      None;
    },
    [|direction|],
  );

  React.useEffect1(
    () => {
      if (List.length(positions) > List.length(directions)) {
        setDirections(_ => List.concat([[direction], directions]));
      };
      None;
    },
    [|List.length(positions)|],
  );

  let loop =
    React.useCallback3(
      () => {
        tick();
        let positions =
          runs mod 3 == 0 ?
            _appendSnake(positions, ~directions, ~size) : positions;

        let pos =
          directions
          |> List.mapi((i, direction) =>
               Direction.apply(List.nth(positions, i), ~size, ~direction)
             );
        setPositions(_ => pos);
      },
      (directions, positions, runs),
    );

  useInterval(loop, 500);

  Array.make(size * size, Cell.Empty)
  |> Array.mapi((i, c) =>
       List.exists(p => p == i, positions) ? Cell.Player : c
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