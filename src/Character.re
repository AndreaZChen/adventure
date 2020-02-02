type t =
  | Anethir
  | Jaziel
  | Stieletta;

let toString = (character: t) =>
  switch (character) {
  | Anethir => "Anethir"
  | Jaziel => "Jaziel"
  | Stieletta => "Stieletta"
  };

let fromString = string =>
  switch (string) {
  | "stieletta"
  | "s" => Some(Stieletta)
  | "anethir"
  | "a" => Some(Anethir)
  | "jaziel"
  | "j" => Some(Jaziel)
  | _ => None
  };