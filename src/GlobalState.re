type action =
  | SceneTransitioned(string)
  | HelpDialogOpened
  | HelpDialogClosed
  | CharacterMenuOpened
  | CharacterMenuClosed
  | AnethirAddDamage(int)
  | JazielAddDamage(int)
  | StielettaAddDamage(int)
  | StielettaRemoveHairPins(int);

type t = {
  currentSceneId: string,
  isShowingHelpDialog: bool,
  isShowingCharacterMenu: bool,
  anethirDamage: int,
  jazielDamage: int,
  stielettaDamage: int,
  stielettaHairPins: int,
};

let defaultState = {
  currentSceneId: "",
  isShowingHelpDialog: false,
  isShowingCharacterMenu: false,
  anethirDamage: 0,
  jazielDamage: 0,
  stielettaDamage: 0,
  stielettaHairPins: 5,
};

let storeState: t => unit =
  state => {
    open Dom.Storage;
    setItem("currentSceneId", state.currentSceneId, localStorage);
    setItem(
      "anethirDamage",
      state.anethirDamage->string_of_int,
      localStorage,
    );
    setItem("jazielDamage", state.jazielDamage->string_of_int, localStorage);
    setItem(
      "stielettaDamage",
      state.stielettaDamage->string_of_int,
      localStorage,
    );
    setItem(
      "stielettaHairPins",
      state.stielettaHairPins->string_of_int,
      localStorage,
    );
  };

let loadState: unit => option(t) =
  () => {
    open Dom.Storage;
    let currentSceneIdOpt = getItem("currentSceneId", localStorage);
    let anethirDamageOpt =
      getItem("anethirDamage", localStorage)->Belt.Option.map(int_of_string);
    let jazielDamageOpt =
      getItem("jazielDamage", localStorage)->Belt.Option.map(int_of_string);
    let stielettaDamageOpt =
      getItem("stielettaDamage", localStorage)
      ->Belt.Option.map(int_of_string);
    let stielettaHairPinsOpt =
      getItem("stielettaHairPins", localStorage)
      ->Belt.Option.map(int_of_string);
    switch (
      currentSceneIdOpt,
      anethirDamageOpt,
      jazielDamageOpt,
      stielettaDamageOpt,
      stielettaHairPinsOpt,
    ) {
    | (
        Some(currentSceneId),
        Some(anethirDamage),
        Some(jazielDamage),
        Some(stielettaDamage),
        Some(stielettaHairPins),
      ) =>
      Some({
        currentSceneId,
        isShowingHelpDialog: false,
        isShowingCharacterMenu: false,
        anethirDamage,
        jazielDamage,
        stielettaDamage,
        stielettaHairPins,
      })
    | _ => None
    };
  };

let reducer = (action: action, state: t) =>
  switch (action) {
  | SceneTransitioned(newSceneId) =>
    ReactUpdate.UpdateWithSideEffects(
      {...state, currentSceneId: newSceneId},
      self => {
        storeState(self.state);
        None;
      },
    )
  | HelpDialogOpened =>
    ReactUpdate.Update({...state, isShowingHelpDialog: true})
  | HelpDialogClosed =>
    ReactUpdate.Update({...state, isShowingHelpDialog: false})
  | CharacterMenuOpened =>
    ReactUpdate.Update({...state, isShowingCharacterMenu: true})
  | CharacterMenuClosed =>
    ReactUpdate.Update({...state, isShowingCharacterMenu: false})
  | AnethirAddDamage(damage) =>
    ReactUpdate.Update({
      ...state,
      anethirDamage: state.anethirDamage + damage,
    })
  | JazielAddDamage(damage) =>
    ReactUpdate.Update({...state, jazielDamage: state.jazielDamage + damage})
  | StielettaAddDamage(damage) =>
    ReactUpdate.Update({
      ...state,
      stielettaDamage: state.stielettaDamage + damage,
    })
  | StielettaRemoveHairPins(amount) =>
    ReactUpdate.Update({
      ...state,
      stielettaHairPins: max(state.stielettaHairPins - amount, 0),
    })
  };