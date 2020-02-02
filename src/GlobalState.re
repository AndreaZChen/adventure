type t = {
  currentScene: Scene.t,
  currentActionInputFieldValue: string,
  actionHistory: list(string),
  narrationHistory: list(string),
};

type action =
  | ActionSent
  | ActionInputFieldUpdated(string);

let reducer = (action: action, state: t) =>
  switch (action) {
  | ActionSent =>
    let actionResult: Scene.actionResult =
      state.currentScene.getNextSceneFromAction(
        state.currentActionInputFieldValue,
      );

    ReactUpdate.Update({
      ...state,
      currentActionInputFieldValue: "",
      actionHistory:
        Belt.List.length(state.actionHistory) >= Config.actionHistoryLimit
          ? Belt.List.take(state.actionHistory, Config.actionHistoryLimit - 1)
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
          "> " ++ state.currentActionInputFieldValue,
        )
        ->Belt.List.add(
            switch (actionResult) {
            | NextScene(nextNarration, _nextScene) => nextNarration
            | InvalidAction(message) => message
            },
          ),
      currentScene:
        switch (actionResult) {
        | NextScene(_nextNarration, nextScene) => nextScene
        | InvalidAction(_message) => state.currentScene
        },
    });
  | ActionInputFieldUpdated(text) =>
    ReactUpdate.Update({...state, currentActionInputFieldValue: text})
  };

let initialState = {
  currentScene: InitialScene.value,
  currentActionInputFieldValue: "",
  actionHistory: [],
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