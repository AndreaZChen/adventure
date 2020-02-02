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
    state.currentActionInputFieldValue == ""
      ? ReactUpdate.NoUpdate
      : {
        let command = Command.fromString(state.currentActionInputFieldValue);

        let actionResult: Scene.actionResult =
          state.currentScene.getNextSceneFromCommand(command);

        ReactUpdate.Update({
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
              "> " ++ state.currentActionInputFieldValue,
            )
            ->Belt.List.add(
                switch (actionResult) {
                | NextScene(nextNarration, _)
                | SameScene(nextNarration) => nextNarration
                },
              ),
          currentScene:
            switch (actionResult) {
            | NextScene(_nextNarration, nextScene) => nextScene
            | SameScene(_message) => state.currentScene
            },
        });
      }
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