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