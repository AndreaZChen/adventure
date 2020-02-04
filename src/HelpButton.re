module Styles = {
  open Css;

  let helpButton = style([
    position(`absolute),
    zIndex(CommonStyles.dialogZIndex - 1),
    top(`px(20)),
    left(`px(20)),
  ]);
};

[@react.component]
let make = (~globalDispatch: GlobalState.action => unit) => {
  let onClick = React.useCallback1(
    _ => globalDispatch(GlobalState.HelpDialogOpened),
    [|globalDispatch|],
  );

  <button className=Styles.helpButton onClick>
    {React.string("?")}
  </button>;
};