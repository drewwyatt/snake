let rec cycle = (list, prepended) =>
  switch (list) {
  | [head, ...tail] when List.length(list) > 1 =>
    cycle(tail, List.append(prepended, [head]))
  | _ => prepended
  };

let wrap = (val_, _) => val_;