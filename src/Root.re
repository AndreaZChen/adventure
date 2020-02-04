module Styles = {
  open Css;

  let rootWrapper =
    style([
      position(`absolute),
      display(`flex),
      alignItems(`center),
      justifyContent(`center),
      width(`percent(100.)),
      height(`percent(100.)),
      bottom(`px(0)),
      right(`px(0)),
    ]);

  let centralColumn =
    style([
      position(`relative),
      display(`flex),
      flexDirection(`column),
      alignItems(`center),
      justifyContent(`center),
      width(`percent(80.)),
      height(`percent(80.)),
    ]);

  global("body", [
    fontFamily("Lato"),
    lineHeight(`abs(1.8)),
    backgroundColor(`hex(CommonStyles.defaultBackgroundHex)),
  ]);
};

let initialState: GlobalState.t = {
  currentSceneRenderer: InitialScene.renderer,
  isShowingHelpDialog: false,
};

[@react.component]
let make = () => {
  let (globalState, globalDispatch) =
    ReactUpdate.useReducer(initialState, GlobalState.reducer);

  let onCloseHelpDialog = React.useCallback1(() => globalDispatch(HelpDialogClosed), [|globalDispatch|]);

  <div className=Styles.rootWrapper>
    <HelpButton globalDispatch/>
    <div className=Styles.centralColumn>
      {globalState.currentSceneRenderer(~globalState, ~globalDispatch)}
    </div>
    {globalState.isShowingHelpDialog
      ? <HelpDialog onClose=onCloseHelpDialog />
      : React.null}
  </div>
};