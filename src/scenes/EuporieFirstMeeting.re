module Scene: Interfaces.Scene = {
  let id = "euporieFirstMeeting";

  let title = {js|🔥🌲🌫️ A Forest Clearing 🌫️🌲🔥|js};

  let backgroundColorHex = CommonStyles.euporieHex;

  type state = {
    charactersGreetedSequence: list(Character.t),
  };

  let initialState = {charactersGreetedSequence: []};

  type action =
    | NextScene
    | GreetStieletta
    | GreetAnethir
    | GreetJaziel;

  let reducer =
      (
        ~globalDispatch: GlobalState.action => unit,
        ~scrollToTop: unit => unit,
        action: action,
        state: state,
      ) =>
    switch (action) {
    | GreetStieletta =>
      ReactUpdate.UpdateWithSideEffects(
        {
          charactersGreetedSequence:
            Belt.List.add(state.charactersGreetedSequence, Stieletta),
        },
        _self => {
          globalDispatch(StielettaRemoveHairPins(1));
          scrollToTop();
          None;
        },
      )
    | GreetAnethir =>
      ReactUpdate.UpdateWithSideEffects(
        {
          charactersGreetedSequence:
            Belt.List.add(state.charactersGreetedSequence, Anethir),
        },
        _self => {
          scrollToTop();
          None;
        },
      )
    | GreetJaziel =>
      ReactUpdate.UpdateWithSideEffects(
        {
          charactersGreetedSequence:
            Belt.List.add(state.charactersGreetedSequence, Jaziel),
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
    let make = (~globalState: GlobalState.t, ~globalDispatch: GlobalState.action => unit) => {
      let scrollToTop = ScrollToTopProvider.useScrollToTop();
      let reducer =
        React.useMemo2(
          () => reducer(~globalDispatch, ~scrollToTop),
          (globalDispatch, scrollToTop),
        );
      let (localState, localDispatch) =
        ReactUpdate.useReducer(initialState, reducer);

      <>
        {switch (localState.charactersGreetedSequence) {
         | [] =>
           <>
             <FadeInDiv key="initial" fadeInTime=2000>
               <Text>
                {globalState.euporieFirstMeetingStielettaGoesFirst
                ? {js||js}
                : {js|The wall of fire parts, the smoke clears, and there she is.

Leaning against the base of a burning tree is a figure - a tiefling woman, judging by the wine-red skin and smooth curved horns. She's resting one arm on her upraised knee, |js}
++{js|twirling a charred twig absent-mindedly between her fingers, and the other is supporting her head as she lounges. With the deep navy cape draped underneath her, and her relaxed |js}
++{js|demeanour, the tiefling gives off a distinct air of comfort and ownership. The fire doesn't seem to affect her at all; her clothes and skin are completely untouched.

Amber, almond-shaped eyes watch the trail of soot the twig makes as she spins it around—she's either bored, lost in thought, or pretending to be. She does not acknowledge the three adventurers with her gaze.

"My," she says, "|js}}
               </Text>
             </FadeInDiv>
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=2500
               startFadeInAt=2000>
               <button onClick={_ => localDispatch(GreetAnethir)}>
                 {React.string("Introduce: Anethir")}
               </button>
               <button onClick={_ => localDispatch(GreetJaziel)}>
                 {React.string("Introduce: Jaziel")}
               </button>
               <button onClick={_ => localDispatch(GreetStieletta)}>
                 {React.string(
                   Belt.List.some(localState.charactersGreetedSequence, character => character == Stieletta)
                   ? "Introduce: Stieletta (" ++ string_of_int(globalState.stielettaHairPins) ++ " hair pins left)"
                   : "Introduce: Stieletta"
                  )}
               </button>
             </FadeInDiv>
           </>
         | [_reaction1, _reaction2, ..._] =>
           <>
             <br />
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=2500
               startFadeInAt=2000>
               <button onClick={_ => localDispatch(NextScene)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
         }}
      </>;
    };
  };

  let renderer = (~globalState, ~globalDispatch) =>
    <Component globalState globalDispatch />;
};