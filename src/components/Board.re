let to_styles = length =>
  ReactDOMRe.Style.make(
    ~display="grid",
    ~gridTemplateColumns=
      "repeat("
      ++ (length |> float_of_int |> sqrt |> Js.Float.toString)
      ++ ", 10px)",
    ~gridGap="1px",
    ~position="relative",
    (),
  );

let to_class_name = cell =>
  switch (cell) {
  | Cell.Apple => "cell apple"
  | Cell.Empty => "cell"
  | Cell.Player => "cell player"
  };

[@react.component]
let make = (~cells) =>
  <div style={to_styles(Array.length(cells))}>
    {
      cells
      |> Array.mapi((key, cell) =>
           <div className=cell->to_class_name key=key->string_of_int />
         )
      |> ReasonReact.array
    }
  </div>;