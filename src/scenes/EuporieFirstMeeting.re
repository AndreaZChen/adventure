module Scene: Interfaces.Scene = {
  let id = "euporieFirstMeeting";

  let title = {js|🔥🌲🌫️ A Forest Clearing 🌫️🌲🔥|js};

  let backgroundColorHex = "E25822";

  type state = {
    charactersReactedSequence: list(Character.t),
    anethirBurned: option(bool),
  };

  let initialState = {charactersReactedSequence: [], anethirBurned: None};

  type action =
    | NextScene
    | ReactStieletta
    | ReactAnethir
    | ReactJaziel
    | AnethirTouchFire
    | AnethirReconsiderTouchingFire;

  let reducer =
      (
        ~globalDispatch: GlobalState.action => unit,
        ~scrollToTop: unit => unit,
        action: action,
        state: state,
      ) =>
    switch (action) {
    | ReactStieletta =>
      ReactUpdate.UpdateWithSideEffects(
        {
          ...state,
          charactersReactedSequence:
            Belt.List.add(state.charactersReactedSequence, Stieletta),
        },
        _self => {
          scrollToTop();
          None;
        },
      )
    | ReactAnethir =>
      ReactUpdate.UpdateWithSideEffects(
        {
          ...state,
          charactersReactedSequence:
            Belt.List.add(state.charactersReactedSequence, Anethir),
        },
        _self => {
          scrollToTop();
          None;
        },
      )
    | ReactJaziel =>
      ReactUpdate.UpdateWithSideEffects(
        {
          ...state,
          charactersReactedSequence:
            Belt.List.add(state.charactersReactedSequence, Jaziel),
        },
        _self => {
          scrollToTop();
          None;
        },
      )
    | AnethirTouchFire =>
      ReactUpdate.UpdateWithSideEffects(
        {...state, anethirBurned: Some(true)},
        _self => {
          globalDispatch(AnethirAddDamage(1));
          scrollToTop();
          None;
        },
      )
    | AnethirReconsiderTouchingFire =>
      ReactUpdate.UpdateWithSideEffects(
        {...state, anethirBurned: Some(false)},
        _self => {
          scrollToTop();
          None;
        },
      )
    | NextScene => ReactUpdate.NoUpdate
    };

  module Component = {
    [@react.component]
    let make = (~globalDispatch: GlobalState.action => unit) => {
      let scrollToTop = ScrollToTopProvider.useScrollToTop();
      let reducer =
        React.useMemo2(
          () => reducer(~globalDispatch, ~scrollToTop),
          (globalDispatch, scrollToTop),
        );
      let (localState, localDispatch) =
        ReactUpdate.useReducer(initialState, reducer);

      <FadeInDiv key="initial" fadeInTime=4000>
        <Text> {js|[To be continued...]|js} </Text>
      </FadeInDiv>;
    };
  };

  let renderer = (~globalState as _, ~globalDispatch) =>
    <Component globalDispatch />;
};