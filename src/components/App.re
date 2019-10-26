let cells =
  Array.make(100, Models.Empty)
  |> Array.mapi((i, c) => i == 45 ? Models.Player : c);

[@react.componenr]
let make = () =>
  <main> <h1> "Snake"->ReasonReact.string </h1> <Board cells /> </main>;