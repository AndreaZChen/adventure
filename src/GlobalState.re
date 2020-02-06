type action =
  | SceneTransitioned(string)
  | HelpDialogOpened
  | HelpDialogClosed;

type t = {
  currentSceneId: string,
  isShowingHelpDialog: bool,
};

let storeState: t => unit = state => {
  open Dom.Storage;
  setItem("currentSceneId", state.currentSceneId, localStorage);
};

let loadState: unit => option(t) = () => {
  open Dom.Storage;
  let currentSceneIdOpt = getItem("currentSceneId", localStorage);
  switch (currentSceneIdOpt) {
  | Some(currentSceneId) => Some({
      currentSceneId,
      isShowingHelpDialog: false,
    })
  | None => None
  };
};

let reducer = (action: action, state: t) =>
  switch (action) {
  | SceneTransitioned(newSceneId) =>
    ReactUpdate.UpdateWithSideEffects({
      ...state,
      currentSceneId: newSceneId,
    }, self => {
      storeState(self.state);
      None;
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