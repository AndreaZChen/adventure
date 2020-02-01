[@react.component]
let make = () => {
  let (globalState, _globalDispatch) = GlobalState.useGlobalState();

  globalState.actionsHistory
  ->Belt.List.map(action => React.string(action))
  ->Belt.List.toArray
  ->React.array;
};