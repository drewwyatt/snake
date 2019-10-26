let useInterval = (callback, delay) => {
  let savedCallback = React.useRef(None);

  React.useEffect1(
    () => {
      React.Ref.setCurrent(savedCallback, Some(callback));
      None;
    },
    [|callback|],
  );

  React.useEffect1(
    () => {
      let handler =
        switch (React.Ref.current(savedCallback)) {
        | Some(cb) => cb
        | None => (() => ())
        };

      let id = Js.Global.setInterval(handler, delay);
      Some(() => Js.Global.clearInterval(id));
    },
    [|delay|],
  );
};

let useCells = size => {
  let (position, setPosition) =
    React.useState(() => size * size / 2 + size / 2);
  let prevPlayerDirection = React.useRef(Direction.Up);

  let loop =
    React.useCallback1(
      () => {
        let direction = React.Ref.current(prevPlayerDirection);
        Js.log("direction: " ++ Js.String.make(direction));
        Js.log("position: " ++ string_of_int(position));
        setPosition(p => Direction.apply(p, size, direction));
      },
      [|React.Ref.current(prevPlayerDirection)|],
    );

  useInterval(loop, 1000);

  Array.make(size * size, Cell.Empty)
  |> Array.mapi((i, c) => i == position ? Cell.Player : c);
};