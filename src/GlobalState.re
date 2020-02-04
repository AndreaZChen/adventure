type sceneRenderer =
  (~globalState: t, ~globalDispatch: action => unit) =>
  React.element
and action =
  | SceneTransitioned(sceneRenderer)
  | HelpDialogOpened
  | HelpDialogClosed
and t = {
  currentSceneRenderer: sceneRenderer,
  isShowingHelpDialog: bool,
};

let reducer = (action: action, state: t) =>
  switch (action) {
  | SceneTransitioned(newSceneRenderer) =>
    ReactUpdate.Update({
      ...state,
      currentSceneRenderer: newSceneRenderer,
    })
  | HelpDialogOpened =>
    ReactUpdate.Update({
      ...state,
      isShowingHelpDialog: true,
    })
  | HelpDialogClosed =>
    ReactUpdate.Update({
      ...state,
      isShowingHelpDialog: false,
    })
  };