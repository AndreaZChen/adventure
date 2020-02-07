let id = "forestFire";

type state = {
  charactersReactedSequence: list(Character.t),
  anethirBurned: option(bool),
};

let initialState = {
  charactersReactedSequence: [],
  anethirBurned: None,
};

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
      {
        ...state,
        anethirBurned: Some(true)
      },
      _self => {
        scrollToTop();
        None;
      },
    )
  | AnethirReconsiderTouchingFire =>
    ReactUpdate.UpdateWithSideEffects(
      {
        ...state,
        anethirBurned: Some(false)
      },
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

    <>
      {switch (localState.charactersReactedSequence) {
       | [] =>
        <>
         <FadeInDiv key="initial" fadeInTime=2000>
           <Text>
             {js|The forest is a roaring inferno.

Stieletta, Anethir, and Jaziel are on their feet, standing back to back around the campfire in the center of the clearing.

A disembodied voice cackles somewhere among the trees.|js}
           </Text>
         </FadeInDiv>
          <FadeInDiv
            className=CommonStyles.buttonsArea fadeInTime=2500 startFadeInAt=2000>
            <button onClick={_ => localDispatch(ReactAnethir)}>
              {React.string("React: Anethir")}
            </button>
            <button onClick={_ => localDispatch(ReactJaziel)}>
              {React.string("React: Jaziel")}
            </button>
            <button onClick={_ => localDispatch(ReactStieletta)}>
              {React.string("React: Stieletta")}
            </button>
          </FadeInDiv>
        </>
       | [Anethir] =>
        switch (localState.anethirBurned) {
        | None =>
          <>
            <FadeInDiv fadeInTime=2000>
              <Text>
                {js|"Ten gold coins says it's fake," Anethir says nonchalantly.

"What!?" Jaze and Stieletta exclaim in unison.

"You heard me! Fake, illusory, |js}
              </Text>
              <Text italicize=true>
  {js|bedräglig|js}
              </Text>
              <Text>
  {js|, whatever you wanna call it. I'm gonna stick my hand in it."

Jaziel groans, clutching the lute even tighter in his hands. "An, you damned rascal, this isn't the time to—"

With a mad glint in their eye, Anethir runs towards the edge of the clearing, closer to the burning trees...|js}
              </Text>
            </FadeInDiv>
            <br />
            <FadeInDiv
              className=CommonStyles.buttonsArea fadeInTime=2500 startFadeInAt=2000>
              {localState.charactersReactedSequence->Belt.List.length < 3
                ? <>
                    <button onClick={_ => localDispatch(AnethirTouchFire)}>
                      {React.string("Put hand in fire")}
                    </button>
                    <button onClick={_ => localDispatch(AnethirReconsiderTouchingFire)}>
                      {React.string("Reconsider")}
                    </button>
                  </>
                : <button onClick={_ => localDispatch(NextScene)}>
                    {React.string("Next")}
                  </button>}
            </FadeInDiv>
          </>
        | Some(false) =>
          React.null
        | Some(true) =>
          React.null
        }
       | _ =>
      //  | [_reaction1, _reaction2, _reaction3, ..._] =>
        <>
        <br />
          <FadeInDiv
            className=CommonStyles.buttonsArea fadeInTime=2500 startFadeInAt=2000>
            <button onClick={_ => localDispatch(NextScene)}>
              {React.string("Next")}
            </button>
          </FadeInDiv>
        </>
       }}
    </>;
  };
};

let renderer = (~globalState as _, ~globalDispatch) =>
  <Component globalDispatch />;