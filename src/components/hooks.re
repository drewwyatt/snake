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