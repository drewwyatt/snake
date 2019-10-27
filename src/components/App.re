[@react.component]
let make = () => {
  let direction = Hooks.useDirection();
  let cells = Hooks.useCells(10, direction);
  <main> <h1> "Snake"->ReasonReact.string </h1> <Board cells /> </main>;
};