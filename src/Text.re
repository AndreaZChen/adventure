module Styles = {
  open Css;

  let text = (character: option(Character.t), npc: option(Character.NPC.t), italicize: bool) =>
  style([
    whiteSpace(`preWrap),
    fontStyle(italicize ? `italic : `normal),
    color(`hex(
      switch (character) {
      | Some(Stieletta) => CommonStyles.stielettaHex
      | Some(Anethir) => CommonStyles.anethirHex
      | Some(Jaziel) => CommonStyles.jazielHex
      | None =>
        switch (npc) {
        | Some(Euporie) =>
          CommonStyles.euporieHex
        | None =>
          CommonStyles.defaultTextHex
        }
      })),
  ]);
}

[@react.component]
let make = (~character: option(Character.t)=?, ~npc: option(Character.NPC.t)=?, ~italicize=false, ~children: string) =>
  <span className={Styles.text(character, npc, italicize)}>{React.string(children)}</span>;