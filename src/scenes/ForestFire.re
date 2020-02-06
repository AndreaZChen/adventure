let id = "forestFire";

type state = {charactersReactedSequence: list(Character.t)};

let initialState = {charactersReactedSequence: []};

type action =
  | NextScene
  | ReactStieletta
  | ReactAnethir
  | ReactJaziel;

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
        charactersReactedSequence:
          Belt.List.add(state.charactersReactedSequence, Jaziel),
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
         <FadeInDiv fadeInTime=2000>
           <Text>
             {js|The forest is a roaring inferno.

Stieletta, Anethir, and Jaziel are on their feet, standing back to back around the campfire in the center of the clearing.

A disembodied voice cackles somewhere among the trees.|js}
           </Text>
         </FadeInDiv>
       | [Anethir] =>
         <FadeInDiv fadeInTime=2000>
           <Text>
             {js|"Are you guys seeing this?" Anethir exclaims, pointing at the ring of fire that surrounds their camp.

"YES!" Jaziel and Stieletta shout in response.

"No, I don't mean the fire, I mean I "|js}
           </Text>
           <Text italicize=true> "do" </Text>
           <Text>
             {js| mean the fire, but the—just look!"

They pick up a small twig from the ground, and poke at the campfire with it; orange |js}
           </Text>
         </FadeInDiv>
       | [_reaction1, _reaction2, _reaction3, ..._] => React.null
       }}
      <br />
      <FadeInDiv
        className=CommonStyles.buttonsArea fadeInTime=2500 startFadeInAt=2000>
        {localState.charactersReactedSequence->Belt.List.length < 3
           ? <>
               <button onClick={_ => localDispatch(ReactAnethir)}>
                 {React.string("React: Anethir")}
               </button>
               <button onClick={_ => localDispatch(ReactJaziel)}>
                 {React.string("React: Jaziel")}
               </button>
               <button onClick={_ => localDispatch(ReactStieletta)}>
                 {React.string("React: Stieletta")}
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