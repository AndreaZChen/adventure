type t =
  | Anethir
  | Jaziel
  | Stieletta;

type pair =
  | StielettaAnethir
  | AnethirJaziel
  | JazielStieletta;

module NPC = {
  type t =
    | Euporie;
};

type character = t;

module Set = {
  module Comparator = Belt.Id.MakeComparable({type t = character; let cmp = Pervasives.compare});

  type t = Belt.Set.t(character, Comparator.identity);

  let empty: t = Belt.Set.make(~id=(module Comparator));
};