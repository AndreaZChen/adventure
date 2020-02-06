let id = "forestFire";

type state = {
  charactersSpokenSequence: list(Character.pair),
};

let initialState = {
  charactersSpokenSequence: [],
};

type action =
  | NextScene
  | SpeakStielettaAnethir
  | SpeakAnethirJaziel
  | SpeakJazielStieletta;

let reducer = (~globalDispatch: GlobalState.action => unit, ~scrollToTop: unit => unit, action: action, state: state) =>
  switch (action) {
  | SpeakStielettaAnethir =>
    ReactUpdate.UpdateWithSideEffects({
      charactersSpokenSequence: Belt.List.add(state.charactersSpokenSequence, StielettaAnethir)
    }, _self => {
      scrollToTop();
      None;
    })
  | SpeakAnethirJaziel =>
    ReactUpdate.UpdateWithSideEffects({
      charactersSpokenSequence: Belt.List.add(state.charactersSpokenSequence, AnethirJaziel)
    }, _self => {
      scrollToTop();
      None;
    })
  | SpeakJazielStieletta =>
    ReactUpdate.UpdateWithSideEffects({
      charactersSpokenSequence: Belt.List.add(state.charactersSpokenSequence, JazielStieletta)
    }, _self => {
      scrollToTop();
      None;
    })
  | NextScene =>
    ReactUpdate.NoUpdate;
  };

module Component = {
  [@react.component]
  let make = (~globalDispatch: GlobalState.action => unit) => {
    let scrollToTop = ScrollToTopProvider.useScrollToTop();
    let reducer = React.useMemo2(() => reducer(~globalDispatch, ~scrollToTop), (globalDispatch, scrollToTop));
    let (localState, localDispatch) = ReactUpdate.useReducer(initialState, reducer);

    <>
      {switch (localState.charactersSpokenSequence) {
      | [] =>
          <FadeInDiv fadeInTime=2000>
            <Text>
{js|Suddenly, the forest erupts into fire.|js}
            </Text>
          </FadeInDiv>
      | _ => React.null
      }}
      <br />
      <FadeInDiv className=CommonStyles.buttonsArea fadeInTime=2500 startFadeInAt=2000>
        {localState.charactersSpokenSequence->Belt.List.length < 3
          ? <>
              <button onClick={_ => localDispatch(SpeakAnethirJaziel)}>
                {React.string("Speak: Anethir x Jaziel")}
              </button>
              <button onClick={_ => localDispatch(SpeakJazielStieletta)}>
                {React.string("Speak: Jaziel x Stieletta")}
              </button>
              <button onClick={_ => localDispatch(SpeakStielettaAnethir)}>
                {React.string("Speak: Stieletta x Anethir")}
              </button>
            </>
          : <button onClick={_ => localDispatch(NextScene)}>
              {React.string("Next")}
            </button>}
      </FadeInDiv>
    </>;
  };
};

let renderer = (~globalState as _, ~globalDispatch) =>
  <Component globalDispatch />;