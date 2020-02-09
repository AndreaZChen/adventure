module Styles = {
  open Css;

  let helpButton =
    style([
      position(`absolute),
      zIndex(CommonStyles.dialogZIndex - 1),
      top(`px(5)),
      right(`px(5)),
    ]);
};

[@react.component]
let make = (~globalDispatch: GlobalState.action => unit) => {
  let onClick =
    React.useCallback1(
      _ => globalDispatch(GlobalState.CharacterMenuOpened),
      [|globalDispatch|],
    );

  <button className=Styles.helpButton onClick>
    {React.string({js|💅🎻🔮|js})}
  </button>;
};