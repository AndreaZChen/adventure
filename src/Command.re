type t = {
  character: option(Character.t),
  action: string,
  arguments: list(string),
};

let fromString = string => {
  let words = Js.String.split(" ", string)->Belt.List.fromArray;

  switch (words) {
  | [character, action, ...arguments]
      when Belt.Option.isSome(Character.fromString(character)) => {
      character: Character.fromString(character),
      action,
      arguments,
    }
  | [action, ...arguments] => {character: None, action, arguments}
  | [] => {character: None, action: "", arguments: []}
  };
};

module Defaults = {
  let help = {character: None, action: "help", arguments: []};
};