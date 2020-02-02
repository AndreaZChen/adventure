type action =
  | ActionSent
  | ActionInputFieldUpdated(string)
  | CommandTextClicked(Command.t);

type t = {
  currentCommandReducer: (Command.t, t) => t,
  currentActionInputFieldValue: string,
  actionHistory: list(string),
  redoActionHistory: list(string),
  narrationHistory: list(React.element),
};

let reducer = (action: action, state: t) =>
  switch (action) {
  | ActionSent =>
    state.currentActionInputFieldValue == ""
      ? ReactUpdate.NoUpdate
      : {
        let actionUpdatedState = {
          ...state,
          currentActionInputFieldValue: "",
          actionHistory:
            Belt.List.length(state.actionHistory) >= Config.actionHistoryLimit
              ? Belt.List.take(
                  state.actionHistory,
                  Config.actionHistoryLimit - 1,
                )
                ->Belt.Option.mapWithDefault([], actionHistory =>
                    Belt.List.add(
                      actionHistory,
                      state.currentActionInputFieldValue,
                    )
                  )
              : Belt.List.add(
                  state.actionHistory,
                  state.currentActionInputFieldValue,
                ),
          narrationHistory:
            Belt.List.add(
              state.narrationHistory,
              React.string("> " ++ state.currentActionInputFieldValue),
            ),
        };

        let command = state.currentActionInputFieldValue->Command.fromString;

        state.currentCommandReducer(command, actionUpdatedState)
        ->ReactUpdate.Update;
      }
  | CommandTextClicked(command) =>
    ReactUpdate.Update(state.currentCommandReducer(command, state))
  | ActionInputFieldUpdated(text) =>
    ReactUpdate.Update({...state, currentActionInputFieldValue: text})
  };

let pushNarrationElement = (state: t, narrationElement: React.element) => {
  ...state,
  narrationHistory: Belt.List.add(state.narrationHistory, narrationElement),
};

let pushNarrationString = (state: t, narrationString: string) => {
  ...state,
  narrationHistory:
    Belt.List.add(state.narrationHistory, React.string(narrationString)),
};

let rec initialState = {
  currentCommandReducer: (_, _) => initialState,
  currentActionInputFieldValue: "",
  actionHistory: [],
  redoActionHistory: [],
  narrationHistory: [],
};

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