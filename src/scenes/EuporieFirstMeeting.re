module Scene: Interfaces.Scene = {
  let id = "euporieFirstMeeting";

  let title = {js|🔥🌲🌫️ A Forest Clearing 🌫️🌲🔥|js};

  let backgroundColorHex = CommonStyles.euporieHex;

  type state = {charactersGreetedSequence: list(Character.t)};

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
          ...state,
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
          ...state,
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
          ...state,
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
    let make =
        (
          ~globalState: GlobalState.t,
          ~globalDispatch: GlobalState.action => unit,
        ) => {
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
             <FadeInDiv key="noReactionYet" fadeInTime=2000>
               <Text npc=Euporie> "Euporie" </Text>
               <Text>
                 {js| stands at the edge of the clearing, the very picture of grace and elegance. Her pose is casually relaxed, and a wide grin is on her face.

|js}
               </Text>
               <Text character=Stieletta> {js|Stieletta|js} </Text>
               <Text>
                 {js| is glaring daggers at Euporie. She barely seems able to contain her rage.

|js}
               </Text>
               <Text character=Jaziel> {js|Jaziel|js} </Text>
               <Text>
                 {js| takes in Euporie's fine clothing and aristocratic demeanor, looking her up and down. He thinks for a while, then gives her a cautious but approving nod.

|js}
               </Text>
               <Text character=Anethir> {js|Anethir|js} </Text>
               <Text>
                 {js| examines Euporie carefully, then takes a look around at the charred, smoking remains of the clearing they're standing in. They seem unsure what to make of the situation.

|js}
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
                 {React.string("Introduce: Stieletta")}
               </button>
             </FadeInDiv>
           </>
         | [Jaziel, ..._] =>
           <>
             <FadeInDiv key="jazielReacts" fadeInTime=2000>
               <Text>
                 {js|Jaziel takes a step forward, approaching the tiefling woman.

"Greetings, fair Euporie!" he says, spreading his arms in a welcoming gesture. "I am Jaziel, keeper of tales, bringer of wit, taker of hearts. These are my companions, Anethir Compsci—"

"Not how you say that," Anethir interjects.

"—master of the occult, and Stieletta Goldenheel, whom you seem to be acquainted with already." He takes a very deep bow, so theatrical that his hair falls in his face.

Euporie watches Jaziel's spiel with a bemused smile, resting her chin on her hand. "That's lovely," she says. "I like you already."|js}
               </Text>
             </FadeInDiv>
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
         | [Anethir, ..._] =>
           <>
             <FadeInDiv key="anethirReacts" fadeInTime=2000>
               <Text> {js|placeholder|js} </Text>
             </FadeInDiv>
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
         | [Stieletta, ...previousReactions] =>
           let numberOfPreviousThrows =
             Belt.List.keep(previousReactions, previous =>
               previous == Stieletta
             )
             ->Belt.List.length;
           <>
             <FadeInDiv
               key={
                 "stielettaReacts" ++ string_of_int(numberOfPreviousThrows)
               }
               fadeInTime=2000>
               <Text>
                 {switch (numberOfPreviousThrows) {
                  | 0 => {js|Stieletta pulls an ornate hair pin from her hair—long and sharp, like a jeweled dagger—and throws it at Euporie.

The tiefling cocks her head slightly to the side; the hair pin flies past her and lodges itself in a tree.

"Come now, Stieletta," she says. "Where are your manners?"

Stieletta's lips curl into a bitter frown.|js}
                  | 1 => {js|Stieletta pulls another hair pin from her hair and throws it. It whizzes past Euporie's cheek harmlessly, ending up stuck in the same tree behind her.

"Stieletta, please," she says. "You're embarrassing yourself."

Jaziel gives his friend a troubled look. "Are you okay?" he whispers. "Perhaps you should let me handle this one."|js}
                  | 2 => {js||js}
                  | 3 => {js||js}
                  | 4 => {js||js}
                  | _ => {js||js}
                  }}
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
               <button
                 onClick={_ => localDispatch(GreetStieletta)}
                 disabled={globalState.stielettaHairPins <= 0}>
                 {React.string(
                    "Introduce: Stieletta ("
                    ++ globalState.stielettaHairPins->string_of_int
                    ++ " hair pins left)",
                  )}
               </button>
             </FadeInDiv>
           </>;
         }}
      </>;
    };
  };

  let renderer = (~globalState, ~globalDispatch) =>
    <Component globalState globalDispatch />;
};