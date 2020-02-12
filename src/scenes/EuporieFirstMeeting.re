module Scene: Interfaces.Scene = {
  let id = "euporieFirstMeeting";

  let title = {js|🔥🌲🌫️ A Forest Clearing 🌫️🌲🔥|js};

  let backgroundColorHex = CommonStyles.euporieHex;

  type state = {
    introductionDone: bool,
    charactersGreetedSequence: list(Character.t),
  };

  let initialState = {introductionDone: false, charactersGreetedSequence: []};

  type action =
    | NextScene
    | IntroductionDone
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
    | IntroductionDone =>
      ReactUpdate.Update({...state, introductionDone: true})
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
         | [] when !localState.introductionDone =>
           <>
             {globalState.euporieFirstMeetingStielettaGoesFirst
                ? <>
                    <FadeInDiv key="initial1" fadeInTime=2000>
                      <Text>
                        {js|The circle of flame that ensnares the three adventurers begins to close in on them, as more and more of the clearing is swallowed by smoke and fire.

"Terribly sorry," the mysterious voice gloats, "but this is the end for—"

"Oh, enough!" Stieletta shouts. "I know it's you, |js}
                      </Text>
                      <Text npc=Euporie> "Euporie" </Text>
                      <Text> {js|!"|js} </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial2" fadeInTime=2500 startFadeInAt=2000>
                      <br />
                      <Text> {js|For a moment, nothing happens.|js} </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial3" fadeInTime=3000 startFadeInAt=2500>
                      <br />
                      <Text>
                        {js|And then, in an instant, all of the raging fires disappear into puffs of ash, snuffed out like candles.|js}
                      </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial4" fadeInTime=3500 startFadeInAt=3000>
                      <br />
                      <Text>
                        {{js|From the lingering smoke, a figure emerges.

She is a tiefling woman, with wine-red skin, bright amber eyes, and smooth curved horns. She approaches them with long, regal strides in her leather boots; an ornate cape, dyed a deep navy color, flows behind her. |js}
                         ++ {js|Everything about her, from her smartly tailored vest to the poise and elegance of her gait, exudes wealth and power.

"Well, well!" she says, grinning. "If it isn't Goldilocks Stabbytoes, in all her glory!"|js}}
                      </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial5" fadeInTime=4000 startFadeInAt=3500>
                      <br />
                      <Text> {js|Stieletta grits her teeth.|js} </Text>
                    </FadeInDiv>
                  </>
                : <>
                    <FadeInDiv key="initial1" fadeInTime=2000>
                      <Text>
                        {{js|The wall of fire parts, the smoke clears, and there she is.

Leaning against the base of a burning oak is a figure—a tiefling woman, judging by the wine-red skin and smooth curved horns. She rests one foot on the tree, her knee upraised,|js}
                         ++ {js| while she twirls a charred twig absent-mindedly between her fingers. With the deep navy cape draped underneath her, and her relaxed |js}
                         ++ {js|demeanour, the tiefling gives off a distinct air of comfort and ownership. The fire doesn't seem to affect her at all; her clothes and skin are completely untouched.

Amber, almond-shaped eyes watch the trail of soot the twig makes as she spins it around—she's either bored and lost in thought, or pretending to be. She does not acknowledge the three adventurers with her gaze.

"My name," she says, "is |js}}
                      </Text>
                      <Text npc=Euporie> "Euporie" </Text>
                      <Text>
                        {js|."

She finally looks up at them, a devilish smirk on her face. "And you, my unfortunate friends, are—wait a minute."|js}
                      </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial2" fadeInTime=2500 startFadeInAt=2000>
                      <br />
                      <Text>
                        {js|She coughs, and suddenly her composure is completely lost. In an instant, the raging fires surrounding the clearing vanish into puffs of smoke, snuffed out like a candle.|js}
                      </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial3" fadeInTime=3000 startFadeInAt=2500>
                      <br />
                      <Text>
                        {js|"Stieletta!? Knifeshoes Fancyfoot!?" she says.|js}
                      </Text>
                    </FadeInDiv>
                    <FadeInDiv
                      key="initial4" fadeInTime=3500 startFadeInAt=3000>
                      <br />
                      <Text>
                        {js|A bright grin spreads across her lips.|js}
                      </Text>
                    </FadeInDiv>
                  </>}
             <FadeInDiv
               className=CommonStyles.buttonsArea
               fadeInTime=4000
               startFadeInAt=3500>
               <button onClick={_ => localDispatch(IntroductionDone)}>
                 {React.string("Next")}
               </button>
             </FadeInDiv>
           </>
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