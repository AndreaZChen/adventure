module Styles = {
  open Css;

  let helpButton = merge([
    style([
      position(`absolute),
      zIndex(CommonStyles.dialogZIndex - 1),
      top(`px(20)),
      left(`px(20)),
    ]),
    CommonStyles.defaultButton,
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