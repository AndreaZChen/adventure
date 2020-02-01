[@react.component]
let make = () => {
  let globalStateAndDispatch =
    ReactUpdate.useReducer(GlobalState.initialState, GlobalState.reducer);

  <GlobalState.Provider value=globalStateAndDispatch>
    <Scene />
    <Input />
  </GlobalState.Provider>;
};