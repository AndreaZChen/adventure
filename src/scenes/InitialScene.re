

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
    ReactUpdate.SideEffects(_self => {
      globalDispatch(SceneTransitioned(ForestFire.renderer));
      scrollToTop();
      None;
    })
  };

module Component = {
  module InitialNarration = {
    [@react.component]
    let make = () => {
      let narration0 = <Text>
"Three friends are seated around a campfire in the woods."
      </Text>;

      let narration1 = <Text>
"It is nighttime. The forest is dark and silent; massive trees surround them on all sides, but in the small clearing where they have made \
camp, the moon's rays pierce the canopy of leaves above. The warm glow of the campfire bathes them in a dim but cozy light."
      </Text>;

      let narration2 = <>
        <Text character=Stieletta>
  "Stieletta Goldenheel"
        </Text>
        <Text>
" sits comfortably on the forest floor, eyes closed, with her legs crossed in the lotus position and her hands peacefully folded in her lap. \
She almost looks like she's sleeping, but occasionally an eye flits open to stare at her companions."
        </Text>
      </>;

      let narration3 = <>
        <Text character=Jaziel>
  "Jaziel"
        </Text>
        <Text>
" the bard sits across from her, tuning his lute idly, occasionally plucking on the strings. He doesn't seem to be concentrating very hard on his instrument, \
though; his eyes are drawn to the spiral parchment-book his friend is intently leafing through."
        </Text>
      </>;

      let narration4 = <>
        <Text character=Anethir>
  "Anethir"
        </Text>
        <Text>
" the warlock is perched on a small rock beside Jaziel. The light of the campfire illuminates the pages of their compact notebook, \
which is filled to the brim with arcane scribbles, inscrutable symbols, notes in the margins. They flip back and forth between the same few pages, \
thinking hard."
        </Text>
      </>;

      <>
        narration0
        <br />
        <FadeInDiv fadeInTime=2000>
          narration1
        </FadeInDiv>
        <br />
        <FadeInDiv fadeInTime=4000 startFadeInAt=2000>
          narration2
        </FadeInDiv>
        <br />
        <FadeInDiv fadeInTime=6000 startFadeInAt=4000>
          narration3
        </FadeInDiv>
        <br />
        <FadeInDiv fadeInTime=8000 startFadeInAt=6000>
          narration4
        </FadeInDiv>
      </>;
    };
  };

  [@react.component]
  let make = (~globalDispatch: GlobalState.action => unit) => {
    let scrollToTop = ScrollToTopProvider.useScrollToTop();
    let reducer = React.useMemo2(() => reducer(~globalDispatch, ~scrollToTop), (globalDispatch, scrollToTop));
    let (localState, localDispatch) = ReactUpdate.useReducer(initialState, reducer);

    <>
      {switch (localState.charactersSpokenSequence) {
      | [] => <InitialNarration />
      | [StielettaAnethir] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
  {js|The relative peace and quiet is broken by Stieletta's shrill voice.

"Will you please put down your book of|js}
          </Text>
          <Text italicize=true>
  {js| foul magics?"|js}
          </Text>
          <Text>
  {js| she snaps, glaring at Anethir with one eye. "If you don't sleep now, you'll be too exhausted to keep pace in the morning. You already have short legs. Then poor Jaze here will have to carry you, and nobody wants that."

"ok mom," says Anethir, without even looking up from their notebook.|js}
          </Text>
        </FadeInDiv>
      | [StielettaAnethir, StielettaAnethir] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
  {js|"I'm not joking," she insists. "Jaze will have to carry you on his back all the way to the next settlement. You know how frail and weak his body is."

Jaziel coughs conspicuously. "I'm actually—"

"I don't think we're going to the 'next settlement'," Anethir says, still absorbed by the arcane symbols in their notebook. "If I'm reading this right... northwest, with the mountain... and this could be a tower or a statue or something... but I don't understand the..."

They lean into the spiral notebook, as if pressing their face closer to it would somehow make the runes and patterns more decipherable.|js}
          </Text>
        </FadeInDiv>
      | [JazielStieletta, StielettaAnethir] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
  {js|"Jaze, please do something about this," Stieletta whines. "Play some sort of magic spell that puts gnomes to sleep."

Jaziel laughs softly. "Aren't you supposed to be a monk? Shouldn't you be able to meditate despite a distraction or three?" He winks at her.

Stieletta's face reddens with anger. She opens and closes her mouth several times, but says nothing; then, with an indignant snort, she closes her eyes again and returns to her meditation.|js}
          </Text>
        </FadeInDiv>
      | [AnethirJaziel, StielettaAnethir] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
  {js|"Jaze, please do something about this," Stieletta whines. "Play some sort of magic spell that puts gnomes to sleep."

Jaziel laughs softly, then leans over to Anethir. "You heard the lady, An," he says playfully. "If you can't convince me that what you're doing is extremely cool and important, i'll have to use my bard magics to knock you out."

"Highly doubt it," Anethir replies flatly. They hold up the notebook for Jaziel to read. "D'you see this symbol here?" They tap on a small scribble in the center of the page. "I've almost got this thing figured out, but this one's weird. It's right there in the center, but it's so |js}
          </Text>
          <Text italicize=true>
"simple,"
          </Text>
          <Text>
{js| and that's what throws me off. What's it supposed to be? A sword? Wand? Ooh, wand, actually..."

They pull out a ballpoint quill from a pocket, and start scribbling more notes in the one corner of the page not yet covered with illegible ink.|js}
          </Text>
        </FadeInDiv>
      | [AnethirJaziel] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
  {js|Adjusting the final string, Jaziel finally puts his lute down and leans over towards Anethir.

"So when are you going to share what it is you're working on?" he says, grinning.

"I'm not entirely sure what I'm working on," Anethir replies, "but it sure is work." They frown. "These symbols right here—I wrote 'em down as fast as I could after I woke up, I think I got it all down, but I don't understand—"

They tap a finger on the center of the page, where an elongated, intricate symbol has been drawn, surrounded by incomprehensible scribbles. "I've gotten as far as: we're looking for |js}
          </Text>
          <Text italicize=true>
  {js|this|js}
          </Text>
          <Text>
{js| thing, and I'm pretty sure we're headed in the right direction, but what |js}
          </Text>
          <Text italicize=true>
  {js|is|js}
          </Text>
          <Text>
{js| it?"

They rub the bridge of their nose in frustration.|js}
          </Text>
        </FadeInDiv>
      | [AnethirJaziel, AnethirJaziel] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|Jaziel stares intently at the symbol. It looks like a straight line, with curls coiling around it and some sort of protrusion at the top. His mind swirls with imagery and ideas: a column of fire, a spiral staircase, a gnarled and ancient tree...?

"You'd think your all-knowing patron would be a little bit more forthcoming with these things," he says, stroking his chin. "Why the cryptic riddles?"

"First of all," Anethir replies, "not necessarily all-knowing. Or at least we don't know that It knows all. Secondly, It might not be intentionally cryptic! Maybe It doesn't even speak our languages! I dunno." They shrug. "It's always been communication through dreams and visions with S-dog, that's just how we roll.

"S-dog?" says Jaziel, raising an eye-brow.

"Yeah! You know, the Seeker. S-dog. Big S. 👉👉"

"Urgh!" Jaziel exclaims, wincing and reflexively covering his ears. "I'm never gonna get used to that."

Anethir winks.|js}
          </Text>
        </FadeInDiv>
      | [StielettaAnethir, AnethirJaziel] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|Stieletta snorts loudly, prompting the other two to look up at her.

"Whatever it is that awaits you at the end of your path," she says coldly, "it will not play out the way you expect."

"Yes!!" Anethir exclaims. "That! is the whole point!! We don't know what we're going to find, but we're going to |js}
          </Text>
          <Text italicize=true>
{js|find out|js}
          </Text>
          <Text>
{js|, and that's what it's all about!"

Stieletta's lip curls with disapproval. "But the price will be too high. Trust me, I know of these things. Your dealings with the demon-spawn of the abyss—

"It's not a demon, it's an unspecified extraplanar being," Anethir says.

"—extraplanar beings of the abyss will only lead to death and destruction, for you and for all those you care about."

Anethir pouts, then quietly returns their attention to the notebook. "Implying that I care about..." they mumble, trailing off into silence.|js}
          </Text>
        </FadeInDiv>
      | [JazielStieletta, AnethirJaziel] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|Stieletta sighs performatively, drawing the attention of the other two.

"Jaze, don't get taken in by these vile, occult magics," she says sternly. The dim light from the campfire casts her face in a dramatic glow. "There are better paths for you to travel."

Jaziel scratches the back of his head awkwardly. "You may be right," he says, after a brief pause. "But unlike our friend here—"

He reaches over to pat Anethir on the head, but Anethir swats his hand away, having already sunk back into their studies of the notebook.

"—er, unlike An, I have something at stake. It's not just about knowledge for knowledge's sake..."

An awkward silence. The rustling of leaves in the wind and the faint crackling of the fire somehow feel too overwhelmingly loud.|js}
          </Text>
        </FadeInDiv>
      | [JazielStieletta] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|"Jaze, my dear bard," says Stieletta, "play us a song, that we may end this night in |js}
          </Text>
          <Text italicize=true>
{js|some|js}
          </Text>
          <Text>
{js| degree of comfort and luxury." She takes a deep breath and closes her eyes expectantly.

"Of course, my lady," Jaziel replies with a smug grin. "Are you familiar with the ogre folk song 'All ye Stars'?"

"No," says Stieletta tersely.

Jaziel nods, then hefts the lute into his arms with a practiced motion. His fingers lovingly wrap around its neck, and he begins to sing as he plucks its strings:

|js}
          </Text>
          <Text italicize=true>
{js|"Hark now, thou art an All Star,
get thee thy game on,
mayst thou long play,"|js}
          </Text>
          <Text>
{js|"Change of heart," Stieletta mutters, without opening her eyes. "I think I would rather meditate in silence tonight."|js}
          </Text>
        </FadeInDiv>
      | [JazielStieletta, JazielStieletta] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|"No?" says Jaziel playfully, still strumming on his lute. "I've so many other songs in my repertoire, my lady. Have you heard the one about Ragnar the Red?"

"Spare me," she replies. Still, a very faint smile cracks across her stony face.

"As you wish," he says. Carefully, he puts the lute down on the forest floor, then lies down next to it, crossing his arms behind his head. Above him, the night sky is full of stars, and the full moon shines bright.

"You should try lying down, Stieletta. It's more comfortable "|js}
          </Text>
          <Text italicize=true>
{js|and|js}
          </Text>
          <Text>
{js| you get to see the stars.

She says nothing at first. Silence falls over them, save for the soft crackling of the campfire and the occasional rustle from Anethir's notebook as they leaf through it.

"Maybe I should," she finally says. "Perhaps just this once, I'll..."|js}
          </Text>
        </FadeInDiv>
      | [AnethirJaziel, JazielStieletta] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|"Oh, I know this one!" says Anethir, finally looking up from their notebook.

"Excellent!" Jaziel replies, beaming. "Then let us sing together, my friend! A most shitty serenade for you, my lady."

Stieletta groans, and finally opens her eyes—just enough to squint disapprovingly at the two of them—as they begin to sing:|js}
          </Text>
          <br />
          <Text italicize=true>
{js|"'Tis a cool place, and it doth get colder,
Thou art bundled up now, but wait 'til thou art older,
Alas! ye meteor men beggeth to differ,"|js}
          </Text>
          <br />
          <Text>
{js|"Enough!" she finally shrieks, her face red with fury. Then she stands, rising to her full height, reminding the two singers of just how much taller than them she is.

She marches over to Jaziel with menacing steps and holds out her hand. "Let me play your lute," she says, seething, "and I will show you true suffering—"|js}
          </Text>
        </FadeInDiv>
      | [StielettaAnethir, JazielStieletta] =>
        <FadeInDiv fadeInTime=2000>
          <Text>
{js|But Jaziel does not stop singing; if anything, Stieletta's barely restrained irritation only seems to fuel his playing.

"Warlock, the time has come," Stieletta says, raising her voice somewhat to be heard above the sound of Jaziel's lute. "You must destroy Jaziel with your dark magics. I regretfully urge you to do it."

Anethir looks up from their notebook, stares at Stieletta, then at Jaziel, then at Stieletta again. "Trying to decide whether I'd rather have some peace and quiet so I can decipher these symbols, or have him keep annoying you. Leaning towards the latter."

"Much obliged, An," says Jaziel, still strumming on his lute. "I'll return the favor next time you mess with her."|js}
          </Text>
        </FadeInDiv>
      | [_interaction1, _interaction2, _interaction3, ..._] =>
        <>
          <FadeInDiv fadeInTime=2000>
            <Text>
{js|Suddenly, the forest erupts into fire.|js}
            </Text>
          </FadeInDiv>
          <br />
          <FadeInDiv fadeInTime=4000 startFadeInAt=2000>
            <Text>
{js|Every tree around them bursts into flames at once. A circle of raging fire surrounds the clearing, trapping the three shocked wanderers inside. Gusts of hot air tug at their clothes; sparks and cinders dance around them in little whirlwinds.

"So," |js}
            </Text>
            <Text npc=Euporie>
{js|a voice says|js}
            </Text>
            <Text>
{js|, booming throughout the forest. "Looks like someone else is on the same path as me."

The voice seems to be coming from everywhere all at once, and the flames quiver and roar in sync with its words. "I have to say, I was expecting competition sooner! But no matter. Better to overestimate than to underestimate, right?"|js}
            </Text>
          </FadeInDiv>
        </>
      }}
      <br />
      <FadeInDiv className=CommonStyles.buttonsArea fadeInTime=10000 startFadeInAt=8000>
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

let renderer: GlobalState.sceneRenderer = (~globalState as _, ~globalDispatch) =>
  <Component globalDispatch />;