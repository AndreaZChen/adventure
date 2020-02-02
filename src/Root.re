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
      justifyContent(`flexEnd),
      width(`percent(80.)),
      height(`percent(80.)),
    ]);

  global("body", [fontFamily("Lato")]);
};

[@react.component]
let make = () => {
  let globalStateAndDispatch =
    ReactUpdate.useReducer(GlobalState.initialState, GlobalState.reducer);

  <GlobalState.Provider value=globalStateAndDispatch>
    <div className=Styles.rootWrapper>
      <div className=Styles.centralColumn>
        <NarrationDisplay />
        <Input />
      </div>
    </div>
  </GlobalState.Provider>;
};