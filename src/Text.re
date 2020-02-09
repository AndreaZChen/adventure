module Styles = {
  open Css;

  let text =
      (
        character: option(Character.t),
        npc: option(Character.NPC.t),
        italicize: bool,
        bold: bool,
        displayValue,
      ) =>
    style([
      whiteSpace(`preWrap),
      fontStyle(italicize ? `italic : `normal),
      fontWeight(bold ? `bold : `normal),
      display(displayValue),
      color(
        `hex(
          switch (character) {
          | Some(Stieletta) => CommonStyles.stielettaHex
          | Some(Anethir) => CommonStyles.anethirHex
          | Some(Jaziel) => CommonStyles.jazielHex
          | None =>
            switch (npc) {
            | Some(Euporie) => CommonStyles.euporieHex
            | None => CommonStyles.defaultTextHex
            }
          },
        ),
      ),
    ]);
};

[@react.component]
let make =
    (
      ~character: option(Character.t)=?,
      ~npc: option(Character.NPC.t)=?,
      ~italicize=false,
      ~bold=false,
      ~display=`inline,
      ~children: string,
    ) =>
  <span className={Styles.text(character, npc, italicize, bold, display)}>
    {React.string(children)}
  </span>;