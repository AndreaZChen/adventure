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
  switch (string->String.lowercase_ascii) {
  | "stieletta"
  | "sti"
  | "s" => Some(Stieletta)
  | "anethir"
  | "an"
  | "a" => Some(Anethir)
  | "jaziel"
  | "jaze"
  | "j" => Some(Jaziel)
  | _ => None
  };