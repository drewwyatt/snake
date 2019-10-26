[@react.component]
let make = () => {
  let cells = Hooks.useCells(10);
  <main> <h1> "Snake"->ReasonReact.string </h1> <Board cells /> </main>;
};