open Css;

let defaultBackgroundHex = "f2f2f2";
let darkerBackgroundHex = "d8d8d8";
let defaultBorderHex = "000000";
let defaultTextHex = "000000";
let defaultClickableTextHex = "B60024";
let defaultClickableHoveredTextHex = "DC143C";

let stielettaHex = "DAA520";
let anethirHex = "6A0DAD";
let jazielHex = "4876FF";
let euporieHex = "8B0000";

let dialogZIndex = 1000;

let scrollbarWidth = 20;

let buttonsArea = style([
  width(`percent(100.)),
  display(`flex),
  flexWrap(`wrap),
  justifyContent(`spaceAround),
  alignItems(`center),
  borderTop(`px(1), `solid, `hex(defaultBorderHex)),
  paddingTop(`px(10)),
  marginTop(`px(10)),
]);

global("button", [
  cursor(`pointer),
  margin(`px(10)),
  paddingTop(`em(0.35)),
  paddingBottom(`em(0.35)),
  paddingLeft(`em(1.2)),
  paddingRight(`em(1.2)),
  border(`em(0.1), `solid, `hex(defaultBorderHex)),
  backgroundColor(`hex(darkerBackgroundHex)),
  borderRadius(`em(0.12)),
  textAlign(`center),
  transitionDuration(200),
  hover([
    backgroundColor(`hex(defaultBorderHex)),
    color(`hex(defaultBackgroundHex)),
  ]),
  active([
    backgroundColor(`hex(defaultBorderHex)),
    color(`hex(defaultBackgroundHex)),
  ]),
]);

global("hr", [
  borderColor(`hex(defaultBorderHex)),
  width(`percent(100.)),
]);

global("body", [
  unsafe("scrollbar-width", string_of_int(scrollbarWidth) ++ "px"),
]);

global(
  "::-webkit-scrollbar-track:vertical",
  [
    boxShadow(
      Shadow.box(
        ~x=`px(1),
        ~y=`px(0),
        ~blur=`px(1),
        ~spread=`px(0),
        ~inset=true,
        `hex("F6F6F6"),
      ),
    ),
    boxShadow(
      Shadow.box(
        ~x=`px(-1),
        ~y=`px(0),
        ~blur=`px(1),
        ~spread=`px(0),
        ~inset=true,
        `hex("F6F6F6"),
      ),
    ),
  ],
);

global(
  "::-webkit-scrollbar-track:horizontal",
  [
    borderLeft(`px(1), `solid, `hex(defaultBorderHex)),
    boxShadow(
      Shadow.box(
        ~x=`px(0),
        ~y=`px(1),
        ~blur=`px(1),
        ~spread=`px(0),
        ~inset=true,
        `hex("F6F6F6"),
      ),
    ),
    boxShadow(
      Shadow.box(
        ~x=`px(0),
        ~y=`px(-1),
        ~blur=`px(1),
        ~spread=`px(0),
        ~inset=true,
        `hex("F6F6F6"),
      ),
    ),
  ],
);

global(
  "::-webkit-scrollbar",
  [
    backgroundColor(`hex(defaultBackgroundHex)),
    width(`px(scrollbarWidth)),
    unsafe("-webkit-appearance", "none"),
  ],
);

global(
  "::-webkit-scrollbar-thumb",
  [
    backgroundClip(`paddingBox),
    backgroundColor(`hex(darkerBackgroundHex)),
    borderColor(`transparent),
    borderTopLeftRadius(`px(9)),
    borderTopRightRadius(`px(8)),
    borderBottomRightRadius(`px(8)),
    borderBottomLeftRadius(`px(9)),
    borderStyle(`solid),
    borderTopWidth(`px(3)),
    borderRightWidth(`px(3)),
    borderBottomWidth(`px(3)),
    borderLeftWidth(`px(4)),
    boxShadow(
      Shadow.box(
        ~x=`px(0),
        ~y=`px(0),
        ~blur=`px(1),
        `rgba((255, 255, 255, 0.5)),
      ),
    ),
  ],
);

global(
  "::-webkit-scrollbar-thumb:hover",
  [backgroundColor(`rgba((0, 0, 0, 0.5)))],
);