type t = {actionsHistory: list(string)};

type action =
  | InputAction(string);

let reducer = (action: action, state: t) =>
  switch (action) {
  | InputAction(action) =>
    ReactUpdate.Update({
      actionsHistory:
        Belt.List.length(state.actionsHistory) >= Config.actionHistoryLimit
          ? Belt.List.take(
              state.actionsHistory,
              Config.actionHistoryLimit - 1,
            )
            ->Belt.Option.mapWithDefault([], actionsHistory =>
                Belt.List.add(actionsHistory, action)
              )
          : Belt.List.add(state.actionsHistory, action),
    })
  };

let initialState = {actionsHistory: []};
let initialDispatch: action => unit = ignore;

let context = React.createContext((initialState, initialDispatch));

module Provider = {
  let makeProps = (~children, ~value, ()) => {
    "children": children,
    "value": value,
  };
  let make = React.Context.provider(context);
};

let useGlobalState = () => React.useContext(context);