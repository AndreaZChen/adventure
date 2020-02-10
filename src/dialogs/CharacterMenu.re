module Styles = {
  open Css;

  let nameRightPadding = 15;

  let content = style([display(`grid)]);

  let jazielNameDiv =
    style([
      paddingRight(`px(nameRightPadding)),
      gridRowStart(1),
      gridRowEnd(2),
      gridColumnStart(1),
      gridColumnEnd(2),
      borderBottom(`px(1), `solid, `hex(CommonStyles.defaultBorderHex)),
    ]);

  let jazielInfoDiv =
    style([
      display(`flex),
      alignItems(`flexStart),
      justifyContent(`flexStart),
      flexDirection(`column),
      gridRowStart(1),
      gridRowEnd(2),
      gridColumnStart(2),
      gridColumnStart(3),
      borderBottom(`px(1), `solid, `hex(CommonStyles.defaultBorderHex)),
    ]);

  let anethirNameDiv =
    style([
      paddingRight(`px(nameRightPadding)),
      gridRowStart(2),
      gridRowEnd(3),
      gridColumnStart(1),
      gridColumnEnd(2),
      borderBottom(`px(1), `solid, `hex(CommonStyles.defaultBorderHex)),
    ]);

  let anethirInfoDiv =
    style([
      display(`flex),
      alignItems(`flexStart),
      justifyContent(`flexStart),
      flexDirection(`column),
      gridRowStart(2),
      gridRowEnd(3),
      gridColumnStart(2),
      gridColumnStart(3),
      borderBottom(`px(1), `solid, `hex(CommonStyles.defaultBorderHex)),
    ]);

  let stielettaNameDiv =
    style([
      paddingRight(`px(nameRightPadding)),
      gridRowStart(3),
      gridRowEnd(4),
      gridColumnStart(1),
      gridColumnEnd(2),
    ]);

  let stielettaInfoDiv =
    style([
      display(`flex),
      alignItems(`flexStart),
      justifyContent(`flexStart),
      flexDirection(`column),
      gridRowStart(3),
      gridRowEnd(4),
      gridColumnStart(2),
      gridColumnStart(3),
    ]);
};

[@react.component]
let make = (~globalState: GlobalState.t, ~onClose: unit => unit) => {
  <Dialog onClose>
    <div className=Styles.content>
      <div className=Styles.jazielNameDiv>
        <Text character=Jaziel> {js|🎻 Jaziel|js} </Text>
      </div>
      <div className=Styles.jazielInfoDiv>
        <Text> {js|Class: Bard|js} </Text>
        <Text>
          {{js|Damage taken: |js} ++ string_of_int(globalState.jazielDamage)}
        </Text>
      </div>
      <div className=Styles.anethirNameDiv>
        <Text character=Anethir> {js|🔮 Anethir|js} </Text>
      </div>
      <div className=Styles.anethirInfoDiv>
        <Text> {js|Class: Warlock|js} </Text>
        <Text>
          {{js|Damage taken: |js} ++ string_of_int(globalState.anethirDamage)}
        </Text>
      </div>
      <div className=Styles.stielettaNameDiv>
        <Text character=Stieletta> {js|💅 Stieletta|js} </Text>
      </div>
      <div className=Styles.stielettaInfoDiv>
        <Text> {js|Class: Upper|js} </Text>
        <Text>
          {{js|Damage taken: |js}
           ++ string_of_int(globalState.stielettaDamage)}
        </Text>
        <Text>
          {{js|Hair pins left: |js}
           ++ string_of_int(globalState.stielettaHairPins)}
        </Text>
      </div>
    </div>
    <div className=CommonStyles.buttonsArea>
      <button onClick={_ => onClose()}> {React.string("Close")} </button>
    </div>
  </Dialog>;
};