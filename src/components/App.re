let cells =
  Array.make(100, Cell.Empty)
  |> Array.mapi((i, c) => i == 45 ? Cell.Player : c);

[@react.componenr]
let make = () =>
  <main> <h1> "Snake"->ReasonReact.string </h1> <Board cells /> </main>;