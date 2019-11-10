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
/*
 let _last = list => List.nth(list, List.length(list) - 1);

 let _appendSnake = (positions, ~directions, ~size) => {
   let p = _last(positions);
   let direction = _last(directions);
   List.append(positions, [Direction.apply(p, ~direction, ~size)]);
 };
 */
/*
 let _useCells = (size, direction) => {
   let (positions, setPositions) =
     React.useState(() => [size * size / 2 + size / 2]);
   let (directions, setDirections) = React.useState(() => [direction]);
   let (runs, setRuns) = React.useState(() => 0);
   let tick = React.useCallback1(() => setRuns(r => r + 1), [||]);

   React.useEffect1(
     () => {
       if (List.length(positions) == List.length(directions)) {
         setDirections(_ => Utils.cycle([direction], directions));
       } else {
         Js.log("Oh no.");
       };
       None;
     },
     [|direction|],
   );

   let loop =
     React.useCallback3(
       () => {
         tick();
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
 */

let _toAppliedDirection = (size, directions, idx, position) =>
  Direction.apply(List.nth(directions, idx), ~forSize=size, position);
open Utils;
let useCells = (size, direction) => {
  let (positions, setPositions) = React.useState(() => [36, 46, 56]);
  let (directions, setDirections) =
    React.useState(() => [Direction.Left, Direction.Up, Direction.Up]);

  let tick =
    React.useCallback3(
      () => {
        /* set positions */
        positions
        |> List.mapi(_toAppliedDirection(size, directions))
        |> wrap
        |> setPositions;
        /* set directions */
        [direction] |> cycle(directions) |> wrap |> setDirections;
      },
      (positions, directions, size),
    );

  useInterval(tick, 1000);

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