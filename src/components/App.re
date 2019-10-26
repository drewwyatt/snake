let cells =
  Array.make(100, Cell.Empty)
  |> Array.mapi((i, c) => i == 45 ? Cell.Player : c);

[@react.component]
let make = () => {
  Hooks.useInterval(() => "hey"->Js.log, 1000);
  <main> <h1> "Snake"->ReasonReact.string </h1> <Board cells /> </main>;
};