open Css;

let defaultBackgroundHex = "f2f2f2";
let defaultBorderHex = "000000";
let defaultTextHex = "000000";
let defaultClickableTextHex = "B60024";
let defaultClickableHoveredTextHex = "DC143C";

let dialogZIndex = 1000;

let defaultButton = style([
  paddingTop(`em(0.35)),
  paddingBottom(`em(0.35)),
  paddingLeft(`em(1.2)),
  paddingRight(`em(1.2)),
  border(`em(0.1), `solid, `hex(defaultBorderHex)),
  borderRadius(`em(0.12)),
  textAlign(`center),
  transitionDuration(200),
  hover([
    backgroundColor(`hex(defaultBorderHex)),
    color(`hex(defaultBackgroundHex)),
  ]),
])