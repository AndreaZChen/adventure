let getSceneById: string => (module Interfaces.Scene) =
  id =>
    switch (id) {
    | id when id == InitialScene.Scene.id => (module InitialScene.Scene)
    | id when id == ForestFire.Scene.id => (module ForestFire.Scene)
    | id when id == EuporieFirstMeeting.Scene.id =>
      (module EuporieFirstMeeting.Scene)
    | _unknownId => (module InitialScene.Scene)
    };